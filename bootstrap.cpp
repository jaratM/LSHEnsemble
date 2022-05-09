#include "bootstrap.hpp"

LshEnsemble* BootstrapLshEnsembleEquiDepth(int numPart, int numHash, int maxK, int totalNumDomains, domainRecord *sortedDomains){
    auto parts = new Partition[numPart];
    auto index = NewLshEnsemblePlus(parts, numHash, maxK);
    bootstrapEquiDepth(index, totalNumDomains, sortedDomains);
    return index;
}

void bootstrapEquiDepth(LshEnsemble *index, int totalNumDomains, domainRecord *sortedDomains){
    int depth = totalNumDomains / NumPart;
    int currDepth{0}, currPart{0}, currSize{0};
    
    for (int i = 0; i < totalNumDomains; i++)
    {
        if(currSize > sortedDomains[i].size)
            return;
        currSize = sortedDomains[i].size;
		index->add(sortedDomains[i].key, sortedDomains[i].signatures, currPart);
		currDepth++;
		index->partitions[currPart].upper = currSize;
		if( currDepth >= depth && currPart < NumPart-1) {
			currPart++;
			index->partitions[currPart].lower = currSize;
			currDepth = 0;
		}
    }
    index->index();
}