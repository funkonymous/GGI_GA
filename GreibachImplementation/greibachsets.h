#ifndef GREIBACHSETS_H
#define GREIBACHSETS_H

#include "enumterminalsmap.h"

// This class represents

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
