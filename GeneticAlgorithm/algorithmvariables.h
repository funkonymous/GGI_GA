#ifndef ALGORITHMVARIABLES_H
#define ALGORITHMVARIABLES_H

#include <stdio.h>
#include "greibachsets.h"
#include <string>

// Here are stored all the variables of the algorithm of grammatical inference.
// Changes in this class members take effect during the runtime of the algorithm
// when this is possible but some members should not be changed.
//
// * There are predefined values that change through set methods as it would be
// * really long to implement a constructor with 9 variables.

// Na grapsw set/get methodous gia kathe member

enum {TP = 0, FP = 1, FN = 2, TN = 3};

class GreibachSets;

class AlgorithmVariables
{
public:
    AlgorithmVariables();                      // Dummy constructor
    // Get methods
    size_t getNoNonTerms() const;              // Get number of non-terminal symbols
    size_t getTerm() const;                    // Get a random Terminal
    size_t getNonTerm() const;                 // Get a random Non-Terminal
    size_t getMaxRuleLen() const;              // Get the maximum size of a rule in a GNF
    size_t getMaxNoRules() const;              // Get the maximum number of rules in a GNF
    size_t getPoolSize() const;                // Get the number of individuals for each generation
    size_t getWeight(size_t index) const;      // Get the weight (TP,FN,FP,TN)
    float getSubparse() const;                 // Get the subparse variable
    // Set methods
    void setGNFsets(EnumTerminalsMap &M);      // This must be done during initialization
    void setMaxRuleLen(size_t length);         // Set the maximum length of rule
    void setMaxNofRules(size_t num);           // Set the maximum length of rule
    void setPoolSize(size_t size);             // Set the number of individuals in every population
    void setMaxGenerations(size_t num);        // Set the maximum number of generations for the algorithm
    void setMutationRate(float rate);          // Set the mutation rate
    void setNoNterms(size_t size);             // Set the number of non-terminals
    void setParentalPortion(float p);          // Set the percentage of individuals that contribute to the next gen.
    void setSubParse(float s);                 // Set the subparse variable
    void setConfMatrix(float tp, float fp,
                       float fn, float tn);    // Set the confusion matrix
    void setConvergenceFit(float f);           // Set the convergence fitness
    void setElitism(float e);                  // Set the elitism
    void setMaxGenLength(int l);               // Set the maximum genome length
    void setLogFile(std::string log);          // Set the log file
    void setLogImage(std::string plot);        // Set the plotted images name
    void calculateConvFitness(size_t pos,
                              size_t neg);     // Calculate the absolute convergence fitness
    // Print method
    void print() const;                        // Print the current state of the algorithm's variables
private:
    // SGA variables
    float mutationRate = 0.03;      // Mutation rate 0.03 = 3%
    size_t poolSize = 1000;         // Number of individuals in a generation
    float ParentalPortion = 0.85;   // Natural selection percentage
    float elitism = 0.03;           // Percentage of individuals kept for next pool
    size_t maxGenomeLength = 250;   // Maximum genome length for each individual
    // Termination criterions
    size_t maxGens = 500;           // Maximum number of generations
    float terminationFitness = 0.9; // Accepted convergence fitness out of 1
    float absConvFitness = 0.0;     // Absolute value of convergence fitness
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
    // Logfiles
    std::string logfile = std::string("log.txt");    // Fitness
    std::string logimage = std::string("log.png");   // Plots
};

#endif // ALGORITHMVARIABLES_H
