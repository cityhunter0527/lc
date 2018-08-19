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
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <algorithm>
using namespace std;
bool sort_by_second(const pair<string, int>& x1, const pair<string, int>& x2) {
    return (x1.second > x2.second);
}

class Solution {
private:
    // used to quickly detect whether a given course is already in the list of user's course list
    unordered_map<string, unordered_set<string>>  user_course_track_;
    // used to quickly detect whether a given user is already a friend of another;
    unordered_map<string, unordered_set<string>>  user_friend_track_;
    // user's course list;
    unordered_map<string, vector<string>>       user_course_map_;
    // user's friend list;
    unordered_map<string, vector<string>>       user_friend_map_;
    unordered_set<string>               social_;            // social friends with predefined 1st and 2nd level;
    vector<pair<string, int>>           course_freq_;   // first: course name, second: frequency
    unordered_map<string, int>          course_index_; // key: course name to index in course_freq_

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
    // TODO: what about social fiends extend to 3rd level fried?
    // Can this program scale, or further more, the level of friend is input var?
    vector<string> getRecomendedCourseList (string user) {
        // populate social network
        // first level friends and their courses
        vector<string> friendL1 = getDirectFriends(user);
        for (const auto& x : friendL1) {
            social_.insert(x);
            update_course_for_user(x);
        }
        // 2nd level friends
        for (const auto& x : friendL1) {
            for (const auto& y : getDirectFriends(x)) {
                if (social_.find(y) != social_.end()) {
                    // this is a new 2nd level fried
                    social_.insert(y);
                    update_course_for_user(y);
                }
                // for a known friend, she/he will always get the chance to visit his/her course list;
            }
        }
        std::sort(course_freq_.begin(), course_freq_.end(), sort_by_second);
        vector<string> res;
        for (auto x:course_freq_) {
            res.emplace_back(x.first);
        }
        return res;
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

    void add_friend(string user1, string user2) {
        if (user1 == user2) return;
        if (user_friend_track_[user1].find(user2) == user_friend_track_[user1].end()) {
            user_friend_track_[user1].insert(user2);
            user_friend_map_[user1].emplace_back(user2);
        }
        // user2 is already a friend of user1, skip;
        if (user_friend_track_[user2].find(user1) == user_friend_track_[user2].end()) {
            user_friend_track_[user2].insert(user1);
            user_friend_map_[user2].emplace_back(user1);
        }
        // user1 is already a friend of user2, skip;
    }
};
/*
Jon ------ Ann ---------Tom --------- Joey
|         |
|         |
Lee ----- Mary  ------ Jerry
 */
int main() {
    Solution s;
    s.add_friend("Jon", "Ann");
    s.add_friend("Ann", "Tom");
    s.add_friend("Tom", "Joey");
    s.add_friend("Jon", "Lee");
    s.add_friend("Lee", "Mary");
    s.add_friend("Ann", "Mary");
    s.add_friend("Mary", "Jerry");

    s.add_course("Jon", vector<string>{"Math", "Physics", "Arts"});
    s.add_course("Ann", vector<string>{"Math", "Chemistry", "Gym"});
    s.add_course("Tom", vector<string>{"Math", "Data_Structure", "Gym"});
    s.add_course("Lee", vector<string>{"Math", "Operating_System", "Arts"});
    s.add_course("Mary", vector<string>{"Operating_System", "Algorithms", "Arts"});
    s.add_course("Jerry", vector<string>{"Graph", "Painting", "Algoithms"});
    s.add_course("Joey", vector<string>{"Pingpong", "Swim", "Boxing"});

    string user  = "Jon";
    vector<string> o = s.getRecomendedCourseList("Jon");

    cout << "User: " << user <<"'s recomended course list: " << endl;
    for (auto x: o) {
        cout << x << endl;
    }
    return 1;
}
