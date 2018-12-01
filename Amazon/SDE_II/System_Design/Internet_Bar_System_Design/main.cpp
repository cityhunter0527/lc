//System-Design: Internet bar management system.


#include <iostream>

class SysMgr {
private:
    map<SEATID, Seat>           mSeats;
    SeatMgr                     mstMgr;
    map<USERID, SEATID>         mUsers;
public:
    bool checkin(USERID uid, SEATTYPE type, RESERVE_TYPE rType = PER_HOUR) {
        SEATID sid;
        if (mstMgr.find(type)) {
            sid = mstMgr.getOneSeat(type);
            assert(mSeats[sid].isAvailable());
            mSeats[sid].makeReservation(uid, rType);
            mUsers[uid] = sid;
            return true;  
        } else {
            return false;
        }
    }
    
    void checkout(USERID uid, BILLRecord& b) {
         mSeats[mUsers[uid]].releaseReservation(b); 
         mUsers.earse(mUsers.find(uid));
    }
};

class Seat {
private:
    bool      isReserved;
    USERID    uid;
    SEATID    sid;
    SEATTYPE  type;
    RESERVE_TYPE rtype;
    time_t    start;
    time_t    end;
public:
    Seat(SEATID id, SEATTYPE t) {sid = id; type = t; sReserved = false;}
    ~Seat() {}
    
    void startBilling() {start = getCurrentTime();}
    void endBilling(BILLRecord& b) {
        if (rtype == PER_HOUR) {
            end = getCurrentTime();
            b = getUnitHourPrice() * (start - end)/(1000*1000*1000);
        } else if (rtype == PER_NIGHT) {
            int nNights = getNights();
            int nDays = getDays();
            start = getNewStart();
            end = getCurrentTime();
            b = nNights * PER_NIGHT_FEE + nDays * PER_DAY_FEE + getUnitHourPrice() * (start - end)/(1000*1000*1000);
        }
    }
    
    bool isAvailable() {
        return isReserved;
    }
    
    void releaseReservation(BILLRecord& b) {
        endBilling(b);
        isReserved = false;
        uid = USER_ID_NONE;
        start = 0;
        end = 0;
    }
    
    bool makeReservation(USERID id, RESEARV_TYPE rType = PER_HOUR) {
        if (isAvailable()) {
            rtype = rType;
            isReserved = true;
            uid = id;
            startBiling();
            return true;
        }
        return fales;
    }
};

