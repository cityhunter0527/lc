#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <chrono>
#include <sstream>
#include <cassert>
#include <unistd.h>

const std::thread::id FREE_THREAD_ID = static_cast<std::thread::id>(0);
class Mutex {
private:
    bool isLocked;
    std::thread::id    mTid;
public:
    Mutex() : isLocked(false), mTid(FREE_THREAD_ID) {}
    void lock() {
        // return if already locked by itself
        if (isLocked && mTid == std::this_thread::get_id()) return;
        // if isLocked is false and __sync_lock_test_and_set returns true, it means some other thread
        // is racing and set the isLocked to true before current thread.
        // In this case, current thread need to yield and wait for another round to test_and_set;
        while (isLocked || __sync_lock_test_and_set(&(this->isLocked), true) == true) { 
            std::this_thread::yield();
        }
        mTid = std::this_thread::get_id();
    }
    void unlock() {
        isLocked = false;
        mTid = FREE_THREAD_ID;
    }
};

Mutex               mtx;
std::queue<int>     q;
const size_t        Max_Event_ID    = 30;
bool                job_done        = false;

class Producer {
public:   
    void operator()() {
        static int i = 0;
        while (i <= Max_Event_ID) {
            mtx.lock();
            q.push(i);
            i++;
            mtx.unlock();
        }
        job_done = true;
    }
};

class Consumer {
public:
    void operator()() {
        while (!q.empty() || !job_done) {
            mtx.lock();
            if (q.empty()) {
                mtx.unlock();
                std::this_thread::yield();
                continue;
            }
            int i = q.front();
            q.pop();
            std::cout << std::this_thread::get_id() << ": " << i << std::endl;
            mtx.unlock();
        }
    }
};

int main() {
    Producer p;
    Consumer c;
    std::thread prod_thread1(p);
    std::thread prod_thread2(p);
    std::thread cons_thread1(c);
    std::thread cons_thread2(c);

    prod_thread1.join();
    prod_thread2.join();
    cons_thread1.join();
    cons_thread2.join();

    return 1;
}
