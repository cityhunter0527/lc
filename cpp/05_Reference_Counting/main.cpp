#include <iostream>
#include "refCounter.hxx"
using namespace std;

class Tank : private Counter<Tank> {
public:
    using Counter<Tank>::howmany; // make "howmany" public
};

int main() {
    Tank *p = new Tank;
    Tank t = *p;
    cout << Tank::howmany() << endl;
    delete p;
    cout << Tank::howmany() << endl;
    return 1;
}
