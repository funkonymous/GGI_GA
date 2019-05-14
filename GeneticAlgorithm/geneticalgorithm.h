#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

// headers
#include "enumterminalsmap.h"
#include "algorithmvariables.h"
#include "database.h"
#include "population.h"

namespace ggi {

class GeneticAlgorithm
{
public:
    GeneticAlgorithm(int argc, char **argv);    // Initialize from command line
    ~GeneticAlgorithm();                        // Free any allocated memory

private:
    // opaque pointers for general storage classes
    EnumTerminalsMap *Map;
    AlgorithmVariables *Vars;
    DataBase *PositiveData;                     // Positive dataset
    DataBase *NegativeData;                     // Negative dataset
    Population* Pool;                           // Population
    // private genetic algorithm methods
    void iterate();                             // Run an iteration of the algorithm
};

}
#endif // GENETICALGORITHM_H
