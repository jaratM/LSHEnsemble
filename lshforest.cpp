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
    this->initHashTables.resize(L);
    this->hashTables.resize(L);
}

void Lshforest::add(std::string const& key, uint64_t *sig) {
   for(int i = 0; i < this->l; i++){
        this->initHashTables[i][this->HashKeyFunc(sig, i, this->k)].push_back(key);
    }
}

void Lshforest::index(){ 
    initHashTable::iterator it;
    // auto value_selector = [](auto pair){return pair;};
    for(int i = 0; i < this->l; i++){
        it = this->initHashTables[i].begin();
        while(it != this->initHashTables[i].end()){
            this->hashTables[i].push_back({it->first, it->second});
            it++;
        }
        // std::transform(this->initHashTables[i].begin(), this->initHashTables[i].end(), this->hashTables[i].begin(), value_selector);
        std::sort(this->hashTables[i].begin(), this->hashTables[i].end(), &bucketSorter);
        // std::unordered_map<std::string, std::vector<std::string>>().swap(initHashTables[i]);
    }
}

std::vector<std::string> Lshforest::query(uint64_t *sig, int k, int l){
    if(k == -1) k = this->k;
    if(l == -1) l = this->l;
    int prefixSize = this->hashValueSize * k;
    std::vector<std::string> hs(l);
    for (int i = 0; i < l; i++)
    {
        hs[i] = HashKeyFunc(sig, i, k);
    }
    std::unordered_map<std::string, bool> seens;
    std::string hk;
    int p;
    std::vector<std::string> candidates;
    for (int i = 0; i < l; i++)
    {
        hk = hs[i];
        p = binarySearch(this->hashTables[i], prefixSize, hk);
        if(p < this->hashTables[i].size() && this->hashTables[i][p].hashKey.substr(0, prefixSize) == hk){
            for (int j = p; j < this->hashTables[i].size() && this->hashTables[i][j].hashKey.substr(0,prefixSize) == hk; j++) {
                for(auto const& key : this->hashTables[i][j].keys){
                    if(seens[key]) continue;
                    seens[key] = true;
                    candidates.push_back(key);
                }
            }
        }
    }
    return candidates;
    
}

Param Lshforest::optimalKL(int x, int q, double t){
    double minEr = boost::math::tools::max_value<double>();
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

void littleEndian(byte *b, uint64_t v){
    b[0] = byte(v);
	b[1] = byte(v >> 8);
	b[2] = byte(v >> 16);
	b[3] = byte(v >> 24);
}
std::string Lshforest::HashKeyFunc(uint64_t *sig, int index, int k) {
        int p = 0;
        byte s[k*this->hashValueSize];
        byte buf[this->hashValueSize];
        for(int i = index*k; i < (index+1)*k; i++){
            littleEndian(buf, sig[i]);
            for(int j = 0; j < this->hashValueSize; j++){
                s[j + p] = buf[j];
            }
            p+=this->hashValueSize;
        }
        return std::string(s, s + this->hashValueSize*k);
}