#include <iostream>
using namespace std;

template <typename T> 
class Singleton {
public:
    static T* getInstance();
protected:
    Singleton() {};
};

template <typename T> T* Singleton<T>::getInstance() {
    static T _instance;
    return &_instance;
}

class Widget: private Singleton<Widget> {
public:
    using Singleton<Widget>::getInstance;
    void foo() { cout << "Widget::foo()" << endl; };
protected:
    Widget() {};
};

int main() {
    Widget* p = Widget::getInstance();
    p->foo();
    //Widget* p2 = new Widget(); // <<< second instance, how to fail this???
    return 1;
}
