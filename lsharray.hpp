#ifndef lsharray
#define lsharray
#include "lshforest.hpp"

class LshForestArray
{
    public:
        int maxk;
        int numHash;
        Lshforest *array;
        LshForestArray();
        LshForestArray(int maxk, int numhash, Lshforest *array);
        void add(std::string, uint32_t *sig);
        void index();
        std::vector<std::string> query(uint32_t *, int, int);
        Param optimalKL(int, int, double);

};


#endif
