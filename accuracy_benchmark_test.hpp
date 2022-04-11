#ifndef accuracy_benchmark_test
#define accuracy_benchmark_test

#include "utils.hpp"

void benchmarkAccuracy(std::string, std::string , std::string);

P_r recallPrecision(queryResult, queryResult);

std::vector<queryResult> readQueryResultFile(std::string);

double mean(double [], int);

#endif