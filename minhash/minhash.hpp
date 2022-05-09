#ifndef minhash
#define minhash
#include "fnv.hpp"

using hash64 = std::function<std::uint64_t(byte const *, int)> ;

class Minhash
{
    public:
        int numhash;
        uint64_t* minimums;
        hash64 h1;
        hash64 h2;
        void push(byte const [], int);
        uint64_t* signature();
};


void BigEndian(byte *b, uint64_t v);
Minhash* newMinhash(int seed, int numhash);

#endif
