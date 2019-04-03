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
    Grammar(AlgorithmVariables &Vars);      // Random constructor -> From sets {TerminalSymbols,NonTerminalSymbols}
                                            // generate a random grammar in the GNF
    //Grammar();                            // Explicit constructor -> From a GA genome string convert to GNF
    ~Grammar();                             // Destructor -> Free any allocated memory
    void print() const;                     // Print the grammar rule by rule

private:
    // Pointers to the grammar
    GrammarCodonPtr Genome;                   // Pointer to start of the genome that represents a GNF
    GrammarCodonPtr LastCodon;                // Pointer to the last symbol of the genome
    GrammarCodonPtr *Rules;                   // Vector of pointers to the heads of the rules
    size_t *RulesLen;                         // Vector of lengths of the rules pointed by the above vector
    // Grammar counters
    size_t NumberOfRules;                     // Number of rules in the genome
    size_t GenomeLength;                      // Number of symbols in the whole grammar
                                              // Generate a rule in the Greibach Normal Form     o---+
    // In this method only V is a true variable, everything else is a value changed by reference     |
    // or by a direct pointer to the memory block that a struct exists                               |
    GrammarCodonPtr generateRule(AlgorithmVariables &V, GrammarCodonPtr *LastC, size_t &Len); // <---+
    // Get methods for the parser
    size_t ruleLength(size_t Rule) const;     // Return the length of the rule in Symbols
    size_t ruleHead(size_t Rule) const;       // Return the head of rule [Rule]
    size_t ruleTerminal(size_t Rule) const;   // Return the terminal symbol of the rule [Rule]
    void ruleBody(size_t Rule, GrammarCodonPtr *Start,
                  GrammarCodonPtr *End);      // Return the start and the end of the body through pointers
};

#endif // GRAMMAR_H
