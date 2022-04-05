#include "lshforest.hpp"

Lshforest::Lshforest(){
}
Lshforest::~Lshforest()
{
    std::vector<initHashTable>().swap(initHashTables);
    std::vector<hashTable>().swap(hashTables);
}
Lshforest::Lshforest(int K, int L, int hashValueSize)
{
    if(K < 0 || L <0){
        std::cerr << "k and l must be positive";
    }
    this->k = K;
    this->l = L;
    this->hashValueSize = hashValueSize;
    this->hashKeyFunc = hashKeyFuncGen(hashValueSize);
    this->initHashTables.resize(L);
}

void Lshforest::add(std::string key, uint32_t *sig) {
    std::string tmp;
    for(int i = 0; i < this->l; i++){
        tmp = this->hashKeyFunc(sig, i, this->k);
        this->initHashTables[i][tmp].push_back(key);
    }
}

void Lshforest::index(){
    hashTable ht;
    // auto p = this->initHashTables[1];
    for(int i = 0; i < this->l; i++){
        for (auto x : this->initHashTables[i]){
            ht.push_back({x.first, x.second});
        }
        std::sort(ht.begin(), ht.end(), &bucketSorter);
        this->hashTables.push_back(ht);
    }
    this->initHashTables.clear();
}

std::vector<std::string> Lshforest::query(uint32_t *sig, int k, int l){
    if(k == -1) k = this->k;
    if(l == -1) l = this->l;
    int prefixSize = this->hashValueSize * k;
    std::vector<std::string> hs(l);
    for (int i = 0; i < l; i++)
    {
        hs[i] = this->hashKeyFunc(sig, i, k);
    }
    std::map<std::string, bool> seens;
    // hashTable ht;
    std::string hk;
    int p;
    std::vector<std::string> candidates;
    for (int i = 0; i < l; i++)
    {
        auto ht = this->hashTables[i];
        hk = hs[i];
        p = bs(ht, prefixSize, hk);
        if(p < ht.size() && ht[p].hashKey.substr(0, prefixSize) == hk){
            for (int j = p; j < ht.size() && ht[j].hashKey.substr(0,prefixSize) == hk; j++) {
                for(auto key : ht[j].keys){
                    if(seens[key]) continue;
                    seens[key] = true;
                    candidates.push_back(key);
                }
            }
        }
    }
    seens.clear();
    return candidates;
    
}

Param Lshforest::optimalKL(int x, int q, double t){
    double minEr = double(1e6+5);
    double currFp{}, currFn{}, currEr{};
    int optK{}, optL{};
    for (int l = 1; l < this->l; l++)
    {
        for (int k = 1; k < this->k; k++)
        {
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
