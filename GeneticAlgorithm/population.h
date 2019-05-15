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
    void nextPool(AlgorithmVariables &V); // Derive the next generation
private:
    // Data members
    size_t populationSize;
    Grammar **pool;                           // This is a matrix of pointers to grammars
    // private methods
    void sortPool();                          // Sort the individuals
    size_t getTicket(AlgorithmVariables &V);  // Ticket for crossover probability estimation
};

#endif // POPULATION_H
