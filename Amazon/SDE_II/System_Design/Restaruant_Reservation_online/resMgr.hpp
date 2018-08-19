#ifndef RESV_MGR_HPP
#define RESV_MGR_HPP

#include <vector>
#include <list>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <climits>
using namespace std;

/*
 *  Requirement:
 *      1. List available tables
 *      2. List your resrved information
 *      3. Make a reservation
 *          3.a Long duration reservation (2 years?)
 *          3.b Repeated reservation (every monday lun?)
 *          3.c Reserve by housrs (lunch: 11:00 ~ 14:00, dinner: 17:00 ~ 21:00
 *      4. Cancle a reservation
 *      5. For time being, all the reservation records need a way to complete automatcially to free tables.
 * * */
typedef unsigned long long ulong64;
typedef unsigned int   ulong32;
typedef unsigned short ushort;
typedef unsigned char  uchar;
typedef ushort TableID;

const ushort INVALID_TABLE_ID = USHRT_MAX;
const ushort MAX_TABLE_ID = USHRT_MAX - 1;
const ushort MIN_TABLE_ID = 0;

typedef enum {
    RECUR_NONE,
    RECUR_DAILY, 
    RECUR_WEEKLY,
    RECUR_MONTHLY,
    RECUR_YEARLY
} RecurType;

struct TimeSlice{
    time_t start;
    time_t end;
    RecurType t;
    ushort numOccur;
};

class Table {
public:
    Table(TableID t, ushort tsize):tid(t), size(tsize) {}
    ushort gettid() {return tid;}
    ushort getsize() {return size;}
private:
    TableID tid;
    ushort size;
};

class Customer {
public:
    Customer(ulong64 u, string phoneNum, string fn, string ln, string mail) : uid(u), phone(phoneNum), firstName(fn), lastName(ln), email(mail) {}
    ulong64 getuid() {return uid;}
private:
    ulong64 uid; // user id
    string  phone;
    string  lastName;
    string  firstName;
    string  email;
};

class ResvRecord {
public:
    ResvRecord() {}
    ResvRecord(ulong64 r, TableID t, ulong64 u, TimeSlice ts) : rid(r), tid(t), uid(u), s(ts) {}
    ~ResvRecord(){}
    ulong64 getrid() {return rid;}
    ulong64 getuid() {return uid;}
    ulong64 gettid() {return tid;}
    TimeSlice getTS() {return s;}
private:
    ulong64   rid;  // reservation id
    TableID   tid;  // table id
    ulong64   uid;  // user id
    TimeSlice s;
};

class ResvSysMgr {
private: 
    vector<Table>                               mTables;
    vector<Customer>                            mCustomers;
    vector<list<ResvRecord*>>                   mResvRecordsByTable; 
    unordered_map<ulong64, list<ResvRecord*>>   mResvRecordsByCust;
private:
    bool conflictTS(const TimeSlice s1, const TimeSlice s2);
public:
    ResvSysMgr(int numTables, int size);
    ResvSysMgr(vector<pair<int, int>>& t); // each pair <numTables, size>
    ~ResvSysMgr(); 
public:
    // make a reservation
    bool reserve(ulong64 uid, ushort numGuest, TimeSlice s);

    // reserv a reservation on some table
    bool reserve(ulong64 uid, ushort numGuest, TimeSlice s, TableID tid);
    
    // cancle a reservation
    bool cancel(ulong64 uid, ulong64 resid);
    
    // cancle all reservations by a customer
    bool cancel(ulong64 uid);
 
    // list successful reservation by user id
    vector<ResvRecord> listReservation(ulong64 uid);
  
    // list available tables for reservation
    vector<TableID> listAvailable(ushort numGuest, TimeSlice s); 
   
    // user regist
    bool regist(string cellPhoneNum, string lastName, string firstName, string email);

    // user unregist
    bool unregist(ulong64 uid);
    bool unregist(string cellPhoneNum) {return unregist(stoull(cellPhoneNum));}
    
    // clean all the reservations whose TS is in the past
    void cleanPastReservations();
};
#endif
