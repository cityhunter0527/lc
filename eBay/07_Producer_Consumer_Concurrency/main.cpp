/*
 * Requirement:
 * 1. Multi Producer
 * 2. Multi Consumer
 * */

#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>

std::condition_variable cond;
std::queue<int>         q;
std::mutex              mtx;
const size_t Queue_Size_High = 10;
const size_t Max_Event_ID = 30;
bool job_done = false;

// Set high watermark of the queue size;
class Producer {
public:   
    void operator()() {
        static int i = 0;
        for (; i <= Max_Event_ID; i++) {
            while (q.size() >= Queue_Size_High) std::this_thread::yield();
            std::unique_lock<std::mutex> lock(mtx);
            q.push(i);
            cond.notify_one();
        }
        job_done = true;
    }
};

class Consumer {
public:
    void operator()() {
        while (!q.empty() || !job_done) {
            std::unique_lock<std::mutex> lock(mtx);
            if (q.empty()) {
                std::this_thread::yield();
                continue;
            }
            cond.wait(lock, [&](){return !q.empty();});
            int i = q.front();
            q.pop();
            std::cout << std::this_thread::get_id() << ": " << i << std::endl;
        }
    }
};

int main() {
    Producer p;
    Consumer c1;
    std::thread prod_thread1(p);
    std::thread prod_thread2(p);
    std::thread cons_thread1(c1);
    std::thread cons_thread2(c1);

    prod_thread1.join();
    prod_thread2.join();
    cons_thread1.join();
    cons_thread2.join();
    return 1;
}
