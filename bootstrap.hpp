#ifndef bootstrap
#define bootstrap
#include "lshensemble.hpp"
#include "lshforest.hpp"

class Lshforest;
LshEnsemble* BootstrapLshEnsembleEquiDepth(int, int, int, int, domainRecord *);
void bootstrapEquiDepth(LshEnsemble *, int, domainRecord *);

#endif
