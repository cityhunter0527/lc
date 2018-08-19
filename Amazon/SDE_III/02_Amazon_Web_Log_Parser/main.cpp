/* 
 * Amazon Web log Per week 
   Generate 7 web log file (1 file per day)

   log;
   URL, User ID, Request Time ...

   Generate a list of User IDs that visit amazon every day.

   PLUS:
   * Web log is too large to fit in memory (billions of users)
   * map <key, value> can also not be fit in memory.
*/

#include <iostream>
#include <fstream>
using namespace std;

class WebLogParser {
public:
    // how to persist map<key, value> to disk.
    // how to persist database to disk
    bool parseLog(string logFilePath, string& outputFilePath) {
             
    }
};

int main() {
    return 1;
}




