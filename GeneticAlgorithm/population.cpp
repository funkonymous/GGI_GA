#include "population.h"
#include "iostream"
#include "sgautilities.h"
#include <exception>
#include <algorithm>
#include <omp.h>

Population::Population(AlgorithmVariables &Vars) : populationSize(Vars.getPoolSize()), bestFit(0.0), elitFit(0.0)
{
    std::cout << "Initializing population" << std::endl;
    ez::ezETAProgressBar eta(populationSize);
    eta.start();
    pool = new Grammar*[populationSize];
    for(size_t i = 0 ; i <  populationSize ; ++i){
        pool[i] = new Grammar(Vars);
        while (pool[i]->validGNF(Vars)==false) {
            delete pool[i];
            pool[i] = new Grammar(Vars);
        }
        ++eta;
    }
    eta.reset();
    std::cout << "\e[A\r                                                     " <<
                 "                                                           " <<
                 "             \r";   // erase console output
    std::cout << "Population initialized." << std::endl;
}

Population::~Population(){
    pool[0]->print();
    for(size_t i = 0 ; i <  populationSize ; ++i){
        delete pool[i];
    }
    delete pool;
    std::cout << "Freed memory for " << populationSize << " grammars in the pool." << std::endl;
}

void Population::parse(DataBase &dat, AlgorithmVariables &V, bool dataOrigin){
    int startPosition = 0;
    startPosition = V.getFirstParse() ? ((int) (V.getElitismRate()*populationSize)) : 0;
    V.setFirstParse();
//#pragma omp parallel
{
    for(size_t i = startPosition; i < populationSize; ++i){
        for(size_t j = 0; j < dat.size(); ++j){
//#pragma omp single
{
            pool[i]->parse(dat[j],V,dataOrigin);
            //++eta;

}
        }
    }
}
}


void Population::sortPool(){
    //*
    std::sort(pool, pool + populationSize,
              [](Grammar * a, Grammar * b) -> bool
              { return a->getFitness() > b->getFitness(); } ); //*/ lambda expression
    bestFit = pool[0]->getFitness();
    std::cout << pool[0]->getFitness() << " - " << pool[1]->getFitness() << " - " << pool[(int)(populationSize*0.1)]->getFitness() << " - " <<
              pool[(int)(populationSize*0.2)]->getFitness() << " - " << pool[(int)(populationSize*0.3)]->getFitness() << " - "
              << pool[(int)(populationSize*0.4)]->getFitness() << " - " << pool[(int)(populationSize*0.5)]->getFitness() << " - "
              << pool[(int)(populationSize*0.6)]->getFitness() << " - " << pool[(int)(populationSize*0.7)]->getFitness() << " - "
              << pool[(int)(populationSize*0.8)]->getFitness() << " - " << pool[(int)(populationSize*0.9)]->getFitness() << " - "
              << pool[(int)(populationSize-1)]->getFitness() << std::endl;
}

void Population::nextPool(AlgorithmVariables &V){
    Grammar *newPool[populationSize]; // the next generation
    sortPool();
    float added = 0.0;
    for(size_t i = 0; i< (int) (V.getElitismRate()*populationSize); ++i){
        added+=pool[i]->getFitness();
        newPool[i] = new Grammar(pool[i]->copyGen(),pool[i]->size());
        newPool[i]->setFitness(pool[i]->getFitness());
    }
    elitFit = added / ( V.getElitismRate()* (float) populationSize);
    if(V.getElitismRate()*populationSize>1.0){
        std::cout << "Average elite fitness : " << elitFit << std::endl;
    }
    GrammarCodonPtr newIndividual;
    for(size_t i = (int) (V.getElitismRate()*populationSize); i<populationSize; ++i){
        //std::cout << i << std::endl;
        size_t s = 0;
        do{
            newIndividual = crossover(pool[getTicket(V)],pool[getTicket(V)],V,s);
        }while (newIndividual==NULL) ;
        newPool[i] = new Grammar(newIndividual,s);
        while (newPool[i]->validGNF(V,Unristricted)==false) {
            delete newPool[i];
            do{
                newIndividual = crossover(pool[getTicket(V)],pool[getTicket(V)],V,s);
            }while (newIndividual==NULL) ;
            newPool[i] = new Grammar(newIndividual,s);
        }
        if( (float) (rand()%1000000) <= V.getMutationRate()*10000.0){
            newPool[i]->mutate(V);
        }
    }

    for(size_t i = 0; i<populationSize;++i){
        delete pool[i];
        pool[i] = newPool[i];
        //pool[i] = new Grammar(newPool[i]->copyGen(),newPool[i]->size());
        if(i < (int) (V.getElitismRate()*populationSize)) pool[i]->setFitness(newPool[i]->getFitness());
        //delete newPool[i];
    }

}

size_t Population::getTicket(AlgorithmVariables &V){
    int tickets = 0;
    if(pool[0]->getFitness()-pool[(int) (V.getParentalPortion()*populationSize)-1]->getFitness() <= 1)
        return rand()%populationSize;
    size_t i;
    for(i = 0; i < (int) (V.getParentalPortion()*populationSize); ++i ){
        tickets += pool[i]->getFitness() -
                pool[(int) (V.getParentalPortion()*populationSize)-1]->getFitness();
    }
    int ticket = rand()%tickets;
    for(i = 0; i < (int) (V.getParentalPortion()*populationSize); ++i ){
        ticket -= pool[i]->getFitness() -
                pool[(int) (V.getParentalPortion()*populationSize)-1]->getFitness();
        if(ticket < 0) break;
    }
    return i;
}

GrammarCodonPtr Population::crossover(Grammar *A, Grammar *B, AlgorithmVariables &V, size_t &size){
    // Indices for the crossover
    size_t first_index = rand()%(A->size()-2)+1;
    size_t second_index = rand()%(B->size()-2)+1;
    int tries = 0;
    // Ensure that a valid offspring is derived
    while( (first_index + B->size()-second_index) > V.getMaxGenomeLength() ||
           (first_index + B->size()-second_index) < V.getMaxGenomeLength()/2 ||
           (A->setOrigin(first_index)==Terminal && B->setOrigin(second_index) == Terminal) ||
           first_index <= 2){
        first_index = rand()%(A->size()-2)+1;
        second_index = rand()%(B->size()-2)+1;
        tries++;
        if(tries>10) return NULL;
    }
    GrammarCodonPtr derivedGenome;  // The resulting offspring will be stored here
    derivedGenome = A->copyTo(first_index);
    GrammarCodonPtr tempPtr = derivedGenome;
    while (tempPtr->nextCodon != NULL) {
        tempPtr = tempPtr->nextCodon;
    }
    tempPtr->nextCodon = B->copyFrom(second_index);
    size = first_index + B->size() - second_index;
    return derivedGenome;
}

void Population::printBestFit(){
    std::cout << "Best fitness : " << bestFit << std::endl;
}

float Population::getBestFit(){
    return bestFit;
}

float Population::getElitFit(){
    return elitFit;
}
