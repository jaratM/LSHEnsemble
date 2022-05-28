
#include "lshensemble_benchmark_test.hpp"

void minhashDomains(domainRecord *domainRecords, rawDomain *domains, int size) {
    
    for(int i = 0; i < size; i++){
        auto mh = newMinhash(benchmarkSeed, NumHash);
        for(auto item : domains[i].values){
            mh->push(reinterpret_cast<const uint8_t*>(&item.first[0]), item.first.length());
        }
        domainRecords[i] = (domainRecord){domains[i].key, domains[i].values.size(), mh->signature()};
    }    
}

void benchmarkLshEnsemble(rawDomain *rawDomains, rawDomain *rawQueries, int n, int q,
    double threshold, std::string outputFilename){

    std::vector<domainRecord> domainRecords(n), queries(q);
    auto begin = std::chrono::high_resolution_clock::now();
    
    minhashDomains(domainRecords.data(), rawDomains, n);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsed_secs = end - begin;
    std::cout << "Minhash domains in " << elapsed_secs.count() << "s\n";

    begin = std::chrono::high_resolution_clock::now();
    minhashDomains(queries.data(), rawQueries, q);
    end = std::chrono::high_resolution_clock::now();
    elapsed_secs = end - begin;
    std::cout << "Minhash queries in " << elapsed_secs.count() << "s\n";

    // sort records
    begin = std::chrono::high_resolution_clock::now();
    std::sort(domainRecords.data(), domainRecords.data() + n, &domainRecordSorter);
    std::cout << "Start building LSH Ensemble index \n";
    LshEnsemble *index = BootstrapLshEnsembleEquiDepth(NumPart, NumHash, MaxK, n, domainRecords.data());
    end = std::chrono::high_resolution_clock::now();
    elapsed_secs = end - begin;
    std::cout << "Finished building LSH Ensemble index in " << elapsed_secs.count() << "s\n";

    std::cout << "Start querying LSH Ensemble index with "<< q << " queries.\n";
    begin = std::chrono::high_resolution_clock::now();
    std::vector<queryResult> results;
    queryResult candidates;
    for(int i = 0; i < q; i++){
        candidates = index->query(queries[i].signatures, queries[i].size, threshold);
        candidates.queryKey = queries[i].key;
        results.push_back(candidates);
    }
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsed_secs1 = end - begin;
    std::cout << "Finished querying LSH Ensemble index in " << elapsed_secs1.count() << "s output " << outputFilename << "\n";
    delete index;
    outputQueryResults(results, outputFilename);
}


