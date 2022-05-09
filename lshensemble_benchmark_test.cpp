
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

    domainRecord domainRecords[n], queries[q];
    clock_t begin = clock();
    
    minhashDomains(domainRecords, rawDomains, n);
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << "Minhash domains in " << elapsed_secs << "\n";

    begin = clock();
    minhashDomains(queries, rawQueries, q);
    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << "Minhash queries in " << elapsed_secs << "\n";

    // sort records
    begin = clock();
    std::sort(domainRecords, domainRecords + n, &domainRecordSorter);
    std::cout << "Start building LSH Ensemble index \n";
    LshEnsemble *index = BootstrapLshEnsembleEquiDepth(NumPart, NumHash, MaxK, n, domainRecords);
    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << "Finished building LSH Ensemble index in " << elapsed_secs << "\n";

    std::cout << "Start querying LSH Ensemble index with "<< q << " queries.\n";
    begin = clock();
    std::vector<queryResult> results;
    queryResult candidates;
    for(int i = 0; i < q; i++){
        candidates = index->query(queries[i].signatures, queries[i].size, threshold);
        candidates.queryKey = queries[i].key;
        results.push_back(candidates);
    }
    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    delete index;
    outputQueryResults(results, outputFilename);
    std::cout << "Finished querying LSH Ensemble index in " << elapsed_secs<< " output " << outputFilename << "\n";
}


