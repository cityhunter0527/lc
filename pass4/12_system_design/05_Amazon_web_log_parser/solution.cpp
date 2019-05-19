/* 
 * amazon web log per week 
   generate 7 web log file (1 file per day)

log:
   url, user id, request time ...
   generate a list of user ids that visit amazon every day.

   plus:
   * web log is too large to fit in memory (billions of users)
   * map <key, value> can also not be fit in memory.
*/

#include <iostream>
#include <fstream>
using namespace std;

class weblogparser {
public:
    // how to persist map<key, value> to disk.
    // how to persist database to disk
    bool parselog(string logfilepath, string& outputfilepath) {
             
    }
};

int main() {
    return 1;
}


