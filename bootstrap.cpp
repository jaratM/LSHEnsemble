#include "bootstrap.hpp"

LshEnsemble* BootstrapLshEnsembleEquiDepth(int numPart, int numHash, int maxK, int totalNumDomains, domainRecord *sortedDomains){
    auto parts = new Partition[numPart];
    auto index = NewLshEnsemblePlus(parts, numHash, maxK);
    bootstrapEquiDepth(index, totalNumDomains, sortedDomains);
    return index;
}

void bootstrapEquiDepth(LshEnsemble *index, int totalNumDomains, domainRecord *sortedDomains){
    int depth = totalNumDomains / numPart;
    int currDepth{}, currPart{}, currSize{};
    
    for (int i = 0; i < totalNumDomains; i++)
    {
        if(currSize > sortedDomains[i].size)
            return;
        currSize = sortedDomains[i].size;
		index->add(sortedDomains[i].key, sortedDomains[i].signatures.data(), currPart);
		currDepth++;
		index->partitions[currPart] = {0,currSize};
		if( currDepth >= depth && currPart < numPart-1) {
			currPart++;
			index->partitions[currPart].lower = currSize;
			currDepth = 0;
		}
    }
    index->index();
}