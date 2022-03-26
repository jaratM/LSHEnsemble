#include "bootstrap.hpp"

LshEnsemble* BootstrapLshEnsembleEquiDepth(int numPart, int numHash, int maxK, int totalNumDomains, domainRecord *sortedDomains){
    Partition parts[numPart];
    LshEnsemble *index = NewLshEnsemble(parts, numHash, maxK);
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
        std::cout << sortedDomains[i].key;
        //std::cout << "equidepth initHashTables: " <<index->lshes->initHashTables.size() << "\n";
		index->add(sortedDomains[i].key, sortedDomains[i].signatures, currPart);
        std::cout << sortedDomains[i].key;
		currDepth++;
		index->partitions[currPart].upper = sortedDomains[i].size;
		if( currDepth >= depth && currPart < numPart-1) {
			currPart++;
			index->partitions[currPart].lower = sortedDomains[i].size;
			currDepth = 0;
		}
    }
    index->index();
}