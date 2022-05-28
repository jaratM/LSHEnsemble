#include "bootstrap.hpp"

LshEnsemble* BootstrapLshEnsembleEquiDepth(int numPart, int numHash, int maxK, int totalNumDomains, domainRecord *sortedDomains){
    std::vector<Partition> parts(numPart);
    auto index = NewLshEnsemblePlus(parts, numHash, maxK, totalNumDomains);
    bootstrapEquiDepth(index, totalNumDomains, sortedDomains);
    return index;
}

void bootstrapEquiDepth(LshEnsemble *index, int totalNumDomains, domainRecord *sortedDomains){
    int depth = totalNumDomains / NumPart;
    int currDepth{0}, currPart{0}, currSize{0};
    auto begin = std::chrono::high_resolution_clock::now();
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
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsed_secs = end - begin;
    std::cout << "add() in  " << elapsed_secs.count() << "s\n";
    begin = std::chrono::high_resolution_clock::now();
    index->index();
    end = std::chrono::high_resolution_clock::now();
    elapsed_secs = end - begin;
    std::cout << "index() in  " << elapsed_secs.count() << "s\n";
}