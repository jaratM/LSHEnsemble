#ifndef lshensemble
#define lshensemble

#include "utils.hpp"

using HashKeyFunc = std::function<std::string(uint64_t *, int, int)> ;
using Keys =  std::vector<std::string> ;
using initHashTable = std::map<std::string, Keys> ;
HashKeyFunc hashKeyFuncGen(int);
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

struct Bucket {
	std::string hashKey;
    Keys keys;
};
typedef std::vector<Bucket> hashTable;

class Lshforest;
class LshForestArray;
struct LshEnsemble{
    public:
        Partition *partitions;
        std::vector<LshForestArray> lshes;
        int maxK;
        int numHash;
        std::map<std::string, Param> cmap;
        void add(std::string, uint64_t *, int);
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
int binarySearch(hashTable const&, int, std::string const &);
bool bucketSorter(Bucket const&, Bucket const&);
bool rawDomainSorter(rawDomain const&, rawDomain const&);
LshEnsemble* NewLshEnsemblePlus(Partition *, int, int);
std::string cashKey(int x, int q, double t);
// LshForestArray* NewLshForestArray(int, int);



#endif 