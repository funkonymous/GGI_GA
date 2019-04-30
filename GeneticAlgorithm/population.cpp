#include "population.h"
#include "iostream"
#include "sgautilities.h"

Population::Population(AlgorithmVariables Vars) : populationSize(Vars.getPoolSize())
{
    std::cout << "Initializing population" << std::endl;
    ez::ezETAProgressBar eta(populationSize);
    eta.start();
    pool = new Grammar*[populationSize];
    for(size_t i = 0 ; i <  populationSize ; ++i){
        pool[i] = new Grammar(Vars);
        ++eta;
        //printf("\33[2K\r");
    }
    eta.reset();
}

Population::~Population(){
    for(size_t i = 0 ; i <  populationSize ; ++i){
        delete pool[i];
    }
    delete pool;
}
