#include "linearscan_benchmark_test.hpp"
#include "lshensemble_benchmark_test.hpp"
constexpr int subsets[] {500};
constexpr int subsetsLen {std::size(subsets)};
constexpr double threshold {0.5};
constexpr double fracQuery  {0.1};
constexpr int minDomainSize {10};


int readDomains(std::vector<rawDomain> &rawDomains, std::string const& dir){
    int count = 0;
    for (const auto & entry : std::filesystem::directory_iterator(dir)){
        std::ifstream infile(entry.path());
        std::string key = entry.path().filename();
        std::string value;
        std::map<std::string, bool> values;
        while (std::getline(infile, value))
        {
            std::transform(value.begin(), value.end(), value.begin(), [](unsigned char c){ return std::tolower(c); });
            values[value] = true;
        }
        if(values.size() < minDomainSize) continue;
        count++;
        rawDomains.push_back({values, key});
    }
    return count;
}
void benchmarkCOD(rawDomain  *rawDomains, rawDomain  *queries, int n, int q, double threshold, int subset){
    std::string linearscanOutput = "../output32/_cod_linearscan_threshold=" + std::to_string(threshold) + ",subset=" + std::to_string(subset+1);
	std::string lshensembleOutput = "../output32/_cod_lshensemble_threshold=" + std::to_string(threshold) + ",subset=" + std::to_string(subset+1);
	std::string accuracyOutput = "../output32/_cod_accuracy_threshold=" + std::to_string(threshold) + ",subset=" + std::to_string(subset+1);
    benchmarkLinearscan(rawDomains, queries, n, q, threshold, linearscanOutput);
	// benchmarkLshEnsemble(rawDomains, queries, n, q, threshold, lshensembleOutput);
	// benchmarkAccuracy(linearscanOutput, lshensembleOutput, accuracy_outpuO;


}
int main(int argc, char* argv[]) {

    std::vector<rawDomain> rawDomains;

    clock_t begin = clock();
    int numDomains;
    // Running this function requires a `_cod_domains` directory
    // in the current directory.
    // The `_code_domains` directory should contain domains files,
    // which are line-separated files.
    numDomains = readDomains(rawDomains, "../doc_files");

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << "read " << numDomains << " domains in " << elapsed_secs << "\n";

    // sort domains 
    std::sort(rawDomains.begin(), rawDomains.end(), &rawDomainSorter);

    for(int i = 0; i < subsetsLen; i++){
        std::cout << "subset : " << i << "\n"; 
        int numQuery {int(fracQuery * double(subsets[i]))};
        std::cout << "size of queries" << numQuery <<"\n";
        rawDomain rawDomains_[subsets[i]];
        for (int k = 0; k < subsets[i]; k++) {
            rawDomains_[k] = rawDomains[k];
        }
        rawDomain queries[subsets[i]];
        srand (benchmarkSeed);
        for(int j = 0; j < numQuery; j++){
            queries[j] = rawDomains_[rand() % subsets[i]];
        }
        // Run benchmark
        benchmarkCOD(rawDomains_, queries, subsets[i], numQuery, threshold, i);
    }
    
}