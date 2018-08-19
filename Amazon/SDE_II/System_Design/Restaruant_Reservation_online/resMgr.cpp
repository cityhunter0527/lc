#include "resMgr.hpp"
// 
// Implementation considerations:
// - Reservation needs to be something like accounting. 
// - Tables should not be assigned until reservation is really being claimed.
//
// Requirement:
// - System wide counters:
//
ResvSysMgr::ResvSysMgr(int numTables, int size) {
    for (int i = 0; i < numTables; i++) {
        mTables.push_back(Table(i, size));
        mResvRecordsByTable.push_back(list<ResvRecord>(10));
    }
}

ResvSysMgr::ResvSysMgr(vector<pair<int, int>>& tableVec) {
    TableID tid = 0;
    for (auto x:tableVec) {
        for (int i = 0; i < x.first; tid++, i++) {
            // x.first: numTables.
            // x.second: size
            mTables.push_back(Table(tid, x.second));
            mResvRecordsByTable.push_back(list<ResvRecord>(10));
        }
    }
}

ResvSysMgr::~ResvSysMgr() {
    mTables.clear();
    mCustomers.clear();
    mResvRecordsByTable.clear();
    mResvRecordsByCust.clear();
}

bool ResvSysMgr::reserve(ulong64 uid, ushort numGuest, TimeSlice s) {
    time_t t = time(0);
    // time current time as reservation id
    ulong64 rid = t;

    vector<TableID> out = listAvailable(numGuest, s);
    for (auto x:out) {
        mResvRecordsByTable[x].push_back(ResvRecord(rid, x, uid, s));
        mResvRecordsByCust[uid].push_back(ResvRecord(rid, x, uid, s));
        return true;
    }
    
    return false;
}

bool ResvSysMgr::reserve(ulong64 uid, ushort numGuest, TimeSlice s, TableID tid) {
    time_t t = time(0);
    ulong64 rid = t;

    vector<TableID> out = listAvailable(numGuest, s);
    for (auto x:out) {
        if (x == tid) {
            ResvRecord *rec = new ResvRecord(rid, x, uid, s);
            mResvRecordsByTable[tid].push_back(rec);
            mResvRecordsByCust[uid].push_back(rec);
            return true;
        }
    }
    return false;
}

bool ResvSysMgr::cancel(ulong64 uid) {
    for (list<ResvRecord>::iterator it = mResvRecordsByCust[uid].begin(); it != mResvRecordsByCust[uid].end(); it++) {
        ResvRecord* rec = it;
        mResvRecordsByCust[uid].erase(it);
        delete rec;
    }
    return true;
}

bool ResvSysMgr::cancel(ulong64 uid, ulong64 rid) {
    TableID tid = INVALID_TABLE_ID;
    ResvRecord* rec = nullptr;
    // remove it from the customer reservation list
    for (list<ResvRecord>::iterator it = mResvRecordsByCust[uid].begin(); it != mResvRecordsByCust[uid].end(); it++) {
        if (it->getrid() == rid) {
            tid = it->gettid();
            rec = it;
            mResvRecordsByCust[uid].erase(it);
            break;
        }
    }

    if (tid == INVALID_TABLE_ID)
        return false;

    // remove it from the table reservation list
    for (list<ResvRecord>::iterator it = mResvRecordsByTable[tid].begin(); it != mResvRecordsByTable[tid].end(); it++) {
        if (it->getrid() == rid) {
            mResvRecordsByTable[tid].erase(it);
        }
    }

    if (rec != nullptr) delete rec;
    return true;
}

vector<TableID> ResvSysMgr::listAvailable(ushort numGuest, TimeSlice s) {
    vector<TableID> res; 
    unordered_set<TableID> ctidSet; // conflict table id set
    for (int tid = 0; tid < mResvRecordsByTable.size(); tid++) {
        for (auto x:mResvRecordsByTable[tid]) {
            if (conflictTS(x.getTS(), s)) { 
                // each table will only be added once.
                ctidSet.insert(x.gettid());
                break;
            }
        }
    }
    for (auto y:mTables) {
        // TODO: table size 10, numGuest 2, should we limit it?
        if (ctidSet.find(y.gettid()) == ctidSet.end() && y.getsize() >= numGuest) {
            res.push_back(y.gettid());
        }
    }
    return res;
}

vector<ResvRecord> ResvSysMgr::listReservation(ulong64 uid) {
    vector<ResvRecord> res;
    
    for (auto x:mResvRecordsByCust[uid]) {
        res.push_back(x);
    }

    return res;
}

// if s1 and s2 overlaps, return false;
// Otherwise return true;
// TODO: consider reservation type
bool ResvSysMgr::conflictTS(const TimeSlice s1, const TimeSlice s2) {
    struct tm* s1start = localtime(&(s1.start)), *s1end = localtime(&(s1.end));
    struct tm* s2start = localtime(&(s2.start)), *s2end = localtime(&(s2.end));

    if (s1.start > s1.end || s2.start > s2.end)
        return true;  // s1 not valid or s2 not valid
    if (s1.t == RECUR_NONE && s2.t == RECUR_NONE && (s1.end <= s2.start || s1.start >= s2.end))
        return false; // no overlap
    // overlap
    return true;
}

bool ResvSysMgr::unregist(ulong64 uid) {
    // cancel reservations
    cancel(uid);
    // remove customer
    for (vector<Customer>::iterator it = mCustomers.begin(); it != mCustomers.end(); it++) {
        if (it->getuid() == uid) {
            mCustomers.erase(it);
            return true;
        }
    }
    // remove from mResvRecordsByCust;
    mResvRecordsByCust.erase(mResvRecordsByCust.find(uid));

    return false;
}

// use phoneNum as uid
bool ResvSysMgr::regist(string phone, string firstName, string lastName, string email) {
    ulong64 uid = stoull(phone);
    // TODO: check uid already exists
    mCustomers.push_back(Customer(uid, phone, firstName, lastName, email));
    return true;
}

