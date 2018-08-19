#ifndef __STRING_DETECTOR_H__
#define __STRING_DETECTOR_H__

#include "BloomFilters.hpp"
#include <fstream>
#include <map>
#include <random>

class StringDetector {
public:
    StringDetector() {}
    ~StringDetector() {}
    bool addFile(std::string file);
    bool test(std::string s, std::string& file);
    size_t getFalsePositivePerFile(std::string& s) { return mFalsePositive[s]; }
    size_t getFalsePositiveAll();
private:
    std::map<std::string, BloomFilters*>  mFileBFMap;
    std::map<std::string, size_t>         mFalsePositive;
};

class RandStringGen {
private:
    static const std::string mCharTable;
public:
    static std::string randomString(int len = 32) {
        static std::default_random_engine              e;
        static std::uniform_int_distribution<unsigned> u(0, mCharTable.length()-1);
        std::string ret;
        for (size_t i = 0; i < len; i++) {
            ret += mCharTable[u(e)];
        }
        return ret;
    }
};


class FileWriter {
public: 
    static void doWrite(std::string file, size_t numStrings) {
        std::ofstream fout(file);
        std::vector<std::string> v;
        static std::default_random_engine              e;
        static std::uniform_int_distribution<unsigned> u(8, 32);
        for (size_t i = 0; i < numStrings; i++) {
            std::string s = RandStringGen::randomString(u(e));
            fout << s << std::endl;
            // store first 5 string into sample;
            if (i < 5) 
                v.push_back(s);
        }
        sample.push_back(v);
    }
public:
    static std::vector<std::vector<std::string>> sample;
};
#endif
