// condition_variable::wait (with predicate)
#include <iostream>           // std::cout
#include <thread>             // std::thread, std::this_thread::yield
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable


// 2. Can this code work for multiple consumer and producer? why? 
//    No. 
// 3. Can this code work w/o cond var? If yes, how and could it scale for multiple consuder/producer?
//    Yes.
std::mutex mtx;
std::condition_variable cv;

int cargo = 0;
bool shipment_available() {return cargo!=0;}

void consume (int n) {
    for (int i = 0; i < n; ++i) {
        // mtx.lock() will be called during construction of clock;
        // Blocks if mtx is already locked until mtx is unlocked.
        std::unique_lock<std::mutex> clock(mtx);
        std::cout << std::this_thread::get_id() << ", i: " << i << std::endl;
        // 1. Only blocks (mtx automatcially unlocked) if shipment_available returns false; 
        //    and notification can only unblock this thread when shipment_available becomes true;
        // 2. If shipment_avaialbe returns true, or this thread is unblocked by notification, 
        //    mtx is still automatcially locked.
        cv.wait(clock, shipment_available);
        // consume:
        std::cout << cargo << '\n';
        cargo=0;
        // automatcially call mtx.unlock() in clock's destruction function.
    }
}

int main ()
{
    std::thread consumer_thread (consume,10);

    // produce 10 items when needed:
    for (int i=0; i<10; ++i) {
        while (shipment_available()) std::this_thread::yield();
        // if plock is not declared here, there will be a race:
        // 1. In consume function, after aquire clock, it checks shipment_available (cargo still 0)
        // 2. Before consume thread decides to wait, switch out to main thread.
        // 3. main thread increase cargo by 1 and call notify_one then switch out to consume thread
        // 4. consume thread resumed and call wait, since notify_one is called before wait, wait will wait forever.
        // 5. main thread resumed and keep tracking "shipment_available" and since cargo is still non-zero, it keeps doing yield();
        // 6. Deap lock.
        std::unique_lock<std::mutex> plock(mtx);
        // automatcially call mtx.lock() in plock's construction function;
        cargo = i+1;
        cv.notify_one();
        // automatcially call mtx.unlock() in plock's destruction function;
    }

    consumer_thread.join();

    return 0;
}
