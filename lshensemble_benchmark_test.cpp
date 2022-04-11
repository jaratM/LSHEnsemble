
#include "lshensemble_benchmark_test.hpp"

void minhashDomains(domainRecord *domainRecords, rawDomain *domains, int size, int numHash) {
    rp::MinHash mh(numHash, benchmarkSeed);
    for(int i = 0; i < size; i++){
        std::vector<uint32_t> sig = mh.minhash_universal(domains[i].values);
        domainRecords[i].signatures = sig;
        domainRecords[i].size = domains[i].values.size();
        domainRecords[i].key = domains[i].key;
    }
}

void benchmarkLshEnsemble(rawDomain *rawDomains, rawDomain *rawQueries, int n, int q,
    double threshold, std::string outputFilename){

    domainRecord domainRecords[n], queries[q];
    clock_t begin = clock();
    
    minhashDomains(domainRecords, rawDomains, n, numHash);
    
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << "Minhash domains in " << elapsed_secs << "\n";
    // outputDomainRecords(domainRecords, n,"signatures/domains");

    begin = clock();
    minhashDomains(queries, rawQueries, q, numHash);

    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << "Minhash queries in " << elapsed_secs << "\n";
    // outputDomainRecords(queries, q, "signatures/queries");
    // std::cout << domainRecords[0].signatures[0] << "\n";
    std::cout << "Start building LSH Ensemble index \n";
    LshEnsemble *index = BootstrapLshEnsembleEquiDepth(numPart, numHash, maxK, n, domainRecords);
    std::cout << "Finished building LSH Ensemble index \n";
    std::cout << "Start querying LSH Ensemble index with "<< q << " queries.\n";

    begin = clock();
    std::vector<queryResult> results;
    queryResult candidates;
    for(int i = 0; i < q; i++){
        candidates = index->query(queries[i].signatures.data(), queries[i].size, threshold);
        candidates.queryKey = queries[i].key;
        results.push_back(candidates);
    }
    delete index;
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << "Finished LSH querying  in " << elapsed_secs << "\n";
    // delete[] index->partitions;
    outputQueryResults(results, outputFilename);
    std::cout << "Finished querying LSH Ensemble index, output " << outputFilename;
}


