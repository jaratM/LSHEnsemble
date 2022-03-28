#ifndef linearscan_benchmark_test
#define linearscan_benchmark_test
#include "utils.hpp"

double computeExactContainment(std::map<std::string, bool> const& query, std::map<std::string, bool> const& domain);

void benchmarkLinearscan(rawDomain const *raw_domains, rawDomain const *queries, int n, int q,
    double threshold, std::string linearscan_output);

#endif