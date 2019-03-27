#ifndef GREIBACHSETS_H
#define GREIBACHSETS_H

#include "enumterminalsmap.h"

// This class represents is a container of the boundaries of the sets (S,N,T) of a formal
// grammar in the Greibach Normal Form. The boundaries are saved in an enumerated form to
// be later used by the algorithm. The original terminal symbols are stored in an instance
// of the EnumTerminalsMap class.
//
// * S <- Starting symbol
// * N <- Non-Terminals set
// * T <- Terminals set
//
// * Random selections from the sets are implemented for initialization of the population
// * pool.
//
// Example: Consider a grammar with set sizes TSize (Terminals) and NTSize (Non-Terminals)
//
// The enumeration boundaries are created as:
// +--------+-----------+----------------+
// | Set    | From      | To             |
// +--------+-----------+----------------+
// | S      |      0    |              0 |
// +--------+-----------+----------------+
// | T      |      1    |          TSize |
// +--------+-----------+----------------+
// | N      | TSize + 1 | TSize + NTsize |
// +--------+-----------+----------------+
//
// The above table implies that a set S = [From, To] (not [From, To)!).

class GreibachSets
{
public:
    GreibachSets(EnumTerminalsMap &m, size_t NonTermSize);  // Constructor of the sets boundaries
    ~GreibachSets();                                        // Dummy destructor
    void printSets() const;                                 // Print the enumerated sets boundaries
    size_t getRandomTerminal() const;                       // Select a random symbol from set T
    size_t getRandomNonTerminal() const;                    // Select a random symbol from (N U S)
private:
    size_t StartSymbol;       // Starting symbol numerical representation
    size_t TerminalsStart;    // Start of Terminal Symbols set numerical representation
    size_t TerminalsEnd;      // End of Terminal Symbols set numerical representation
    size_t NonTerminalStart;  // Start of Non-Terminal Symbols set numerical representation
    size_t NonTerminalEnd;    // End of Non-Terminal Symbols set numerical representation
};

#endif // GREIBACHSETS_H
