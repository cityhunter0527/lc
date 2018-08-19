#include <iostream>
using namespace std;

class A0 {
public:
    A0() {cout << "Ctor of A0" << endl; };
    virtual ~A0() {cout << "Dtor of A0" << endl; };
    virtual void foo() { cout <<"A0::foo()" << endl;}
};

class A { 
public:
    A() {cout << "Ctor of A" << endl; }
    virtual ~A() {cout << "Dtor of A" << endl; }
    virtual void foo() { cout <<"A::foo()" << endl;}
};

class B : public A {
public:
    B() {cout << "Ctor of B" << endl; };
    virtual ~B() {cout << "Dtor of B" << endl; };
    void foo() { cout <<"B::foo()" << endl;}
};

class C : public B {
public:
    C() {cout << "Ctor of C" << endl; };
    ~C() {cout << "Dtor of C" << endl; };
    //void foo() { cout <<"C::foo()" << endl;}
};

class D : public A, public A0 {
public:
    D() {cout << "Ctor of D" << endl; };
    ~D() {cout << "Dtor of D" << endl; };
};
int main() {
#if 0
    A* pa = new B;
    pa->foo(); // B::foo()
    delete pa;

    A* pa2 = new C;
    pa2->foo(); // B::foo()
    delete pa2;
#endif
    A0* pa3 = new D;
    pa3->foo();  // A0::foo();
    delete pa3;
    return 1;
}
