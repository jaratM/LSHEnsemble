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

#include "probability.hpp"



using byte = uint8_t;
constexpr double integrationPrecision { 0.01 };

constexpr int NumHash { 256 };
constexpr int NumPart { 32 };
constexpr int MaxK { 4 };
constexpr int benchmarkSeed { 42 };

struct Param
{
   int k;
   int l;
};

struct Partition{
    int lower;
    int upper;
};

struct Entry {
	std::string hashKey;
    std::string key;
};

typedef std::vector<Entry> hashTable;

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

void outputQueryResults(std::vector<queryResult> const& results, std::string output_file_name);
bool domainRecordSorter(domainRecord const&, domainRecord const&);
int binarySearch(hashTable const&, int, int, std::string const &);
bool entrySorter(Entry const&, Entry const&);
bool rawDomainSorter(rawDomain const&, rawDomain const&);
std::string cashKey(int x, int q, double t);



#endif /* utils */
