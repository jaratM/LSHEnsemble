#include "accuracy_benchmark_test.hpp"
#include <sstream>
void benchmarkAccuracy(std::string groundTruthFilename, std::string queryResultFilename, std::string outputFilename ) {
    std::vector<queryResult> groundTruths, queryResults;
    groundTruths = readQueryResultFile(groundTruthFilename);
	queryResults = readQueryResultFile(queryResultFilename);
    int q = queryResults.size();
    double precisions[q], recalls[q];
    for(int i = 0; i < q; i++){
       P_r p_r = recallPrecision(queryResults[i], groundTruths[i]);
       precisions[i] = p_r.p;
       recalls[i] = p_r.r;
    }
	std::cout << "Mean Precision = " << mean(precisions, q) << "\n";
	std::cout << "Mean Recall = " << mean(recalls, q) << "\n";


    std::ofstream out{outputFilename};
    if(!out){
        std::cerr << "can't create file : " << outputFilename << "\n";
        return;
    }
    out << "Query" << ", Precision" << ", Recall\n";
    for(int i = 0; i < q; i++){
        out<< queryResults[i].queryKey <<", " << precisions[i] << ", " << recalls[i] << "\n";
    }
    out.close();
}

P_r recallPrecision(queryResult result, queryResult groundTruth){
    if (groundTruth.candidates.size() == 0 ){
		return {1.0, 1.0};
	}
	if (result.candidates.size() == 0 ){
		return {0.0, 0.0};
	}
	std::map<std::string, bool> truth;
	for (auto v :groundTruth.candidates){
		truth[v] = true;
	}
    std::map<std::string, bool> test;
	for (auto v : result.candidates){
		test[v] = true;
	}
	if (truth.size() != groundTruth.candidates.size()) {
		std::cerr << "Ground truth contains duplicates";
	}
	if (test.size() != result.candidates.size()) {
		std::cerr <<"Query result contain duplicates!";
	}
	int overlap = 0;
	for(auto id : test ){
		if (truth[id.first]){
			overlap++;
		}
	}
	double recall = double(overlap) / double(truth.size());
	double precision = double(overlap) / double(test.size());
	return {precision, recall};
}

std::vector<queryResult> readQueryResultFile(std::string queryResultFile){
	std::vector<queryResult> results;
	std::ifstream infile(queryResultFile);
	std::string line;
	std::vector<std::string> tokens;
	while (std::getline(infile, line)){
		std::istringstream iss(line);
		std::string token;
		while(std::getline(iss, token, '\t')) 
			tokens.push_back(token);
		
	}
}
double mean(double *a, int size){
	double sum = 0;
	for(int i = 0; i < size; i++){
		sum += a[i];
	}
	return (sum/double(size));
}