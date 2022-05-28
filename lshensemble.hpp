#ifndef lshensemble
#define lshensemble

#include "utils.hpp"

// using Keys =  std::vector<std::string> ;
// using initHashTable = std::unordered_map<std::string, Keys> ;
constexpr double integrationPrecision = 0.01;



struct Param
{
   int k{};
   int l{};
};

struct Partition{
    int lower{};
    int upper{};
};

struct Entry {
	std::string hashKey;
    std::string key;
};
typedef std::vector<Entry> hashTable;

class Lshforest;
class LshForestArray;
class LshEnsemble{
    public:
        std::vector<Partition> partitions;
        std::vector<LshForestArray> lshes;
        int maxK;
        int numHash;
        std::unordered_map<std::string, Param> cmap;
        void add(std::string const&, uint64_t *, int);
        void prepare(std::string, uint64_t *, int);
        void index();
        queryResult query(uint64_t *, int, double);
        /**
         * @brief 
         * 
         * @return std::vector<std::string> 
         */
        std::vector<std::string> queryWithParam(uint64_t *, Param *);
        void computeParams(Param *,int, double);
        ~LshEnsemble();
};

// LshEnsemble* NewLshEnsemble(Partition [], int, int);
bool domainRecordSorter(domainRecord const&, domainRecord const&);
int binarySearch(hashTable const&, int, int, std::string const &);
bool entrySorter(Entry const&, Entry const&);
bool rawDomainSorter(rawDomain const&, rawDomain const&);
LshEnsemble* NewLshEnsemblePlus(std::vector<Partition>, int, int, int);
std::string cashKey(int x, int q, double t);
// LshForestArray* NewLshForestArray(int, int);



#endif 