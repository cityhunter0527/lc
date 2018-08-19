#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include <vector>
#include <cassert>

void* sharedData = nullptr;
std::atomic<int> ready_flag(0);

void* getSharedData() {
    return (void*)0xdeadbeaf;
}

void processData(void* sharedData) {

}

// Thread 1
void produce() {
    sharedData = getSharedData();
    ready_flag.store(1, std::memory_order_release); // <<< All writes in the current thread are visible in other threads that acquire the same atomic variable
}

// Thread 2
void consume() {
    while (ready_flag.load(std::memory_order_acquire) == 0) {  // <<< All writes in other threads that release the same atomic variable are visible in the current thread.
        std::this_thread::yield();
    }
    assert(sharedData != nullptr); // will never trigger because of the memory order acquired, sharedData is assured to be assigned with getSharedData() return value if ready_flag is loaded as non-zero;
    processData(sharedData);
}

int main() {
    std::thread p(produce);
    std::thread c(consume);
    p.join();
    c.join();
    return 1;
}
