#include <iostream>
using namespace std;

class Point2d {
public: 
    Point2d() {}
    virtual ~Point2d() {}
    virtual void foo() {cout << "Point2d::foo()" << endl;}
public:
    float _x = 333, _y = 444;
};

class Vertex : public virtual Point2d {
public:
    Vertex() {}
    virtual ~Vertex() {}
    virtual void foo() {cout << "Vertex::foo()" << endl;}
public:
    Vertex *next;
};

class Point3d : public virtual Point2d {
public:
    Point3d() {}
    virtual ~Point3d() {}
    virtual void foo() {cout << "Point3d::foo()" << endl;} 
public:
    float _z = 222;
};

class Vertex3d : public Vertex, public Point3d {
public:
    virtual void foo() { cout << "Vertex3d::foo()" << endl;}
public:
    float mumble = 111;
};

int main() {
    Vertex3d d;
    Point2d* p2d = &d;
    Point3d* p3d = &d;
    Vertex* pVtx = &d;
    cout << &d << endl;
    cout << p2d << endl;
    cout << p3d << endl;
    cout << pVtx << endl;
    return 1;
}
