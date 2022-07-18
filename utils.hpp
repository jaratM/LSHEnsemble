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


#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include <boost/archive/tmpdir.hpp>

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/unordered_map.hpp>

#include "probability.hpp"

using byte = uint8_t;

constexpr int NumHash {256};
constexpr int NumPart {32};
constexpr int MaxK {4};
constexpr int benchmarkSeed {42};

constexpr double integrationPrecision = 0.01;
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


struct Param
{
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version){
        ar & k;
        ar & l;
    }
    int k;
    int l;
};

struct Partition{
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version){
        ar & lower;
        ar & upper;
    }
    int lower;
    int upper;
};

struct Entry {
    template<class Archive>
        void serialize(Archive & ar, const unsigned int version){
            ar & hashKey;
            ar & key;
        }
	std::string hashKey;
    std::string key;
};
typedef std::vector<Entry> hashTable;

void outputQueryResults(std::vector<queryResult> const& results, std::string output_file_name);
bool domainRecordSorter(domainRecord const&, domainRecord const&);
int binarySearch(hashTable const&, int, int, std::string const &);
bool entrySorter(Entry const&, Entry const&);
bool rawDomainSorter(rawDomain const&, rawDomain const&);
std::string cashKey(int x, int q, double t);

// void outputDomainRecords(domainRecord *records, int size, std::string output_file_name);



#endif /* utils */
