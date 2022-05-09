#include "minhash.hpp"

void Minhash::push(byte const b[], int len){
    uint64_t v1 = h1(b, len);
    uint64_t v2 = h2(b, len);

    for(int i = 0; i < numhash; i++){
        uint64_t hv = v1 + uint64_t(i)*v2;
        if(hv < minimums[i]){
            minimums[i] = hv;
        }
    }
}

uint64_t* Minhash::signature(){
    return minimums;
}

void BigEndian(byte *b, uint64_t v){
    b[0] = byte(v >> 56);
	b[1] = byte(v >> 48);
	b[2] = byte(v >> 40);
	b[3] = byte(v >> 32);
    b[4] = byte(v >> 24);
	b[5] = byte(v >> 16);
	b[6] = byte(v >> 8);
	b[7] = byte(v);

}
Minhash* newMinhash(int seed, int numhash){
    byte b1[8];
    byte b2[8];
    // goRand1 and gorand2 are two random values from Go with seed == 42 
    uint64_t goRand1 = 3440579354231278675;
    uint64_t goRand2 = 608747136543856411;
    BigEndian(b1, goRand1);
    BigEndian(b2, goRand2);

    Fnv fnv1 = Fnv::New64();
    hash64 h1 = [fnv1, b1](byte const *b, int len) mutable{
        fnv1.Reset();
		fnv1.Write(b1, 8);
		fnv1.Write(b, len);
		return fnv1.Sum64();
    };

    Fnv fnv2 = Fnv::New64();
    hash64 h2 = [fnv2, b2](byte const *b, int len) mutable{
        fnv2.Reset();
		fnv2.Write(b2, 8);
		fnv2.Write(b, len);
		return fnv2.Sum64();
    };

    auto mins = new uint64_t[numhash];
    for(int i = 0; i < numhash; i++){
        mins[i] = UINT64_MAX;
    }
    return new Minhash{numhash, mins, h1, h2};
}
