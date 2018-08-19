#include <iostream>
using namespace std;

class Base1 {
public:
    Base1() { cout << "Base1::Base1()" << endl;}
    virtual ~Base1() { cout << "Base1::~Base1()" << endl;}
    virtual void speakClearly() { cout << "Base1::speakClearly()" << endl;}
    virtual Base1* clone() const { cout << "Base1::clone()" << endl;}
protected:
    float data_Base1;
};

class Base2 {
public:
    Base2() {cout << "Base2::Base2()" << endl;}
    virtual ~Base2() {cout << "Base2::~Base2()" << endl;}
    virtual void mumble() {cout << "Base2::mumble()" << endl;}
    virtual Base2* clone() const {cout << "Base2::clone()" << endl;}
protected:
    float data_Base2;
};

class Derived : public Base1, public Base2 {
public: 
    Derived() {cout << "Derived::Derived()" << endl;}
    virtual ~Derived() {cout << "Derived::~Derived()" << endl;}
    virtual Derived* clone() const {cout << "Derived::clone()" << endl;}
protected:
    float data_Derived;
};

int main() {
    Base1* pB1 = new Derived();
    // pB1->mumble();  <<< Can't compile, Base1 don't have mumble
    pB1->clone(); // <<< Derived::Clone();
    
    Base2* pB2 = new Derived();
    pB2->mumble();    // <<< Base2::mumble()
    pB2->clone();  // <<< Derived::clone()

    Derived* pD = new Derived();
    pD->mumble();  // <<< Base2::mumble();
    pD->clone();   // <<< Derived::clone()
    delete pB1;
    delete pB2;
    delete pD;
    return 1;
}
