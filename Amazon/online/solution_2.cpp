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
#include <unordered_map>
#include <map>
#include <vector>
#include <string>

class Solution {
public:
    std::vector<std::string> get_direct_friends(std::string user) {
        std::vector<std::string> res;
        return res;
    }
    std::vector<std::string> get_course_list(std::string user) {
        std::vector<std::string> res;
        return res;
    }
    std::vector<std::string> get_remended_course_list(std::string user) {
        std::vector<std::string> res;
        std::unordered_set<std::string> social_network;
        
        std::vector<std::string> direct = get_direct_friends(user);
        for (auto& x : direct) {
            social_network.set(x);

            auto d = get_direct_friends(x);
            for (auto& y : d) {
                if (social_network.find(y) != social_network.end()) {
                    social_network.set(y);
                }
            }
        }

        std::map<std::string, std::uint32_t>    social_course;
        std::unordered_set<std::string>         cur_user_course_set;
        std::vector<std::string>                cur_user_course = get_course_list(user);
        
        for (auto& x : cur_user_course)  {
            // course list returned by get_course_list should be unique
            assert(cur_user_course_set.find(x) == cur_user_course_set.end())
            cur_user_course_set.set(x);
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
            course_list_vec.push_back(std::make_pir(x.second, x.first));
        }

        std::sort(course_list_vec.begin(), course_list_vec.end());

        for (auto& x : course_list_vec) {
            res.push_back(x);
        }

        return x;
    }
};

int main() {
    return 0;
}

