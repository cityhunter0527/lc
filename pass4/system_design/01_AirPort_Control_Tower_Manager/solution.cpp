/*
 *  Design an airport control tower management system
 *  1. Fly out and Landing airplane management
 *  2. Ability to track which plane is delayed, how many hours are delayed to prioritize
 *  3. Ability to cancel some flight due to remote city weather condition.
 *
 *  Solution:
 *  1. One queue for fly out
 *  2. One queue for landing 
 *  3. each airplane is an object which will request:
 *     3.1 fly in or land
 *     3.2 class members include start time (calculate delay hours), target city, etc.
 *  4. Each runway whould have one waiting way there should a limited number of airplanes on this waiting way. 
 *     other planes should be still connected to bridge before waiting way has room to be queued.
 *  5. Each plane in the air waiting for landing should have left fuel to calculate the flight hours.
 *     Need to handle urgent flight which has limited fuels left (top priority).  
 * */

#include <iostream>

class Passenger {

};

class Flight {
private:
    std::string m_id;                       // flight id
    std::string m_planned_out;              // planned flying out time
    std::string m_duration;                 // flight duration
    std::string m_date;                     // date of this flight: MM/DD/YY
    std::string m_orig_airport;
    std::string m_dest_airport;
    
    std::string m_delayed_time_in_mins;     // deleyed time
    std::vector<std::shared_ptr<Passenger>> m_passengers;

    std::string m_state;                    // ON_BORDING, WAITING_TO_FLY, FLYING, LANDED, BAGAGE_CLAIMING;
    std::string m_left_fuel_flying_in_hours;// flying hours based on the left fuels in the plane;

    std::string m_landing_runway_id;
    std::string m_flying_out_runway_id;

public:
    std::string get_landing_time();
    std::string get_departure_time();
    std::string get_delayed_time();         // how long has this flight been delayed, this information will be showed on screen for passengers in the tower lobby;
    std::string get_left_fuel_flying_time_in_hours();  // how long can this plane flying in the air based on left fuel;

    void set_runway_id(std::string runway_id);
};

class Runway {
private:
    std::string                         m_uuid;      // airport + runway_id;
    std::deque<std::string flight_id>   m_queue;     // each runway should be queued with a list of flights which can either be flying out or landing in.
    std::uint32_t                       m_waiting_way_size;  // each runway will have a waiting way beside it, and this waiting way will have a limitation of planes to be queued.

public:
    void land_request(std::string flight_id);
    void fly_request(std::string flight_id);
};

class Tower {
private:
    std::string                             m_tower_id;
    std::vector<std::shared_ptr<Runway>>    m_runways;
    std::vector<std::string>                m_runway_ids;
    std::deque<std::shared_ptr<Flight>>     m_waiting_list;  // flights that ask for leaving but not assigned with runway yet; 

    std::map<std::string, std::shared_ptr<Flight>>  m_flight_map; // map from flight_id to Flight instance;
    std::map<std::string, std::shared_ptr<Runway>>  m_runway_map; // map from runway_id to Runway instance;

private:
    // get free runway for next flight;
    std::string get_free_runway() {
        
    }
    
    std::shared_ptr<Runway> get_runway_by_id(std::string runway_id) {
    
    }

    std::shared_ptr<Flight> get_flight_by_id(std::string flight_id) {
    
    }

public:
    // assign runway for landing in flight
    bool landing_or_flying_reqeust(std::string flight_id) {
        std::string runway_id = get_free_runway();
        if (runway_id.empty()) { 
            // all runways are currently full, can't satisfy the landing request. 
            return false;
        }
        get_runway_by_id(runway_id)->land_request(flight_id);
        get_flight_by_id(flight_id)->set_runway(runway_id);

        return true;
    }

    // assign runway for urgent flight with limited fuel
    void urgent_landing(std::string flight_id) {
    
    }

    void landed(std::string flight_id) {
    
    }
};

int main() {
    return 0;
}

