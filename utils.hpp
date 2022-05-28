#ifndef utils
#define utils

#include <algorithm>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <cctype> 
#include <stdlib.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <functional>
#include <boost/format.hpp>
#include <boost/math/tools/precision.hpp>
#include <future>
#include <omp.h>
#include <chrono>
#include <map>



using byte = uint8_t;

constexpr int NumHash {256};
constexpr int NumPart {32};
constexpr int MaxK {4};
constexpr int benchmarkSeed {42};

struct rawDomain
{
    std::unordered_map<std::string, bool> values;
    std::string key;
};
struct queryResult{
    std::vector<std::string> candidates;
    std::string queryKey;
    double duration;
};

struct domainRecord
{
    std::string key;
    int size;
    uint64_t *signatures;

};
struct P_r{
    double p;
    double r;
};

// struct Key{
//     int x;
//     int size;
//     bool operator<(Key const& a) const { 
//         return (this->x < a.x && this->size < a.size);
//     }
// };

void outputQueryResults(std::vector<queryResult> const& results, std::string output_file_name);

// void outputDomainRecords(domainRecord *records, int size, std::string output_file_name);



#endif /* utils */
