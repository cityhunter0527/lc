#include "ConsistHash.hpp"
#include <map>
using namespace std;

int main() {
    ConsistHash h;
    h.init();
    vector<string> nodes = {
        "10.1.1.11",
        "10.1.1.12",
        "10.1.1.13",
        "10.1.1.14",
        "10.1.1.15",
        "10.1.1.16"};
    
    for (auto x:nodes) {
        h.addNode(x, 8);
    }

    map<string, int> m;
    for (int i = 0; i < 1000; i++) {
        string x = "www.facebook00" + to_string(i) + ".com";
        ConsistHash::Node* pNode = h.lookup(x);
        //cout << pNode->iden << " : " << x << endl;
        m[pNode->iden]++;
    }

    for (auto x:m)
        cout << x.first << ": " << x.second << endl;

    return 0;
}
