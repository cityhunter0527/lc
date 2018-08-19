#include <iostream>
using namespace std;


class Base {
public:
    Base() {}
    virtual ~Base() {}
};

class Derived : public Base {
public:
    Derived() {}
    ~Derived() {}
};
int main() {
    Derived *d = new Derived;
    Base* pb; 
    Derived* pd;

    // Derived to base;
    if (pb = dynamic_cast<Base*> (d))
        cout << "successful cast" << endl;
    else 
        cout << "failed cast" << endl;

    // Derived to Derived;
    if (pd = dynamic_cast<Derived*> (d))
        cout << "successful cast" << endl;
    else 
        cout << "failed cast" << endl;

    Base* b = new Base();
    // Base to Base
    if (pb = dynamic_cast<Base*>(b))
        cout << "successful cast" << endl;
    else 
        cout << "failed cast" << endl;

    // Base to Derived
    if (pd = dynamic_cast<Derived*>(b))
        cout << "successful cast" << endl;
    else 
        cout << "failed cast" << endl;

    return 1;
}
