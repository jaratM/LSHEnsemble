#include "fnv.hpp"

Fnv::Fnv(){
    s = offset64;
}

Fnv Fnv::New64(){
    return Fnv();
}

void Fnv::Reset(){
    s = offset64;
}
void Fnv::Write(byte const *data, int len){
    uint64_t hash = s;
    for(int i = 0; i < len; i++){
        hash ^= uint64_t(data[i]);
        hash *= prime;
    }
    s = hash;
}
uint64_t Fnv::Sum64(){
    return uint64_t(s);
}