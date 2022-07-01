#ifndef bootstrap
#define bootstrap
#include "lshensemble.hpp"
#include "lshforest.hpp"

class Lshforest;
void  BootstrapLshEnsembleEquiDepth(int, int, int, int, domainRecord *);
void bootstrapEquiDepth(std::vector<LshEnsemble*> , int, domainRecord *);
void saveIndex(int , LshEnsemble *);


#endif
