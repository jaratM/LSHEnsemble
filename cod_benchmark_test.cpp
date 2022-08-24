#include "linearscan_benchmark_test.hpp"
#include "lshensemble_benchmark_test.hpp"
#include "accuracy_benchmark_test.hpp"

// constexpr int subsets[] {65537};
// constexpr int subsetsLen {std::size(subsets)};
constexpr double threshold {0.5};
constexpr double fracQuery  {0.01};
constexpr int minDomainSize {10};


void readDomains(std::vector<rawDomain> &rawDomains, std::string const& dir){
    for (const auto & entry : std::filesystem::directory_iterator(dir)){
        std::ifstream infile(entry.path());
        std::string key = entry.path().filename();
        std::string value;
        std::unordered_map<std::string, bool> values;
        while (std::getline(infile, value))
        {
            std::transform(value.begin(), value.end(), value.begin(), [](unsigned char c){ return std::tolower(c); });
            values[value] = true;
        }
        if(values.size() < minDomainSize) continue;
        rawDomains.push_back({values, key});
    }
}
void benchmarkCOD(rawDomain  *rawDomains, rawDomain  *queries, int n, int q, double threshold, int subset){
    std::string linearscanOutput = "./cod_linearscan_threshold=0.50";
	std::string lshensembleOutput = "./cod_lshensemble_threshold=0.50";
	std::string accuracyOutput = "./cod_accuracy_threshold=0.50";
    benchmarkLinearscan(rawDomains, queries, n, q, threshold, linearscanOutput);
	benchmarkLshEnsemble(rawDomains, queries, n, q, threshold, lshensembleOutput);
	benchmarkAccuracy(linearscanOutput, lshensembleOutput, accuracyOutput);
}
int main(int argc, char* argv[]) {

    std::vector<rawDomain> rawDomains;
    auto begin = std::chrono::high_resolution_clock::now();
    
    readDomains(rawDomains, argv[1]);
    int numDomains = rawDomains.size();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsed_secs = end - begin;
    std::cout << "read " << numDomains << " domains in " << elapsed_secs.count() << "s\n";

    int numQuery {int(fracQuery * double(numDomains))};
    std::cout << "size of queries" << numQuery <<"\n";
 
    rawDomain queries[numQuery];
    srand (benchmarkSeed);
    for(int j = 0; j < numQuery; j++){
        queries[j] = rawDomains[rand() % numDomains];
    }

    // Run benchmark
    std::cout << "start benchmark \n";
    benchmarkCOD(rawDomains.data(), queries, numDomains, numQuery, threshold, 1);
    
}


