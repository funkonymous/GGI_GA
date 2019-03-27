#ifndef GREIBACHSETS_H
#define GREIBACHSETS_H

#include "enumterminalsmap.h"

// This class represents

class GreibachSets
{
public:
    GreibachSets(EnumTerminalsMap &m, size_t NonTermSize);  // Constructor of the sets boundaries
    ~GreibachSets();
    void printSets() const;
    size_t getRandomTerminal() const;
    size_t getRandomNonTerminal() const;
private:
    size_t StartSymbol;
    size_t TerminalsStart;
    size_t TerminalsEnd;
    size_t NonTerminalStart;
    size_t NonTerminalEnd;
};

#endif // GREIBACHSETS_H
