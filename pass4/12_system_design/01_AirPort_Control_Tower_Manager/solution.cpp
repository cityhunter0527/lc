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
#include <string>
#include <map>
#include <vector>
#include <deque>
#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.

class Passenger { 

}; 

class Flight {
public:
    enum FlightState{
        WAIT_FOR_LANDING,
        WAIT_ON_RUNWAY_TO_FLY_OUT
    };
private:
    std::string m_id;                       // flight id
    std::string m_planned_out;              // planned flying out time
    std::string m_duration;                 // flight duration
    std::string m_date;                     // date of this flight: MM/DD/YY
    std::string m_orig_airport;
    std::string m_dest_airport;
    
    std::string m_delayed_time_in_mins;     // deleyed time
    std::vector<std::shared_ptr<Passenger>> m_passengers;

    FlightState m_state;                    // ON_BORDING, WAITING_TO_FLY, FLYING, LANDED, BAGAGE_CLAIMING;
    std::string m_left_fuel_flying_in_hours;// flying hours based on the left fuels in the plane;

    std::string m_runway_id;

public:
    std::string get_landing_time();
    std::string get_departure_time();
    std::string get_delayed_time();                     // how long has this flight been delayed, this information will be showed on screen for passengers in the tower lobby;
    std::string get_left_fuel_flying_time_in_hours();   // how long can this plane flying in the air based on left fuel;

    void set_runway_id(std::string runway_id) {
        m_runway_id = runway_id;
    }
    void set_state(FlightState s) {
        m_state = s;
    }
};

class Runway {
    enum RUNWAY_USE_TYPE {
        RUNWAY_LANDING = 1, 
        RUNWAY_FLYING
    };
private:
    std::string                         m_uuid;             // airport + runway_id;
    std::uint32_t                       m_waiting_way_size; // each runway will have a waiting way beside it, and this waiting way will have a limitation of planes to be queued.
    std::uint32_t                       m_cur_waiting_way_size; // each runway will have a waiting way beside it, and this waiting way will have a limitation of planes to be queued.
    std::deque<std::pair<std::string, RUNWAY_USE_TYPE>>   m_queue;  // each runway should be queued with a list of flights which can either be flying out or landing in.


public:
    Runway(std::string uuid, int size) : m_uuid(uuid), m_waiting_way_size(size) {}

    // when this request is issued, there must be enough room in the waiting_way;
    // TODO: multithreading considerations;
    void land_request(std::string flight_id) {
        m_queue.push_back(std::make_pair(flight_id, RUNWAY_USE_TYPE::RUNWAY_LANDING));
    }

    void fly_request(std::string flight_id) {
        m_queue.push_back(std::make_pair(flight_id, RUNWAY_USE_TYPE::RUNWAY_FLYING));
        assert(m_cur_waiting_way_size < m_waiting_way_size);
        
        m_cur_waiting_way_size++;
    }

    std::string get_next_flight_id() {
        auto flight = m_queue.front();
        if (flight.second == RUNWAY_USE_TYPE::RUNWAY_FLYING)
            m_cur_waiting_way_size--;
        m_queue.pop_front();
        return flight.first;
    }

    uint32_t get_available_capacity() {
        return m_waiting_way_size - m_queue.size();
    }

    std::string get_id() {
        return m_uuid;
    }
};

#define DEFAULT_RUNWAY_SIZE 10

// TODO: When a flight is flying out, it needs to reserve runway seat at destination tower's management system;
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
    // select the runway with minimum queue size;
    // TODO: add maximum runway queue size. we should send alert to fail the reqeust if the runways are queued with too many landing flights;
    // flying out flights are already limited by runway_waiting way's size
    std::string get_free_runway_by_id() {
        int min_size = DEFAULT_RUNWAY_SIZE;
        std::string runway_id;
        for (int i = 0; i < m_runways.size(); i++) {
            uint32_t s = m_runways[i]->get_available_capacity();
            assert (s <= DEFAULT_RUNWAY_SIZE);
            if (min_size < s) {
                min_size = m_runways[i]->get_available_capacity();
                runway_id = m_runways[i]->get_id();
            }
        }

        return runway_id;
    }
    
    // TODO: check for non-exist runway id
    std::shared_ptr<Runway> get_runway_by_id(std::string runway_id) {
        return m_runway_map[runway_id];
    }

    // TODO: check for non-exist flight id
    std::shared_ptr<Flight> get_flight_by_id(std::string flight_id) {
        return m_flight_map[flight_id];
    }

public:
    Tower(int num_runway, std::string tower_id) : m_tower_id(tower_id) {
        for (size_t i = 0; i < num_runway; i++) {
            // generate runway uuid and instances;
            boost::uuids::uuid uuid = boost::uuids::random_generator()();
            std::string uuid_str = boost::uuids::to_string(uuid);
            m_runways.push_back(std::make_shared<Runway>(uuid_str, DEFAULT_RUNWAY_SIZE));          
            m_runway_map[uuid_str] = m_runways[i];
        }
    }

    // assign runway for landing in flight
    bool landing_or_flying_reqeust(std::string flight_id, bool landing = true) {
        std::string runway_id = get_free_runway_by_id();
        std::shared_ptr<Runway> prunway = get_runway_by_id(runway_id);
        std::shared_ptr<Flight> pflight = get_flight_by_id(flight_id);
        if (landing) {
            pflight->set_state(Flight::FlightState::WAIT_FOR_LANDING);
        } else {
            pflight->set_state(Flight::FlightState::WAIT_ON_RUNWAY_TO_FLY_OUT);
        }
        if (runway_id.empty()) { 
            // all runways are currently full, can't satisfy the landing request. 
            return false;
        }
        
        prunway->land_request(flight_id);
        pflight->set_runway_id(runway_id);

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

