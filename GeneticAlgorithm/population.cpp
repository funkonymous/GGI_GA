#include "population.h"
#include "iostream"
#include "sgautilities.h"
#include <exception>
#include <algorithm>

Population::Population(AlgorithmVariables &Vars) : populationSize(Vars.getPoolSize())
{
    std::cout << "Initializing population" << std::endl;
    ez::ezETAProgressBar eta(populationSize);
    eta.start();
    pool = new Grammar*[populationSize];
    for(size_t i = 0 ; i <  populationSize ; ++i){
        pool[i] = new Grammar(Vars);
        ++eta;
    }
    eta.reset();
    std::cout << "\e[A\r                                                     " <<
                 "             \r";   // erase console output
    std::cout << "Population initialized." << std::endl;
}

Population::~Population(){
    for(size_t i = 0 ; i <  populationSize ; ++i){
        delete pool[i];
    }
    delete pool;
    std::cout << "Freed memory for " << populationSize << " grammars in the pool." << std::endl;
}

void Population::parse(DataBase &dat, AlgorithmVariables &V, bool dataOrigin){
    ez::ezETAProgressBar eta((populationSize)*dat.size());
    eta.start();
    for(size_t i = 0; i < populationSize; ++i){
        for(size_t j = 0; j < dat.size(); ++j){
            pool[i]->parse(dat[j],V,dataOrigin);
            ++eta;
        }
    }
    std::cout << "\e[A\r                                                     " <<
                 "             \r";   // erase console output
}

void Population::sortPool(){
    //*
    std::sort(pool, pool + populationSize,
              [](Grammar const * a, Grammar const * b) -> bool
              { return a->getFitness() >= b->getFitness(); } ); //*/ lambda expression
}

void Population::nextPool(AlgorithmVariables &V){
    Grammar **newPool; // the next generation
    newPool = new Grammar*[populationSize];
    sortPool();

    // Elitism migration
    for(size_t i = 0; i<V.getElitismRate()*populationSize; ++i){
        newPool[i] = new Grammar(pool[i]->copyGen(),pool[i]->size());
    }

}

size_t Population::getTicket(AlgorithmVariables &V){
    size_t tickets = 0;
    size_t i;
    for(i = 0; i < (int) (V.getParentalPortion()*populationSize); ++i ){
        tickets += pool[i]->getFitness() -
                pool[(int) (V.getParentalPortion()*populationSize)-1]->getFitness();
    }
    size_t ticket = rand()%tickets;
    for(i = 0; i < (int) (V.getParentalPortion()*populationSize); ++i ){
        ticket -= pool[i]->getFitness() -
                pool[(int) (V.getParentalPortion()*populationSize)-1]->getFitness();
        if(ticket < 0) break;
    }
    return i;
}
