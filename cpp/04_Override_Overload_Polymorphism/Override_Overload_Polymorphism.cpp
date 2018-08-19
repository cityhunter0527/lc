#include <iostream>
using namespace std;

class Animal {
public:
    void sound() { cout << "Animal::sound()" << endl; }
    void sound(int x) { cout << "Animal::sound(): " << x << endl; }
};

class Cat : public Animal {
public: 
    void sound() { cout << "Cat::meow" << endl; } // <<< override
    void sound(string str) { cout << "Cat::"<< str << endl; } // <<< overload
};

int main() {
    Cat c;
    c.sound();
    c.sound("I am Jerry.");
    //c.sound(13); // <<< Won't compile, no matching candidates.
}




