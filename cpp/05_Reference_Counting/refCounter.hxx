
typedef unsigned long long ulong64;

template<class T>
class Counter {
public:
    Counter() { numCnt++; };
    Counter(const Counter& r) { numCnt++; }
    ~Counter() { numCnt--; }
    static ulong64 howmany() { return numCnt; }
private:
    static ulong64 numCnt;
};

template<class T> ulong64 Counter<T>::numCnt = 0;

