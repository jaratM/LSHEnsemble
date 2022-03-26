#ifndef lshensemble
#define lshensemble

#include "utils.hpp"

using HashKeyFunc = std::function<std::string(u_int32_t *, int, int)> ;
using Keys =  std::vector<std::string> ;
using initHashTable = std::map<std::string, Keys> ;
HashKeyFunc hashKeyFuncGen(int);
constexpr double integrationPrecision = 0.01;
using byte = unsigned char;



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

struct Key
{
    int x;
    int size;
    double threshold;
    bool operator<(const Key& a) const{
        return (a.size == size && a.x == x && threshold < a.threshold);
    };
};

// class Lsh{
//     public:
//         void add(std::string, uint32_t *);
//         void index();
//         std::vector<std::string> query(uint32_t *, int, int);
//         Param optimalKL(int, int, double);
// };
class Lshforest;
struct LshEnsemble{
    public:
        Partition *partitions;
        Lshforest *lshes;
        int maxK;
        int numHash;
        std::map<Key, Param> cmap;
        void add(std::string, uint32_t *, int);
        void prepare(std::string, uint32_t *, int);
        void index();
        queryResult query(uint32_t *, int, double);
        std::vector<std::string> queryWithParam(uint32_t *, Param *);
        void computeParams(Param *,int, double);
};

LshEnsemble* NewLshEnsemble(Partition [], int, int);
int bs(hashTable const&, int, std::string);
bool bucketSorter(Bucket const&, Bucket const&);
bool rawDomainSorter(rawDomain const&, rawDomain const&);
// LshEnsemble NewLshEnsemblePlus(Partition *, int, int);


#endif 