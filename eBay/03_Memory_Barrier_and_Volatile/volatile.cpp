#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>
using namespace std;

// int notify;
// volatile int notify;
atomic<int> notify;

void watcher()
{
    this_thread::sleep_for(chrono::seconds(2));
    notify = 1;
    cout << "Notification sent." << endl;
}

int main()
{
    thread(watcher).detach();

    notify = 0;
    while (!notify)
    {
        cout << "Waiting." << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }

    cout << "Notification received." << endl;

    return 0;
}
