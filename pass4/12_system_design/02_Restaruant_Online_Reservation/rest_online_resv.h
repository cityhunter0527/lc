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
#include <iostream>
#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.

// boost::uuids::uuid uuid = boost::uuids::random_generator()();
// std::string uuid_str = boost::uuids::to_string(uuid);

class Customer {
private:
    std::string cell_phone; // also as uuid
    std::string email;
    std::deque<std::shared_ptrResvRecord>  m_records;
};

class ResvRecord {
public:
    ResvRecord(std::string record_id, std::string customer_uuid, std::string table_id, std::string start, std::string end)
        : m_record_id(record_id), m_resv_by_customer_uuid(customer_uuid), m_table_uuid(table_id), m_start_time(start), m_end_time(end) {}
    std::string get_customer() { return m_resv_by_customer_uuid; }
    std::string get_table() { return m_table_uuid; }

private:
    std::string m_record_id;
    std::string m_resv_by_customer_uuid; // cell_phone
    std::string m_table_uuid;
    std::string m_start_time;
    std::string m_end_time;
};

class Table {
private:
    bool conflit (std::string start1, std::string end1, std::string start2, std::string end2) {
    
    }
public:
    Table(std::string uuid, uint16_t size): m_uuid(uuid), m_size(size) {}

    bool reservable(std::string start, std::string end) { 
        for (auto& x : m_map_rec_uuid) {
            // if this requested start,end timeslot conflicts with any existig reservation record, return false;
            if (conflict(x.second->get_start(), x.second->get_end(), start, end)) 
                return false;
        }
        // otherwise return true;
        return true;
    }

    std::string make_resv(std::string customer_uuid, std::string start, std::string end) {
        // generate the record id;
        boost::uuids::uuid uuid = boost::uuids::random_generator()();
        std::string record_id_str = boost::uuids::to_string(uuid);
        // create ResvRecord instance and insert to map;
        m[record_id_str] = std::make_shared<ResvRecord>(record_id_str, customer_uuid, m_uuid, start, end);

        // return the record id;
        return record_id_str;
    }
    
    void cancel_resv_by_customer_id(std::string customer_id) {
        for (auto& x : m_map_rec_uuid) {
            if (x.second->get_customer() == customer_id) {
                m_map_rec_uuid.erase(x.first);
            }
        }
    }

    void cancel_resv_by_record_id(std::string record_id) {
        m_map_resv_id.erase(record_id);
    }

priavet:
    std::string         m_uuid;
    uint16_t            m_size;
    std::map<std::string, std::shared_ptr<ResvRecord>> m_map_rec_uuid; // record id to ResvRecord
};

#define INVALID_TABLE_SIZE 0xff

class ResvManager {
private:
    std::map<int, std::vector<std::string>>         m_map_table_size; // size to vector of tables uuids
    std::map<std::string, std::shared_ptr<Table>>   m_map_tables_id;  // uuid to table
    std::map<std::string, std::shared_ptr<Table>>   m_map_resv_id;    // resv uuid to table

public:
    void add_tables(std::vector<std::pair<int, int>> info) {
        for (auto& x : info) {
            add_table(x.first, x.second);
        }
    }

    void add_table(uint16_t size, uint32_t num_tables) {
        for (int i = 0; i < num_tables, i++) {
            boost::uuids::uuid table_uuid = boost::uuids::random_generator()();
            std::string table_uuid_str = boost::uuids::to_string(table_uuid);
            // map based on table size
            m_map_table_size[size].push_back(table_uuid_str);
            // map based on table uuid
            m_map_table_ids[table_uuid_str] = std::make_shared<Table>(table_uuid_str, size);
        }
    }

    void user_create(std::string cell_phone, std::string email) {
    
    }
    
    std::vector<std::string> list_avialble_tables(uint16_t num_customers, std::string start, std::string end) {
        std::vector<std::string> res;
        uint16_t table_size = get_table_size(num_customers);         
        if (table_size == INVALID_TABLE_SIZE) return res;

        for (auto& x : m_map_table_size[table_size]) {
            // if this table can be reserved, push it into the return value
            if (m_table_uuid[x]->reservable(start, end))
                res.push_back(x);
        }
        return res;
    }

    uint16_t get_table_size(uint16_t num_customers) {
        int table_size = INVALID_TABLE_SIZE;
        
        for (auto& x : m_map_table_size[table_size]) {
            if (x.first >= num_customers && x.first < table_size)
                table_size = x.first;
        }
        return table_size;
    }

    std::string make_resv(std::string customer_id, uint16_t num_customers, std::string start, std::string end) {
        uint16_t table_size = get_table_size(num_customers);   
        if (table_size == INVALID_TABLE_SIZE) 
            return nullptr;

        // for each table uuid in this table size
        for (auto& x : m_map_table_size[table_size]) {
            assert(m_table_uuid.find(x) != m_table_uuid.end());
            if (m_table_uuid[x]->reservable(start, end)) {
                std::string record_id = x.make_resv(customer_id, string, end);
                m_map_resv_id[record_id] = x;
                return record_id;
            }
        }

        // if no table is available, return false;
        return nullptr;
    }

    // cancel all the reservations for this customer on this table id;
    void cancel_resv(std::string customer_id, std::string table_id) {
        m_table_uuid[table_id].cancel_resv_by_customer_id(customer_id);
    }

    // cacel by reservation record id;
    void cancel_resv(std::string record_id) {
        // get table uuid based on reservation record_id
        std::string table_uuid = m_map_resv_id[record_id];
        // remove it from this table's instance
        m_table_uuid[table_uuid].cancel_resv_by_record_id(record_id);
        // remove it from resv id to table map
        m_map_resv_id.erase(record_id);
    }
};
