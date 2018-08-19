/*
 * Input:
 * A list of files, each file contains a set of strings separeated by white space.
 *
 * Assumptions:
 * 1. All strings in a single file could be loaded in memory the same time.
 * 2. All strings from all files could not be loaded in memory the same time.
 * 3. All strings are unique. No duplicated strings accross files.
 *
 * Output:
 * Given a string, return:
 * 1. false if this string does not exist
 * 2. true if string exists in one file and return the file name.
 * */
#ifndef __BLOOM_FILTERS_H__
#define __BLOOM_FILTERS_H__
#include <iostream>
#include <vector>
#include <bitset>
#include <stdint.h>

#include "fnv.hpp"
#include "bobjenkins.hpp"
#include "murmur3.hpp"

const unsigned long long M = 1024ULL;
const unsigned int K = 3;

typedef uint32_t (*BFHashFunc)(const uint8_t* buf, size_t len, uint32_t seed);

class BloomFilters {
private:
    // std::vector<bool>    mHash;
    std::vector<BFHashFunc> mHash {murmur3_32, fnv_32_buf, hashlittle};
    std::bitset<M>          mBset;
public:
    BloomFilters();
    void add(std::string str);
    bool test(std::string str);
};
#endif
