#include <iostream>
using namespace std;

class A0 {
public:
    A0() {cout << "Ctor of A0" << endl; };
    virtual ~A0() {cout << "Dtor of A0" << endl; };
};

class A { 
public:
    A() {cout << "Ctor of A" << endl; };
    virtual ~A() {cout << "Dtor of A" << endl; };
};

class B : public A {
public:
    B() {cout << "Ctor of B" << endl; };
    virtual ~B() {cout << "Dtor of B" << endl; };
};

class C : public B {
public:
    C() {cout << "Ctor of C" << endl; };
    ~C() {cout << "Dtor of C" << endl; };
};

class D : public A, public A0 {
public:
    D() {cout << "Ctor of D" << endl; };
    ~D() {cout << "Dtor of D" << endl; };
};
int main() {
    //B b; // <<< A, B , ~B, ~A
    //D d; // <<< A, A0, D, ~D, ~A0, ~A
    A* pA = new D; // <<< A, A0, D
    delete pA; // <<< ~D, ~A0, ~A

    //A* pa = new B;
    //delete pa;
    return 1;
}
