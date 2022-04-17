#ifndef lsharray
#define lsharray
#include "lshforest.hpp"

class LshForestArray
{
    public:
        int maxk;
        int numHash;
        std::vector<Lshforest> array;
        LshForestArray();
        LshForestArray(int maxk, int numhash);
        ~LshForestArray();
        void add(std::string, uint64_t *sig);
        void index();
        std::vector<std::string> query(uint64_t *, int, int);
        Param optimalKL(int, int, double);

};


#endif
