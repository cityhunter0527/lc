//
// Created by Kuang, Yaming on 2018/8/18.
//
/*
Question 2
Get recommended course list for an Amazon user.
Each amazon user has several direct friends, and so on.
Social network means 2 level friends. 3rd level friends won't be considered.
For example: Jon's social network will be: Ann, Lee, Mary, Tom and Jerry.  Joey is not Jon's social network.
Jon ------ Ann ---------Tom --------- Joey
 |         |
 |         |
 Lee ----- Mary  ------ Jerry
Every user will learn several courses and you will be given below two helper functions to return direct user list and course list.
    vector<string> getDirectFriends(string user);
    vector<string> getCourseList(string user);

For any given user, pls recommend him/her the course list that his/her social network
is also taken and sort with popularity (e.g. the course that most friends have taken
should be recommended firstly). The course that this user has already taken should
not be recommended.
 */
#include <vector>
#include <string>
#include <cassert>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <random>
#include <iostream>
#include <algorithm>
using namespace std;
bool sort_by_second(const pair<string, int>& x1, const pair<string, int>& x2) {
    return (x1.second > x2.second);
}

class Solution {
private:
    // just needed for unit test: quickly detect whether a given course is already in user's course list
    unordered_map<string, unordered_set<string>>    user_course_track_;
    // just needed for unit test: quickly detect whether a given user is already a friend of another;
    unordered_map<string, unordered_set<string>>    user_friend_track_;
    // just needed for unit test: keep track of all users
    set<string>                                     all_users_;

    // user's course list;
    unordered_map<string, vector<string>>       user_course_map_;
    // user's friend list;
    unordered_map<string, vector<string>>       user_friend_map_;
    vector<pair<string, int>>                   course_freq_;  // first: course name, second: frequency
    unordered_map<string, int>                  course_index_; // key: course name value: vector index in course_freq_

    void update_course_for_user (string user) {
        // get this friend's course list;
        vector<string> clist = getCourseList(user);
        for (auto& y : clist) {
            if (course_index_.find(y) == course_index_.end()) {
                // this is a new course
                // push this new course with frequency set to 1;
                course_freq_.emplace_back(make_pair(y, 1));
                // set this course's index in map;
                course_index_[y] = course_freq_.size() - 1;
            } else {
                // this is an a known course
                course_freq_[course_index_[y]].second++;
            }
        }
    }

public:
    vector<string> getDirectFriends(string user) {
        return user_friend_map_[user];
    }
    vector<string> getCourseList(string user) {
        return user_course_map_[user];
    }
    
    vector<string> get_social_friends(string user, size_t social_level) {
        vector<vector<string>> friends_list(social_level+1);
        friends_list[0].push_back(user);
        set<string>            social;            // social friends with predefined 1st and 2nd level;

        for (size_t i = 0; i < social_level; i++) {
            for (const auto& x : friends_list[i]) {
                vector<string> tmp = getDirectFriends(x);
                for (const auto& y: tmp) {
                    if (y != user && social.find(y) == social.end()) {
                        // a new friend
                        social.insert(y);
                        // push to next social level friend list
                        friends_list[i+1].emplace_back(y);
                    }
                }
            }
        }
        vector<string> res;
        for (const auto& x : social) {
            res.emplace_back(x);
        }
        return res;
    }

    // TODO: what about social fiends extend to 3rd level fried?
    // Can this program scale, or further more, the level of friend is input var?
    vector<pair<string, int>> getRecomendedCourseList (string user, size_t social_level = 2) {
        // populate social network
        // first level friends and their courses
        vector<string> social_friends = get_social_friends(user, social_level);
        for (const auto& x : social_friends) {
            assert(x != user);
            update_course_for_user(x);
        }

        // sort based on course frequency
        std::sort(course_freq_.begin(), course_freq_.end(), sort_by_second);

        return course_freq_;
    }

    void add_course(string user, vector<string> course_list) {
        for (auto x:course_list) {
            add_course(user, x);
        }
    }

    void add_course(string user, string course_name) {
        if (user_course_track_[user].find(course_name) == user_course_track_[user].end()) {
            user_course_map_[user].emplace_back(course_name);
            user_course_track_[user].insert(course_name);
        }
        // course already added for this user, just skip
    }

    void add_friend(string user, vector<string> user_list) {
        for (auto x:user_list) {
            add_friend(user, x);
        }
    }

    vector<string> get_all_users() {
        vector<string> res;
        for (const auto& x : all_users_)
            res.emplace_back(x);
        return res;
    }

    void add_friend(string user1, string user2) {
        if (user1 == user2) return;

        if (all_users_.find(user1) == all_users_.end())
            all_users_.insert(user1);
        if (all_users_.find(user2) == all_users_.end())
            all_users_.insert(user2);

        if (user_friend_track_[user1].find(user2) == user_friend_track_[user1].end()) {
            user_friend_track_[user1].insert(user2);
            user_friend_map_[user1].emplace_back(user2);
        }
        // else: user2 is already a friend of user1, skip;
        
        if (user_friend_track_[user2].find(user1) == user_friend_track_[user2].end()) {
            user_friend_track_[user2].insert(user1);
            user_friend_map_[user2].emplace_back(user1);
        }
        // else :user1 is already a friend of user2, skip;
    }

    string get_random_user() {
        vector<string> all_user = get_all_users();
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> dist(0.0, all_user.size()-1.0);
        return all_user[static_cast<int>(dist(mt))];
    }

    // unit test
    vector<string> get_random_course_list(vector<string>& c_list) {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> dist(1.0, static_cast<double>(c_list.size()));
        
        int num_course = static_cast<int>(dist(mt));
        vector<string> res;
        for (size_t i = 0; i < num_course; i++) {
            res.emplace_back(c_list[static_cast<int>(dist(mt))-1]);
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
|           |
|           |
Jacky ---- Stanley
|
|
Danny ---- Forest
 */
int main(int argc, char* argv[]) {
    Solution s;
    
    s.add_friend("Jon", "Ann");
    s.add_friend("Ann", "Tom");
    s.add_friend("Tom", "Joey");
    s.add_friend("Jon", "Lee");
    s.add_friend("Lee", "Mary");
    s.add_friend("Ann", "Mary");
    s.add_friend("Mary", "Jerry");
    s.add_friend("Jerry", "Monica");
    s.add_friend("Lee", "Jackey");
    s.add_friend("Jacky", "Stanley");
    s.add_friend("Mary", "Stanley");
    s.add_friend("Jacky", "Danny");
    s.add_friend("Forest", "Danny");
    
    vector<string> all_users = s.get_all_users();
    cout << "All Users: ";
    for (auto x: all_users)
        cout << x << ", ";
    cout << endl;

    vector<string> course_list = {"Math", "Physics", "Arts", "Chemistry", "Gym", "Data_Structure", "Operating_System", "Machine_Learning", "Algorithms", "Graph", "Painting", "Swimming", "Boxing", "Tennis"};
    for (auto x:all_users) {
        vector<string> c = s.get_random_course_list(course_list);
        cout <<"Adding couse list for [" << x <<"], course : ";
        for (auto y:c) 
            cout << y << ", ";
        cout << endl;
        s.add_course(x, c);
    }
    
    string user  = s.get_random_user();
    cout << "User: " << user << endl;
    if (argc != 2) return 1;
    vector<pair<string, int>> o;
    o = s.getRecomendedCourseList(user, stoi(argv[1]));

    // 
    // User: Jon's recomended course list:
    // Math, Gym, Operating_System, Arts, Chemistry, Data_Structure, Algorithms,
    //
    cout << "User: " << user <<"'s recomended course list: " << endl;
    for (auto x: o) {
        cout << x.first << ": " << x.second << endl;
    }
    return 1;
}
