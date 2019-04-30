#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

// headers
#include "enumterminalsmap.h"
#include "algorithmvariables.h"

class GeneticAlgorithm
{
public:
    GeneticAlgorithm(int argc, char **argv);    // Initialize from command line
    ~GeneticAlgorithm();                        // Free any allocated memory

private:
    // opaque pointers for general storage classes
    EnumTerminalsMap *Map;
    AlgorithmVariables *Vars;
};

#endif // GENETICALGORITHM_H
