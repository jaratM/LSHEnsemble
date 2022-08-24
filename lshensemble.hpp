#ifndef lshensemble
#define lshensemble

#include "utils.hpp"

class Lshforest;
class LshForestArray;
class LshEnsemble{
    public:
        std::vector<Partition> partitions;
        // std::vector<Lshforest> lshes;
        std::vector<LshForestArray> lshes;
        int maxK;
        int numHash;
        std::unordered_map<std::string, Param> cmap;
        void add(std::string const&, uint64_t *, int);
        void prepare(std::string, uint64_t *, int);
        void index();
        queryResult query(uint64_t *, int, double);
        std::vector<std::string> queryWithParam(uint64_t *, Param *);
        void computeParams(Param *,int, double);
        ~LshEnsemble();
};

LshEnsemble* NewLshEnsemblePlus(std::vector<Partition>, int, int, int);

// LshEnsemble* NewLshEnsemble(Partition [], int, int);



#endif 