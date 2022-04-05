#include "lsharray.hpp"

LshForestArray::~LshForestArray(){
    std::vector<Lshforest>().swap(array);
}

LshForestArray::LshForestArray(){}

LshForestArray::LshForestArray(int maxk, int NumHash){
    for (int k = 1; k <= maxk; k++){
		this->array.push_back({k, NumHash/k, 4});
	}
    this->maxk = maxk;
    this->numHash = NumHash;
}

// LshForestArray* NewLshForestArray(int maxk, int numHash){
//     auto array = new std::vector<Lshforest>();
//     for (int k = 1; k <= maxk; k++){
// 		array->push_back({k, numHash/k, 4});
// 	}
//     return new LshForestArray{maxk, numHash, array->data()};
// }

void LshForestArray::add(std::string key, uint32_t *sig){
    for(int i = 0; i < this->maxk; i++){
        (this->array)[i].add(key, sig);
    }
}

void LshForestArray::index(){
     for(int i = 0; i < this->maxk; i++){
        (this->array)[i].index();
    }
}

std::vector<std::string> LshForestArray::query(uint32_t *sig, int K, int L){
    std::vector<std::string> candidates;
    candidates = (this->array)[K-1].query(sig, -1, L);
    return candidates;
}

Param LshForestArray::optimalKL(int x, int q, double t){
    double minEr = double(1e6+5);
    double currFp{}, currFn{}, currEr{};
    int optK{}, optL{};
    for (int l = 1; l < this->numHash; l++)
    {
        for (int k = 1; k < this->maxk; k++)
        {
            if (k*l > this->numHash ){
				continue;
			}
            currFp = probFalsePositive(x, q, l, k, t, integrationPrecision);
            currFn = probFalseNegative(x, q, l, k, t, integrationPrecision);
			currEr = currFn + currFp;
            if(minEr > currEr){
                minEr = currEr;
                optK = k;
                optL = l;
            }
        }   
        
    }
    return {optK, optL};
}
