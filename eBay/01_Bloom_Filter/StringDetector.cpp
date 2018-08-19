#include "StringDetector.hpp"

const std::string RandStringGen::mCharTable = {"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"};

std::vector<std::vector<std::string>> FileWriter::sample; 

bool StringDetector::addFile(std::string file) {
    if (mFileBFMap.find(file) != mFileBFMap.end()) 
        return true;  // file already added;
    // a new file
    std::ifstream fin(file.c_str());
    if (!fin.good()) return false; // file not exist;
    
    mFileBFMap[file] = new BloomFilters;
    // Read each line out of fin and add the string to its bloom filter
    for (std::string line; std::getline(fin, line); ) {
        mFileBFMap[file]->add(line);
    }
    return true;      
}

bool StringDetector::test(std::string s, std::string& file) {
    for (auto& x:mFileBFMap) {
        if (x.second->test(s)) {
            std::ifstream fin(x.first);
            for (std::string line; std::getline(fin, line); ) {
                if (s == line) {
                    file = x.first;
                    return true;
                }
            }
            mFalsePositive[x.first]++;
        }
    }
    return false;
}

size_t StringDetector::getFalsePositiveAll() {
    size_t sum = 0;
    for (auto& x:mFalsePositive) {
        sum += x.second;
    }
    return sum;
}
