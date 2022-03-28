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