#include <iostream>           // std::cout
#include <thread>             // std::thread, std::this_thread::yield
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable

std::mutex mtx;
std::condition_variable cv;

int cargo = 0;
bool shipment_available() {return cargo!=0;}
const int MAX_CARGO = 100;

// 
// A buggy implementation for multiple consumer:
// 1. The below code will hang with thread c2 wait forever. 
// 2. The race is cause when c2 enters with i equals to 99, switch out to c1.
// 3. c1 calls ++i  and i becomes 100 which is not < n and then c1 exits by calling c1.join().
// 4. CPU resumes c2 and now c2 has i being 100 which is different as 99 when c2 enters this for loop. And since the last cargo has been received by c1, cargo becomes zero (set by c1 which consumed this cargo), so shipment_available always return false. 
// 5. c2 waits forever.
//
void consume (int n) {
    static int i = 0;
    for (; i < n; ++i) {  
        std::unique_lock<std::mutex> clock(mtx);
        cv.wait(clock, shipment_available);
        // consume:
        std::cout << cargo << '\n';
        cargo=0;
    }
}

int main ()
{
    std::thread c1(consume, MAX_CARGO);
    std::thread c2(consume, MAX_CARGO);

    // produce 10 items when needed:
    for (int i=0; i<MAX_CARGO; ++i) {
        while (shipment_available()) std::this_thread::yield();
        std::unique_lock<std::mutex> plock(mtx);
        cargo = i+1;
        cv.notify_one();
    }

    c1.join();
    c2.join();

    return 0;
}
