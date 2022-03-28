
#include "linearscan_benchmark_test.hpp"

double computeExactContainment(std::map<std::string, bool> const& query, std::map<std::string, bool> const& domain){
    if (query.size()== 0 || domain.size() == 0) {
		return 0.0;
	}
	std::map<std::string, bool> smaller, bigger;
	smaller = (query.size() < domain.size()) ? query : domain;
    bigger = (query.size() > domain.size()) ? query : domain;
    int intersection = 0;
    for (auto const& x : smaller)
    {
        if(bigger[x.first]) intersection++;
    }
	
	
    return double(intersection / query.size());
}
void benchmarkLinearscan(rawDomain const *raw_domains, rawDomain const *queries, int n, int q,
    double threshold, std::string linearscan_output){
        std::vector<queryResult> results;
        double c;
        std::cout << raw_domains[2].key << "   " << q << " ---- " <<n <<"\n";
        for(int query = 0; query < q; query++){
            clock_t begin = clock();
            std::vector<std::string> r;
            for(int domain = 0; domain < n; domain++){
                c = computeExactContainment(queries[query].values, raw_domains[domain].values);
                std::cout << c << "\n";
                if(c < threshold) continue;
                r.push_back(raw_domains[domain].key);
            }
            clock_t end = clock();
            double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
            results.push_back({r, queries[query].key, elapsed_secs});
        }
        outputQueryResults(results, linearscan_output);
    }

