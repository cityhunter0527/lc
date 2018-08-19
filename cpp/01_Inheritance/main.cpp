/*
 * public inheritance: is kind of 
 * protected inheritance: 
 * private inheritance: has a 
 *
 * Difference between protected and private inheritance:
 * 1. protected: 
 *      public and protected becomes protected in derived class.
 *      base class's public and protected mem fun could still be passed down(called) to derived class's derived class (since they are protected).
 * 2. private
 *      public and protected becomes private in derived class.
 *      base class's public and protected mem fun could NOT be passed down(called) to derived class's derived class (since they are private).
 * */

#include <iostream>
using namespace std;

class A { 
public:
    void A_f() { cout << "A::A_f()" << endl;}
protected:
    void A_g() { cout << "A::A_g()" << endl;}
private:
    void A_h() { cout << "A::A_h()" << endl;}
};

class B : public A {
public:
    void B_f() { 
        A_f();   // <<< good, A_f is public in B;
        A_g();   // <<< good, A_g is protected in B;
        //A_h(); // <<< private member func of base class could NOT be called.
        cout << "B::B_f()" << endl;
    }
};

class C : protected A { // <<< pub and protected member func of A becomes protected in C, 
public:                 // <<< meaning B's instance could call A_f(), but C's instance could NOT.
    void C_f() { 
        A_f();  // <<< good, A_f becomes protected in C; But C's instance couldn't call A_f(); 
        A_g();  // <<< good, A_g is still protected in C
        //A_h(); 
        cout << "C::C_f()" << endl;
    }
};

class D : private A {
public: 
    void D_f() {
        A_f(); // <<< good to call public mem func in A, A_f becomes private in D; 
               // <<< But D's instance couldn't call A's public mem func.
        A_g(); // <<< good to call protected mem func in A, A_g becomes private in D;

    }
};

int main() {
    class B b;
    b.A_f(); // <<< good
    //b.A_g(); // <<< fail, since A_g is protected 
    class C c;
    //c.A_f(); // <<< fail since A_f() is protected 
    c.C_f(); // <<< good, since C_f() is public 

    class A* pA = new class B; // <<< good
    class A* pAC = new class C; // <<< fail, since A's constructure(protected in C) is inaccessible from outside of C;
    class A* pAD = new class D; // <<< fail, since A's constructure(private in C) is inaccessible from outside of C;
    return 1;
}
