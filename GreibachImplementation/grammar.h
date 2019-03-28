#ifndef GRAMMAR_H
#define GRAMMAR_H

// Headers for the class
#include "greibachnormalformutilities.h"
#include "algorithmvariables.h"

// This class represents a formal grammar in the Greibach Normal Form (GNF).
// The internal memory structure of this represntation is compatible for use
// with the genetic operators of the Standard Genetic Algorithm (SGA).
//
// * The internal memory structure is intact during the lifetime of an instance
// * in order to avoid redundant genotype-to-phenotype mappings during the runtime
// * of the genetic algorithm.

class Grammar
{
public:
    Grammar(AlgorithmVariables &Vars);  // Random constructor -> From sets {TerminalSymbols,NonTerminalSymbols}
                                        // generate a random grammar in the GNF
    //Grammar();                        // Explicit constructor -> From a GA genome string convert to GNF
    ~Grammar();                         // Destructor -> Free any allocated memory

private:
    GrammarCodonPtr Genome; //
};

#endif // GRAMMAR_H
