#include "lsharray.hpp"

LshForestArray::~LshForestArray(){
    std::vector<Lshforest>().swap(array);
}

LshForestArray::LshForestArray(){}

LshForestArray::LshForestArray(int maxk, int numHash, int initSize){
    for (int k = 1; k <= maxk; k++){
		this->array.push_back({k, numHash/k, 4, initSize});
	}
    this->maxk = maxk;
    this->numHash = numHash;
}

// LshForestArray* NewLshForestArray(int maxk, int numHash){
//     auto array = new std::vector<Lshforest>();
//     for (int k = 1; k <= maxk; k++){
// 		array->push_back({k, numHash/k, 4});
// 	}
//     return new LshForestArray{maxk, numHash, array->data()};
// }

void LshForestArray::add(std::string const& key, uint64_t *sig){
    for(int i = 0; i < this->maxk; i++){
        (this->array)[i].add(key, sig);
    }
}

void LshForestArray::index(){
     for(int i = 0; i < this->maxk; i++){
        (this->array)[i].index();
    }
}

std::vector<std::string> LshForestArray::query(uint64_t *sig, int K, int L){
    return (this->array)[K-1].query(sig, -1, L);
}

Param LshForestArray::optimalKL(int x, int q, double t){
    double minEr = boost::math::tools::max_value<double>();
    double currFp{0}, currFn{0}, currEr{0};
    int optK{0}, optL{0};
    for (int l = 1; l <= this->numHash; l++)
    {
        for (int k = 1; k <= this->maxk; k++)
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
