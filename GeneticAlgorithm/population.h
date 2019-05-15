#ifndef POPULATION_H
#define POPULATION_H

#include "algorithmvariables.h"
#include "grammar.h"
#include "database.h"


class Population
{
public:
    Population(AlgorithmVariables &Vars); // explicit constructor
    ~Population();                        // destructor

    void parse(DataBase &dat, AlgorithmVariables &V,
               bool dataOrigin);          // Parse the whole population with this dataset
    void sortPool();                      // Sort the individuals
private:
    size_t populationSize;
    Grammar **pool;    // This is a matrix of pointers to grammars
};

#endif // POPULATION_H
