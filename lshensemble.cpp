#include "lshensemble.hpp"
#include "lsharray.hpp"

// LshEnsemble* NewLshEnsemble(Partition *parts, int numHash, int maxK){

//     auto lshes = new std::vector<Lshforest>() ;
// 	for(int i = 0; i < numPart; i++){ 
// 		lshes->push_back({maxK, numHash/maxK, 4});
// 	}
// 	return new LshEnsemble{parts, lshes->data(), maxK, numHash};
// }

LshEnsemble* NewLshEnsemblePlus(Partition *parts, int numHash, int maxk){
    auto index = new LshEnsemble{parts, std::vector<LshForestArray>(numPart), maxk, numHash};
    for(int i = 0; i < numPart; i++){ 
            (index->lshes)[i] = {maxk, numHash};
        }
    return index;
}

LshEnsemble::~LshEnsemble(){
    delete [] partitions;
    std::vector<LshForestArray>().swap(lshes);
}

void LshEnsemble::add(std::string key, uint32_t *sig, int partInd){
    this->lshes[partInd].add(key, sig);
}

void LshEnsemble::prepare(std::string key, uint32_t *sig, int size)  {
	for(int i = 0; i < numPart; i++){
		if (size >= this->partitions[i].lower && size <= this->partitions[i].upper) {
			this->add(key, sig, i);
			break;
		}
	}
	std::cerr << "no matching partition \n";
}

void LshEnsemble::index(){
    for(int i = 0; i < numPart; i++){
        this->lshes[i].index();
    }
}

queryResult LshEnsemble::query(uint32_t *sig, int size, double threshold){
    Param params[numPart];
    this->computeParams(params, size, threshold);
    clock_t begin = clock();
    std::vector<std::string> candidates;
    candidates = this->queryWithParam(sig, params);
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    queryResult results{candidates:candidates, duration:elapsed_secs};
    return results;
}

std::vector<std::string> LshEnsemble::queryWithParam(uint32_t *sig, Param *params){
    std::vector<std::string> results, tmp;
    for(int i = 0; i < numPart; i++){
        tmp = this->lshes[i].query(sig, params[i].k, params[i].l);
        results.insert(results.end(), tmp.begin(), tmp.end());
    }
    return results;
}

void LshEnsemble::computeParams(Param *params, int size, double threshold){
    Param optP;
    int x;
    for(int i = 0; i < numPart; i++){
        x = this->partitions[i].upper;
        Key key{x, size, threshold};
        if(this->cmap.count(key)){
            params[i] = this->cmap[key];
        }else{
            optP = this->lshes[i].optimalKL(x, size, threshold);
            this->cmap[key] = optP;
            params[i] = optP;
        }
    }
}

void littleEndian(byte *b, uint32_t v){
    b[0] = byte(v);
	b[1] = byte(v >> 8);
	b[2] = byte(v >> 16);
	b[3] = byte(v >> 24);
}

HashKeyFunc hashKeyFuncGen(int hashValueSize){

    return  [hashValueSize](uint32_t *sig, int index, int k) mutable
    {
        byte s[numHash*hashValueSize];
        byte buf[hashValueSize];
        for(int i = index*k; i < (index+1)*k; i++){
            littleEndian(buf, sig[i]);
            for(int j = 0; j < hashValueSize; j++){
                s[i*hashValueSize + j] = buf[j];
            }
        }
        return std::string(s, s + hashValueSize);
    };
}

int  bs(hashTable const& v, int prefix, std::string q){

	int i = 0, j = v.size();
    int h;
	while(i < j){
		h = int(i+j >> 1); 
		if(!(v[h].hashKey.substr(0, prefix) >= q)) {
			i = h + 1;
		} else {
			j = h;
		}
	}
	return i;
}

bool bucketSorter(Bucket const& domain, Bucket const& domain1){
    return domain.hashKey < domain1.hashKey;
}

bool rawDomainSorter(rawDomain const& domain, rawDomain const& domain1){
    return domain.values.size() < domain1.values.size();
}