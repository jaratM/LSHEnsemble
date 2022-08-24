#ifndef lshforest
#define lshforest
#include "lshensemble.hpp"



class Lshforest
{
    public:
        int k;
        int l;
        int hashValueSize;
        int numIndexedKeys;
        std::vector<hashTable> hashTables;
        Lshforest();
        Lshforest(int k, int l, int hashValueSize, int numIndexedKeys);
        ~Lshforest();
        void add(std::string const&, uint64_t *);
        void index();
        std::vector<std::string> query(uint64_t *, int, int);
        Param optimalKL(int, int, double);
        std::string HashKeyFunc(uint64_t *sig, int index, int k);

};
#endif