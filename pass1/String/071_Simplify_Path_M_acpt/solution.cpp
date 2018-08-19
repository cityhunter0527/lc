/*
 * 71. Simplify Path
 *
 * Given an absolute path for a file (Unix-style), simplify it.
 *
 * For example,
 * path = "/home/", => "/home"
 * path = "/a/./b/../../c/", => "/c"
 *
 * Corner Cases:
 *   Did you consider the case where path = "/../"?
 *   In this case, you should return "/".
 *   Another corner case is the path might contain multiple slashes '/' together, such as "/home//foo/".
 *   In this case, you should ignore redundant slashes and return "/home/foo".
 * */

#include <iostream>
#include <string>
#include <stack>
using namespace std;

class Solution {
public:
    string simplifyPath(string path) {
        stack<string> s;
        string res;
        int i = 0, len = path.length();
        string tmp;
        while (i < len) {
            while (path[i] == '/' && i<len) i++;
            while (path[i] != '/' && i<len) tmp.push_back(path[i++]);
            if (tmp.compare("..") == 0 ) {
                if (!s.empty())
                    s.pop();
            } else if (tmp.compare(".") != 0 && !tmp.empty())
                s.push(tmp);
            tmp.clear();
        } 
        // populate res;
        if (s.empty()) {
            res.push_back('/');
            return res;
        }
        while (!s.empty()){
            res.insert(0, s.top());
            res.insert(0, 1, '/');
            s.pop();
        }
        return res;
    }
};

int main() {
    string path = "/a/./b/../../c/";
    //path = "/home//foo/";
    Solution s;
    string res = s.simplifyPath(path);
    cout << res << endl;
    return 1;
}
