#ifndef lshensemble_benchmark_test
#define lshensemble_benchmark_test
#include "./LSH/minhash.hpp"
#include "bootstrap.hpp"
void minhashDomains(domainRecord *domainRecords, rawDomain *domains, int size);

void benchmarkLshEnsemble(rawDomain *rawDomains, rawDomain *rawQueries, int n, int q,
    double threshold, std::string output_filename);

#endif /* lshensemble_benchmark_test */
