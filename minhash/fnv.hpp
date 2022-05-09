#ifndef fnv
#define fnv
#include "../utils.hpp"

struct Fnv
{
    uint64_t offset64 = uint64_t(14695981039346656037);
    uint64_t prime = (1099511628211);
    uint64_t s;
    Fnv();
    void Reset();
    void Write(byte const *, int);
    uint64_t Sum64();
    static Fnv New64();

};





#endif