#include "algorithmvariables.h"

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
}

size_t AlgorithmVariables::getPoolSize() const{
    return poolSize;
}

void AlgorithmVariables::setPoolSize(size_t size){
    poolSize = size;
}

void AlgorithmVariables::setMaxNofRules(size_t num){
    MaxNoRules = num;
}
