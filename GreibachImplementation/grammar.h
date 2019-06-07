#ifndef GRAMMAR_H
#define GRAMMAR_H

// Headers for the class
#include "greibachnormalformutilities.h"
#include "algorithmvariables.h"
#include "dataword.h"


// This class represents a formal grammar in the Greibach Normal Form (GNF).
// The internal memory structure of this represntation is compatible for use
// with the genetic operators of the Standard Genetic Algorithm (SGA).
//
// * The internal memory structure is intact during the lifetime of an instance
// * in order to avoid redundant genotype-to-phenotype mappings during the runtime
// * of the genetic algorithm.

enum {Negative = 0, Positive = 1};
enum {Strict = 0, Unristricted = 1};

class Grammar
{
public:
    Grammar(AlgorithmVariables &Vars);          // Random constructor -> From sets {TerminalSymbols,NonTerminalSymbols}
                                                // generate a random grammar in the GNF
    Grammar(GrammarCodonPtr G, size_t len);     // Explicit constructor -> From a GA genome string convert to GNF
    ~Grammar();                                 // Destructor -> Free any allocated memory
    void print() const;                         // Print the grammar rule by rule
    void printRule(size_t Rule) const;          // Print the rule [Rule]
    void parse(DataWord &data,                  // Check if the dataword [data] belongs in the grammar
               AlgorithmVariables &V,           // and update the fitness
               bool dataOrigin);
    float getFitness() const;                   // Return the fitness of the individual
    GrammarCodonPtr copyGen();                  // Make a copy of the genome
    size_t size();                              // Length of the genome
    // crossover functions
    GrammarCodonPtr copyTo(size_t index);       // Copy genome [0,index)
    GrammarCodonPtr copyFrom(size_t index);     // Copy genome [index,end)
    size_t setOrigin(size_t offset);            // Terminal or Non-terminal in offset
    float setFitness(float f);                  // Set the fitness of the individual
    // Mutation
    void mutate(AlgorithmVariables &V);         // Replace a random symbol
    // Invalid GNFs checkink
    bool validGNF(AlgorithmVariables &V,        // If the GNF has: 1) Symbol 0 in the head of a rule
            bool strictness = Unristricted);    //                 2) At least two rules 3) At least 1 rule : RuleLen=2
                                                //                 4) All rules length <= maxRuleLen

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
    // Parsing functions for the parsing tree
    inline bool parse(DataWord &w, size_t wStart, size_t wEnd, size_t Head, size_t &depth);
    inline bool parse(DataWord &w, size_t wStart, size_t wEnd, GrammarCodonPtr FirstHead,
               GrammarCodonPtr LastHead, size_t &depth);
    float fitness;                            // fitness of the individual
};

#endif // GRAMMAR_H
