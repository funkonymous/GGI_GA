#ifndef POPULATION_H
#define POPULATION_H

#include "algorithmvariables.h"
#include "grammar.h"


class Population
{
public:
    Population(AlgorithmVariables Vars);  // explicit constructor
    ~Population();                        // destructor
private:
    size_t populationSize;
    Grammar **pool;    // This is a matrix of pointers to grammars
};

#endif // POPULATION_H
