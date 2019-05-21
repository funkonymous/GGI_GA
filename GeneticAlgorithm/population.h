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
    void printBestFit();                  // Print the best fitness in the pool
    float getBestFit();                   // Get the best fitness in the pool
    float getElitFit();                   // Get the average elite fitness in the pool
private:
    // Data members
    size_t populationSize;
    Grammar **pool;                           // This is a matrix of pointers to grammars
    float bestFit;
    float elitFit;
    // private methods
    void sortPool();                          // Sort the individuals
    size_t getTicket(AlgorithmVariables &V);  // Ticket for crossover probability estimation
    GrammarCodonPtr crossover(Grammar *A,
       Grammar *B, AlgorithmVariables &V,
                              size_t &size);  // Crossover operator
};

#endif // POPULATION_H
