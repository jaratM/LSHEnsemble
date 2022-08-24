#include "utils.hpp"

void outputQueryResults(std::vector<queryResult> const& results, std::string output_file_name){
    std::ofstream out{output_file_name};
    if(!out){
        std::cerr << "can't create file : " << output_file_name << "\n";
        return;
    }
    for(auto result : results){
        out << result.queryKey << "\t";
        out << std::to_string(result.duration) << "s\t";
        for(int i = 0; i < result.candidates.size(); i++){
            out << result.candidates[i];
            if(i < result.candidates.size() - 1)
                out << "\t";
        }
        out << "\n";
    }
    out.close();
}

int  binarySearch(hashTable const& v, int size, int prefix, std::string const& q){

	int i = 0, j = size;
    int h;
	while(i < j){
		h = int(i+j >> 1); 
		if(!(v[h].hashKey.substr(0, prefix) >= q)) {
			i = h + 1;
		} else {
			j = h;
		}
	}
	return i;
}

bool entrySorter(Entry const& domain, Entry const& domain1){
    return domain.hashKey < domain1.hashKey;
}

bool rawDomainSorter(rawDomain const& domain, rawDomain const& domain1){
    return domain.values.size() < domain1.values.size();
}

bool domainRecordSorter(domainRecord const& record1, domainRecord const& record2){
    return record1.size < record2.size;
}

std::string cashKey(int x, int q, double t){
    return boost::str(boost::format("%d %d %.2f") % x % q % t);
}

// void outputDomainRecords(domainRecord *records, int size, std::string output_file_name){
//     std::ofstream out{output_file_name};
//     if(!out){
//         std::cerr << "can't create file : " << output_file_name << "\n";
//         return;
//     }
//     for(int i = 0; i < size; i++){
//         out << records[i].key << "\t";
//         for(int j = 0; j < records[i].signatures.size(); j++){
//             out << records[i].signatures[j];
//             if(i < records[i].signatures.size() - 1)
//                 out << "\t";
//         }
//         out << "\n";
//     }
//     out.close();
// }