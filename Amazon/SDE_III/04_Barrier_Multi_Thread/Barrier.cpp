/*
 * Requirements:
 * 1. Design something out to allow multithreads to wait on something and when all the threads 
 *    reaches that state, then all the threads move on.
 *    
 *    just like java barrier lib
 * */
#include <iostream>
#include <unordered_map>
using namespace std;

ulong64 Barrier::numWaitingClients = 0;
ulong64 Barrier::totalClients = 0;
typedef unsigned long long ulong64;
class Barrier {
typedef ClientID ulong64;
public:
    Barrier() {
        totalClients++;
    }
    static ClientID registerClient() {
        ClientID cid = genClientID();
        clients[cid] = false;
        return cid;
    }
    static void unregisterClient(ClientID cid) {
        clients[cid].erase();
    }
    static ClientID genClientID() {
        return SHA_2(time(NULL));
    }
    static bool wait(ClientID cid) {
        if (!m.try_lock()) {
            // m is already lock by other threads
            return false;
        }
        
        // m is locked
        bool ret = true;
        if (!clients[cid]) {
            clients[cid] = true;
            numWaitingClients++;
        }
        if (numWaitingClients == totalClients) 
            ret = true;
        else
            ret = false;
        m.unlock();
        return ret;
    }
public:
    static ulong64 totalClients;
    static ulong64 numWaitingClients;
    static unordered_map<ClientID, bool> clients;
    static mutex m;
};

class Client: private Barrier {
private:
    ClientID mCid;

public:
    Client() {
        mCid = registerClient();
    }
    ~Client() {
        unregisterClient(mCid);
    }

    void runTask() {
        while (!wait(mCid)) {
            sleep (10);
        }
    }
};
