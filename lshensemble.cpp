#include "lshensemble.hpp"
#include "lsharray.hpp"

// LshEnsemble* NewLshEnsemble(Partition *parts, int numHash, int maxK){

//     auto lshes = new std::vector<Lshforest>() ;
// 	for(int i = 0; i < NumPart; i++){ 
// 		lshes->push_back({maxK, numHash/maxK, 4});
// 	}
// 	return new LshEnsemble{parts, lshes->data(), maxK, numHash};
// }
 
LshEnsemble* NewLshEnsemblePlus(Partition partition, int numHash, int maxk, int initSize){
    return new LshEnsemble{partition, {maxk, numHash, initSize}, maxk, numHash};
}

LshEnsemble::~LshEnsemble(){
}

void LshEnsemble::add(std::string const& key, uint64_t *sig, int partInd){
    this->lshes.add(key, sig);
}

// void LshEnsemble::prepare(std::string key, uint64_t *sig, int size)  {
// 	for(int i = 0; i < NumPart; i++){
// 		if (size >= this->partitions[i].lower && size <= this->partitions[i].upper) {
// 			this->add(key, sig, i);
// 			break; 
// 		}
// 	}
// 	std::cerr << "no matching partition \n";
// }

void LshEnsemble::index(){
    for(int i = 0; i < NumPart; i++){
        this->lshes.index();
    }
}

queryResult LshEnsemble::query(uint64_t *sig, int size, double threshold){
    Param param;
    param = this->computeParams(size, threshold);
    clock_t begin = clock();
    std::vector<std::string> candidates;
    candidates = this->queryWithParam(sig, param);
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    queryResult results{candidates:candidates, duration:elapsed_secs};
    return results;
}

std::vector<std::string> LshEnsemble::queryWithParam(uint64_t *sig, Param const& param){
    
    std::vector<std::string> results;
    results = this->lshes.query(sig, param.k, param.l);
    return results;
}

Param LshEnsemble::computeParams(int size, double threshold){
    Param optP;
    optP = this->lshes.optimalKL(this->partition.upper, size, threshold);
    return optP; 
}


