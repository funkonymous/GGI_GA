#include "algorithmvariables.h"

#include <iostream>

AlgorithmVariables::AlgorithmVariables()
{
    ; // dummy constructor
}

size_t AlgorithmVariables::getNoNonTerms() const{
    return NoNTerms;
}

void AlgorithmVariables::setGNFsets(EnumTerminalsMap &M){
    Gsets = GreibachSets(M,NoNTerms);  // Set the sets T,N
}

size_t AlgorithmVariables::getTerm() const{
    return Gsets.getRandomTerminal();
}

size_t AlgorithmVariables::getNonTerm() const{
    return Gsets.getRandomNonTerminal();
}

size_t AlgorithmVariables::getMaxRuleLen() const{
    return MaxRuleLen;
}

size_t AlgorithmVariables::getMaxNoRules() const{
    return MaxNoRules;
}

void AlgorithmVariables::setMaxRuleLen(size_t length){
    MaxRuleLen = length;
    maxGenomeLength = MaxRuleLen*MaxNoRules;
}

size_t AlgorithmVariables::getPoolSize() const{
    return poolSize;
}

void AlgorithmVariables::setPoolSize(size_t size){
    poolSize = size;
}

void AlgorithmVariables::setMaxNofRules(size_t num){
    MaxNoRules = num;
    maxGenomeLength = MaxRuleLen*MaxNoRules;
}

void AlgorithmVariables::setMaxGenerations(size_t num){
    maxGens = num;
}

void AlgorithmVariables::setMutationRate(float rate){
    mutationRate = rate;
}

void AlgorithmVariables::setNoNterms(size_t size){
    NoNTerms = size;
}

void AlgorithmVariables::setParentalPortion(float p){
    ParentalPortion = p;
}

void AlgorithmVariables::setSubParse(float s){
    subParse = s;
}

void AlgorithmVariables::setConvergenceFit(float f){
    terminationFitness = f;
}

void AlgorithmVariables::setElitism(float e){
    elitism = e;
}

void AlgorithmVariables::setConfMatrix(float tp, float fp, float fn, float tn){
    weightsMatrix[0][0] = tp;
    weightsMatrix[0][1] = fp;
    weightsMatrix[1][0] = fn;
    weightsMatrix[1][1] = tn;
}

void AlgorithmVariables::setMaxGenLength(int l){
    maxGenomeLength = l;
}

void AlgorithmVariables::setLogFile(std::string log){
    logfile = log;
}

void AlgorithmVariables::setLogImage(std::string plot){
    logimage = plot;
}

void AlgorithmVariables::calculateConvFitness(size_t pos, size_t neg){
    absConvFitness = terminationFitness * (pos * getWeight(TP) + neg * getWeight(TN));
}

size_t AlgorithmVariables::getWeight(size_t index) const{
    switch(index){
        case TP :
            return weightsMatrix[0][0];
            break;
        case FP :
            return weightsMatrix[0][1];
            break;
        case FN :
            return weightsMatrix[1][0];
            break;
        case TN :
            return weightsMatrix[1][1];
            break;
        default :
            return 1;
            break;
    }
}

float AlgorithmVariables::getSubparse() const{
    return subParse;
}

void AlgorithmVariables::print() const{
    std::cout << " ~ Greibach grammatical inference algorithm running with variables ~" << std::endl;
    std::cout << "   -> Genetic algorithm variables : " << std::endl;
    std::cout << "\t 1) Pool size : " << poolSize << std::endl;
    std::cout << "\t 2) Mutation Rate : " << mutationRate << std::endl;
    std::cout << "\t 3) Elitism : " << elitism << std::endl;
    std::cout << "\t 4) Parental portion : " << ParentalPortion << std::endl;
    std::cout << "\t 5) Maximum number of generations : " << maxGens << std::endl;
    std::cout << "\t 6) Convergence fitness rate : " << terminationFitness << std::endl;
    std::cout << "\t 7) Confusion matrix for fitness estimation : " << "\n\t >>" <<
                 " TP : " << weightsMatrix[0][0] << " || FP : " << weightsMatrix[0][1] <<
                 " || FN : " << weightsMatrix[1][0] << " || TN : " << weightsMatrix[1][1] << std::endl;
    std::cout << "\t 8) Absolute convergence fitness value : " << absConvFitness << std::endl;
    std::cout << "   -> Greibach Normal Form variables : " << std::endl;
    std::cout << "\t 1) Number of non-terminal symbols : " << NoNTerms << std::endl;
    std::cout << "\t 2) Maximum rule length in the initial population : " << MaxRuleLen << std::endl;
    std::cout << "\t 3) Maximum number of rules in the initial population : " << MaxNoRules << std::endl;
    std::cout << "\t 4) Subparse variable : " << subParse << std::endl;
    std::cout << "   -> Log files : " << std::endl;
    std::cout << "\t 1) Text log : " << logfile << std::endl;
    std::cout << "\t 2) Plotted graph : " << logimage << std::endl;
}
