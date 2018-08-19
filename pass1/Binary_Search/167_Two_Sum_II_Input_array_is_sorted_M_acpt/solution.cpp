/*
 * 167. Two Sum II - Input array is sorted
 * Given an array of integers that is already sorted in ascending order, 
 * find two numbers such that they add up to a specific target number.
 *
 * The function twoSum should return indices of the two numbers such that 
 * they add up to the target, where index1 must be less than index2. 
 * Please note that your returned answers (both index1 and index2) are not zero-based.
 *
 * You may assume that each input would have exactly one solution.
 *
 * Input: numbers={2, 7, 11, 15}, target=9
 * Output: index1=1, index2=2
 * */

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    // two pointers
    vector<int> twoSum3(vector<int>& numbers, int target) {
        int p1 = 0, p2 = numbers.size()-1;
        while (p1 < p2) {
            if (numbers[p1] + numbers[p2] < target) p1++;
            else if (numbers[p1] + numbers[p2] > target) p2--;
            else return vector<int>({p1+1, p2+1});
        }
        return vector<int>();
    }

    int binarySearch(vector<int>& nums, int l, int h, int target) {
        while (l < h) {
            int m = (l+h)/2;
            if (nums[m] < target)
                l = m + 1;
            else if (nums[m] > target)
                h = m - 1;
            else 
                return m;
        }
        return l;
    }
    // binary Search + two pointers
    vector<int> twoSum(vector<int>& numbers, int target) {
        int i = 0, n = numbers.size();
        int l = 0, h = n-1;
        while (l < h) {
            if (numbers[l] + numbers[h] < target) { 
                l = binarySearch(numbers, l+1, h-1, target - numbers[h]);   
            } else if (numbers[l] + numbers[h] > target) {
                h = binarySearch(numbers, l+1, h-1, target - numbers[l]);   
            } else {
                return vector<int>({l+1, h+1});
            }
        }
        return vector<int>();
    }
};

int main() {
    //vector<int> v = {2,7,11,15};
    vector<int> v = {1,2,3,4,4,9,56,78};
    Solution s;
    vector<int> o = s.twoSum(v, 8);
    for (auto x:o)
        cout << x << ",";
    cout << endl;
    return 1;
}
