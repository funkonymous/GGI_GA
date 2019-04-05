#ifndef ALGORITHMVARIABLES_H
#define ALGORITHMVARIABLES_H

#include <stdio.h>
#include <greibachsets.h>

// Here are stored all the variables of the algorithm of grammatical inference.
// Changes in this class members take effect during the runtime of the algorithm
// when this is possible but some members should not be changed.
//
// * There are predefined values that change through set methods as it would be
// * really long to implement a constructor with 9 variables.

// Na grapsw set/get methodous gia kathe member

class GreibachSets;

class AlgorithmVariables
{
public:
    AlgorithmVariables();                 // Dummy constructor
    // Get methods
    size_t getNoNonTerms() const;
    size_t getTerm() const;               // Get a random Terminal
    size_t getNonTerm() const;            // Get a random Non-Terminal
    size_t getMaxRuleLen() const;         // Get the maximum size of a rule in a GNF
    size_t getMaxNoRules() const;         // Get the maximum number of rules in a GNF
    // Set methods
    void setGNFsets(EnumTerminalsMap &M); // This must be done during initialization
    void setMaxRuleLen(size_t length);    // Set the maximum length of rule
    // TODO
    // void printAlgoVars() const;
private:
    // SGA variables
    float mutationRate = 0.03;      // Mutation rate 0.03 = 3%
    size_t poolSize = 1000;         // Number of individuals in a generation
    float ParentalPortion = 0.85;   // Natural selection percentage
    float elitism = 0.03;           // Percentage of individuals kept for next pool
    // GNF variables
    GreibachSets Gsets;             // The sets of terminal and non-terminal symbols
    size_t NoNTerms = 20;           // Non-Terminals set size
    size_t MaxRuleLen = 5;          // Max number of symbols to a production rule Symbols = [2~MaxRuleLen]
    size_t MaxNoRules = 50;         // Max number of production rules
    float subParse = 0.01;          // Partial parse of a word contribution
    // Fitness estimation
    float weightsMatrix[2][2] = { { 1.0, 1.0 } , { 1.0, 1.0} };
    // +----+----+
    // | TP | FP |
    // +----+----+  <-- weights matrix effect on the fitness estimation
    // | FN | TN |
    // +----+----+
};

#endif // ALGORITHMVARIABLES_H
