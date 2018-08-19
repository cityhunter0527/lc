#include <cassert>
#include <random>
#include <string>
#include <vector>
#include <cassert>
#include "BloomFilters.hpp"
#include "StringDetector.hpp"
#include <iomanip>  

int main() {
    const size_t numStr = M/4;
    FileWriter::doWrite("file1", numStr);
    FileWriter::doWrite("file2", numStr);
    FileWriter::doWrite("file3", numStr);
    FileWriter::doWrite("file4", numStr);
    FileWriter::doWrite("file5", numStr);
    FileWriter::doWrite("file6", numStr);
    FileWriter::doWrite("file7", numStr);
    FileWriter::doWrite("file8", numStr);
    
    StringDetector sd;
    sd.addFile("file1");
    sd.addFile("file2");
    sd.addFile("file3");
    sd.addFile("file4");
    sd.addFile("file5");
    sd.addFile("file6");
    sd.addFile("file7");
    sd.addFile("file8");

    // now test the saved sample string and assert they can be found in bloom filter 
    for (size_t i = 0; i < FileWriter::sample.size(); i++) {
        for (size_t j = 0; j < FileWriter::sample[i].size(); j++) {
            std::string fname;
            assert(sd.test(FileWriter::sample[i][j], fname));
            assert(fname == "file" + std::to_string(i+1));
        }
    }

    FileWriter::doWrite("false.txt", numStr);
    std::ifstream fin("false.txt");
    for (std::string line; std::getline(fin, line); ) {
        std::string fname;
        assert(sd.test(line, fname) == false);
    }
    
    // Note: false positive all could be larger than "numStr" because each single string
    // could be reported as false positive in multiple files.
    std::cout << "False positive All: " << sd.getFalsePositiveAll() << std::endl;
    for (size_t i = 1; i <= 8; i++) {
        std::string fname = "file" + std::to_string(i);
        size_t fp = sd.getFalsePositivePerFile(fname);
        std::cout << fname << ": " << std::setw(5) << fp << ", Rate: " << (float)fp/numStr << std::endl;
    }
    return 1;
}
