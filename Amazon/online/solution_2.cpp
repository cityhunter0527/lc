/*
 * Get recommendated course list for an Amazon user.
Each amazon user has several direct friends, and so on. 
Social network means 2 level friends. 3rd level friends won't be considered.
For example: Jon's social network will be: Ann, Lee, Mary, Tom and Jerry.  Joey is not Jon's social network.

Jon ------ Ann ---------Tom --------- Joey
  |         |
  |         |  
 Lee ----- Mary  ------ Jerry

Every user will learn serval couses and you will be given below two helper functions to return 
direct user list and course list.

For any given user, pls recommend him/her the course list that his/her social network is also 
taken and sort with popularity (e.g. the couse that most friends have taken should be recommended firstly).
The course that this user has already taken should not be recommended.
 * 
 * */

#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <vector>
#include <string>
#include <random>
#include <algorithm>

std::vector<std::string> user_list = {"Jon", "Ann", "Tom", "Joey", "Lee", "Mary", "Jerry", "Monica", "Jacky", "Stanley", "Danny", "Forest"};
std::vector<std::string> course_list = {"Math", "Physics", "Arts", "Chemistry", "Gym", "Data_Structure", "Operating_System", "Machine_Learning", "Algorithms", "Graph", "Painting", "Swimming", "Boxing", "Tennis"};

class Solution {
////////////////////////////////////////// Testing //////////////////////////////////////////
public:
    std::vector<std::string> get_random_course_list(bool no_dup = true) {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> dist(1.0, static_cast<double>(course_list.size()/2));
        std::vector<bool>             already_visited(course_list.size(), false);
        
        int num_course = static_cast<int>(dist(mt));
        std::vector<std::string> res;
        for (size_t i = 0; i < num_course; i++) {
            int d = static_cast<int>(dist(mt))-1;
            // if no duplicates are allowed
            if (no_dup && !already_visited[d]) {
                // if the course name has already been picked, skip this one and continue
                already_visited[d] = true;
                res.emplace_back(course_list[d]);
            }
        }
        return res;
    }
    // no check of duplicate course 
    void add_course(std::string user, std::string user_course_name) {
        m_course_map[user].push_back(user_course_name);
    }

    // no check of duplicate friend
    void add_friend(std::string user, std::string user_friend) {
        m_direct_friends_map[user].push_back(user_friend);
        m_direct_friends_map[user_friend].push_back(user);
    }
private:
    std::unordered_map<std::string, std::vector<std::string>>  m_course_map;   // user to cours list map
    std::unordered_map<std::string, std::vector<std::string>>  m_direct_friends_map;  // user to direct friends map
//////////////////////////////////////// End of Testing //////////////////////////////////////////
public:
    std::vector<std::string> get_direct_friends(std::string user) {
        return m_direct_friends_map[user];
    }
    std::vector<std::string> get_course_list(std::string user) {
        return m_course_map[user];
    }
    std::vector<std::string> get_remended_course_list(std::string user) {
        std::vector<std::string> res;
        std::unordered_set<std::string> social_network;
        
        // Get social friends for this user
        std::vector<std::string> direct = get_direct_friends(user);
        for (auto& x : direct) {
            assert (x != user);
            if (social_network.find(x) == social_network.end()) social_network.insert(x);

            auto d = get_direct_friends(x);
            for (auto& y : d) {
                if (y != user && social_network.find(y) == social_network.end()) social_network.insert(y);
            }
        }
        
        // Test
        std::cout << user << "'s social (2nd level) friends: [";
        for (auto& x : social_network) {
            std::cout << x << ", ";
        }
        std::cout << "]\n";

        std::map<std::string, std::uint32_t>    social_course;
        std::unordered_set<std::string>         cur_user_course_set;
        std::vector<std::string>                cur_user_course = get_course_list(user);
        
        for (auto& x : cur_user_course)  {
            // course list returned by get_course_list should be unique
            assert(cur_user_course_set.find(x) == cur_user_course_set.end());
            cur_user_course_set.insert(x);
        }

        // for every user in social network
        for (auto& x : social_network) {
            auto c = get_course_list(x);
            // for every course of social friend
            for (auto& y : c) {
                // if this course is not already in cur_user's course list, then add it
                if (cur_user_course_set.find(y) == cur_user_course_set.end()) {
                    if (social_course.find(y) == social_course.end())
                        social_course[y] = 1;
                    else
                        social_course[y]++;
                }
            }
        }

        // now we collected all the social course lists and their number of occurencies in "social_course";
        std::vector<std::pair<std::uint32_t, std::string>> course_list_vec;
        for (auto& x : social_course) {
            course_list_vec.push_back(std::make_pair(x.second, x.first));
        }

        std::sort(course_list_vec.begin(), course_list_vec.end());

        for (auto& x : course_list_vec) {
            res.push_back(x.second);
        }

        return res;
    }
};
/*
 *     
Jon ------ Ann ---------Tom --------- Joey
|          |
|          |
Lee ----- Mary  ------ Jerry -------- Monica
|          |
|          |
Jacky ---- Stanley
|
|
Danny ---- Forest
 */


int main() {
    std::cout << "\n======================= Start ========================\n";
    Solution s;
    
    s.add_friend("Jon", "Ann");
    s.add_friend("Ann", "Tom");
    s.add_friend("Tom", "Joey");
    s.add_friend("Jon", "Lee");
    s.add_friend("Lee", "Mary");
    s.add_friend("Ann", "Mary");
    s.add_friend("Mary", "Jerry");
    s.add_friend("Jerry", "Monica");
    s.add_friend("Lee", "Jacky");
    s.add_friend("Jacky", "Stanley");
    s.add_friend("Mary", "Stanley");
    s.add_friend("Jacky", "Danny");
    s.add_friend("Forest", "Danny");
    
    for (auto& x : user_list) {
        std::vector<std::string> random_course_list = s.get_random_course_list();
        std::cout << x << "'s registered course: [";
        for (auto& y : random_course_list) {
            std::cout << y << ", ";
            s.add_course(x, y);
        }
        std::cout << "]\n";
    }
    
    std::cout << "\n======================= Result ========================\n";
    for (auto& x : user_list) {
        std::vector<std::string> out = s.get_remended_course_list(x);
        std::cout << x << "'s remended course: [";
        for (auto& y : out) {
            std::cout << y << ", ";
        }
        std::cout << "]\n";
        std::cout << "++++++++++++++++++++++++++++++++++++++++++\n";
    }
    return 0;
}

