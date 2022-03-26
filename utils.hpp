#ifndef utils
#define utils

#include <algorithm>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <cctype> 
#include <stdlib.h>
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <functional>



constexpr int numHash {256};
constexpr int numPart {32};
constexpr int maxK {4};
constexpr int benchmarkSeed {42};

struct rawDomain
{
    std::map<std::string, bool> values;
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
    uint32_t *signatures;

};

void outputQueryResults(std::vector<queryResult> const& results, std::string output_file_name);
// void outputDomainRecords(domainRecord *records, int size, std::string output_file_name);



#endif /* utils */
