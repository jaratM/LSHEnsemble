#ifndef lshforest
#define lshforest
#include "lshensemble.hpp"
#include "probability.hpp"
class Lshforest
{
    public:
        int k;
        int l;
        int hashValueSize;
        std::vector<initHashTable> initHashTables;
        std::vector<hashTable> hashTables;
        HashKeyFunc hashKeyFunc;
        Lshforest();
        Lshforest(int k, int l, int hashValueSize);
        // ~Lshforest();
        void add(std::string, uint32_t *);
        void index();
        std::vector<std::string> query(uint32_t *, int, int);
        Param optimalKL(int, int, double);
};
#endif