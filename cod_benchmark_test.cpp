#include "linearscan_benchmark_test.hpp"
#include "lshensemble_benchmark_test.hpp"
#include "accuracy_benchmark_test.hpp"

constexpr int subsets[] {65537};
constexpr int subsetsLen {std::size(subsets)};
constexpr double threshold {0.5};
constexpr double fracQuery  {0.01};
constexpr int minDomainSize {10};


int readDomains(std::vector<rawDomain> &rawDomains, std::string const& dir){
    int count = 0;
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
        count++;
        rawDomains.push_back({values, key});
    }
    return count;
}
void benchmarkCOD(rawDomain  *rawDomains, rawDomain  *queries, int n, int q, double threshold, int subset){
    std::string linearscanOutput = "_cod_linearscan_threshold=0.50";
	std::string lshensembleOutput = "_cod_lshensemble_threshold=0.50";
	std::string accuracyOutput = "_cod_accuracy_threshold=0.50";
    // benchmarkLinearscan(rawDomains, queries, n, q, threshold, linearscanOutput);
	benchmarkLshEnsemble(rawDomains, queries, n, q, threshold, lshensembleOutput);
	benchmarkAccuracy(linearscanOutput, lshensembleOutput, accuracyOutput);
}
int main(int argc, char* argv[]) {

    std::vector<rawDomain> rawDomains;

    auto begin = std::chrono::high_resolution_clock::now();
    int numDomains;
    // Running this function requires a `_cod_domains` directory
    // in the current directory.
    // The `_code_domains` directory should contain domains files,
    // which are line-separated files.
    numDomains = readDomains(rawDomains, argv[1]);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsed_secs = end - begin;
    std::cout << "read " << numDomains << " domains in " << elapsed_secs.count() << "s\n";

    int numQuery {int(fracQuery * double(numDomains))};
    std::cout << "size of queries" << numQuery <<"\n";

    std::vector<rawDomain> queries(numQuery);
    srand (benchmarkSeed);
    for(int j = 0; j < numQuery; j++){
        queries[j] = rawDomains[rand() % numDomains];
    }
    


    // std::vector<std::string> query;
    // std::ifstream infile("./querynames");
    // std::string filename;
    // while (std::getline(infile, filename))
    // {
    //     query.push_back(filename);
    // }
    // for(int j = 0; j < numQuery; j++){
    //     for(int i =0; i < numDomains; i++){
    //         if(rawDomains[i].key == query[j]) 
    //             queries[j] = rawDomains[i];
    //     }
    // }
    // Run benchmark
    std::cout << "start benchmark \n";
    benchmarkCOD(rawDomains.data(), queries.data(), numDomains, numQuery, threshold, 1);
    
}


