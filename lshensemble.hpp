#ifndef lshensemble
#define lshensemble

#include "lsharray.hpp"

class LshEnsemble{
    
    public:
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version){
                ar & maxK;
                ar & numHash;
                ar & partition;
                ar & lshes;
                ar & cmap;
            }
        Partition partition;
        LshForestArray lshes;
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
        std::vector<std::string> queryWithParam(uint64_t *, Param const&);
        Param computeParams(int, double);
        
        ~LshEnsemble();
};

// LshEnsemble* NewLshEnsemble(Partition [], int, int);

LshEnsemble* NewLshEnsemblePlus(Partition , int, int, int);
// LshForestArray* NewLshForestArray(int, int);



#endif 