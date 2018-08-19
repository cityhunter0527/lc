/*
 *Input: City Blocks: lengh, width.
 * Amazon Locker Location: X: [x1,x2,x3 ...], Y: [y1,y2,y3...]
 Output: 2d array, each element is the closest length to amazon locker. Note the length
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
vector<vector<int>> getClosestBlockLenghToLocker(int cityLength, int cityWidth, vector<int> LockerXCoordination, vector<int> LockerYCoordination) {
}
 * */

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
private:
    size_t dist(const pair<int, int>& p1, const pair<int, int>& p2) {
        return abs(p1.first-p2.first) + abs(p1.second - p2.second);
    }
public:
    vector<vector<int>> getClosestBlockLengthToLocker(int cityLength, int cityWidth, vector<int> LockerXCoordination, vector<int> LockerYCoordination) {
        vector<vector<int>> res(cityWidth, vector<int>(cityLength));
        for (size_t i = 0; i < cityWidth; i++) {
            for (size_t j = 0; j < cityLength; j++) {
                // calculate closest dist of res[i][j] to locker
                size_t min = INT_MAX;
                for (size_t k = 0; k < LockerXCoordination.size(); k++) {
                    size_t l = dist(make_pair(i,j), make_pair(LockerXCoordination[k]-1, LockerYCoordination[k]-1));
                    if (l < min) {
                        min = l;
                    }
                }
                res[i][j] = min;
            }
        }
        return res;
    }
};

int main() {
    Solution s;
    vector<int> x = {1};
    vector<int> y = {1};
    vector<vector<int>> o = s.getClosestBlockLengthToLocker(3,5,x,y);
    for (auto x : o) {
        for (auto y:x) {
            cout << y << ", ";
        }
        cout << endl;
    }
    return 1;
}
