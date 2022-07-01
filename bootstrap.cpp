#include "bootstrap.hpp"

void BootstrapLshEnsembleEquiDepth(int numPart, int numHash, int maxK, int totalNumDomains, domainRecord *sortedDomains){
    Partition partition;
    std::vector<LshEnsemble*> indexes(numPart);
    for(int i = 0; i < numPart; i++){
        indexes[i] = NewLshEnsemblePlus(partition, numHash, maxK, totalNumDomains/numPart);
    }
    bootstrapEquiDepth(indexes, totalNumDomains, sortedDomains);

}

void bootstrapEquiDepth(std::vector<LshEnsemble*> indexes, int totalNumDomains, domainRecord *sortedDomains){
    int depth = totalNumDomains / NumPart;
    int currDepth{0}, currPart{0}, currSize{0};
    for (int i = 0; i < totalNumDomains; i++)
    {
        if(currSize > sortedDomains[i].size)
            return;
        currSize = sortedDomains[i].size;
		indexes[currPart]->add(sortedDomains[i].key, sortedDomains[i].signatures, currPart);
		currDepth++;
		indexes[currPart]->partition.upper = currSize;
		if( currDepth >= depth && currPart < NumPart) {
            indexes[currPart]->index();
            saveIndex(currPart, indexes[currPart]);
            delete indexes[currPart];
			currPart++;
            if(currPart == NumPart) return;
			indexes[currPart]->partition.lower = currSize;
			currDepth = 0;
		}
    }
}

void saveIndex(int partition, LshEnsemble *idx){
    std::ofstream ofs("../indexes/" + std::to_string(partition));
    boost::archive::text_oarchive oa(ofs);
    oa << idx;
}