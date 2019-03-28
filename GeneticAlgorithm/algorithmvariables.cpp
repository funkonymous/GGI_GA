#include "algorithmvariables.h"

AlgorithmVariables::AlgorithmVariables()
{
    ; // This is a dummy constructor
}

size_t AlgorithmVariables::getNoNonTerms() const{
    return NoNTerms;
}

void AlgorithmVariables::setGNFsets(EnumTerminalsMap &M);
