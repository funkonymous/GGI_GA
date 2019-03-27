#ifndef GRAMMAR_H
#define GRAMMAR_H

// This class represents a formal grammar in the Greibach Normal Form (GNF).
// The internal memory structure of this represntation is compatible for use
// with the genetic operators of the Standard Genetic Algorithm (SGA).

class Grammar
{
public:
    Grammar();              // Random constructor -> From sets {TerminalSymbols,NonTerminalSymbols}
                            // generate a random grammar in the GNF
    Grammar();              // Explicit constructor -> From a GA genome string convert to GNF
    ~Grammar();             // Destructor -> Free any allocated memory

private:
};

#endif // GRAMMAR_H
