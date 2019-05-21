#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

// headers
#include "enumterminalsmap.h"
#include "algorithmvariables.h"
#include "database.h"
#include "population.h"
#include <vector>

namespace ggi {

class GeneticAlgorithm
{
public:
    GeneticAlgorithm(int argc, char **argv);    // Initialize from command line
    ~GeneticAlgorithm();                        // Free any allocated memory
    void run();                                 // Execute the algorithm

private:
    // opaque pointers for general storage classes
    EnumTerminalsMap *Map;
    AlgorithmVariables *Vars;
    DataBase *PositiveData;                     // Positive dataset
    DataBase *NegativeData;                     // Negative dataset
    Population* Pool;                           // Population
    // private genetic algorithm methods
    void iterate();                             // Run an iteration of the algorithm
    // algorithm runtime results
    size_t iterations;                          // Iterations done
    std::vector<float> bestFit;                 // Best fitness in each iteration
    std::vector<float> elitFit;                 // Average elite fitness in each iteration
};

}
#endif // GENETICALGORITHM_H
