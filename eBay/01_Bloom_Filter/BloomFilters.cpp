#include "BloomFilters.hpp"

BloomFilters::BloomFilters() {
    // init mHash
    // return index of bit index in mBset
}

void BloomFilters::add(std::string s) {
    for (auto& x:mHash) {
        size_t i = x((const unsigned char*)s.c_str(), s.length(), 1)%M;
        mBset[i] = 1;
    }
}

bool BloomFilters::test(std::string s) {
    for (auto& x:mHash) {
        size_t i = x((const unsigned char*)s.c_str(), s.length(), 1)%M;
        if (!mBset.test(i))
            return false;
    }
    return true;
}
