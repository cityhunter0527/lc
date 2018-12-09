/**
Question 1:
Input: City Blocks: lengh, width.
Amazon Lockes Location: X: [x1,x2,x3 ...], Y: [y1,y2,y3...]
Output: 2d array, each element is the closest length to amazon locker. Note the length 不能走斜线。

Example1:
Input:
3
5
[1]
[1]

Output:
012
123
234
345
567

Example2
Input:
5
5
[1, 2]
[2, 4]

Output:
*
* */ 

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cmath>

class Solution {
private:
    int dist(int x1, int y1, int x2, int y2) {
        return std::abs(x1-x2) + std::abs(y1-y2);
    }
public:
    std::vector<std::vector<int>> get_closest_blk_len_to_locker(int city_len, int city_width, std::vector<int> locker_x_coord, std::vector<int> locker_y_coord) {
        std::vector<std::vector<int>> res(city_width, std::vector<int>(city_len));
        std::vector<std::pair<int, int>>   coords;
        
        for (std::uint32_t i = 0; i < locker_x_coord.size(); i++) {
            coords.push_back(std::make_pair(locker_x_coord[i], locker_y_coord[i]));
        }

        std::sort(coords.begin(), coords.end());

        int closest_len; 
        for (std::uint32_t x = 0; x < city_len; x++) {
            for (std::uint32_t y = 0; y < city_width; y++) {
                closest_len = INT_MAX;
                for (std::uint32_t k = 0; k < coords.size(); k++) {
                    // lockers' index starts from [1][1]
                    std::uint64_t l = dist(x+1,y+1, coords[k].first, coords[k].second);
                    if (closest_len > l)
                        closest_len = l;
                }
                res[x][y] = closest_len;
            }
        }
        return res;
    }
};

int main () {
    Solution s;
    std::vector<int> x_coords {1};
    std::vector<int> y_coords {1};
    std::uint32_t len = 3, width = 5;
    std::vector<std::vector<int>> out;
    out = s.get_closest_blk_len_to_locker(len, width, x_coords, y_coords);   
    for (auto& x : out) {
        for (auto& y : x) {
            std::cout << y << " ";
        }
        std::cout << "\n";
    }
    return 0;
}
