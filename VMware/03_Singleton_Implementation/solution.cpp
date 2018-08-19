/*
 * implement singleton pattern
 * */

class Singleton {
public:
    static Singleton* getInstance();
protected:
    Singleton(){};
private:
    static Singleton* _instance;
};

Singleton* Singleton::_instance = 0;
Singleton* Singleton::getInstance() {
    if (_instance == 0)
        _instance = new Singleton();
    return _instance;
}

int main() {
    return 1;
}
