#ifndef GREIBACHNORMALFORMUTILITIES_H
#define GREIBACHNORMALFORMUTILITIES_H

#include <stdio.h>

//+--------------- Grammar Utilities -----------------------+
// The building block of an individuals genome to be
// stored in a grammar instance.
// See grammar.h for more info
enum {Terminal = 0, NonTerminal = 1}; // Distinguished set origin of the symbol
struct grammarCodon{
    size_t Symbol;                    // Symbol value
    bool SetOrigin;                   // Terminal or Non-Terminal? That is the question
    struct grammarCodon *nextCodon;   // Next codon in a genome
};

typedef grammarCodon GrammarCodon;
typedef grammarCodon *GrammarCodonPtr;
//+---------------------------------------------------------+

#endif // GREIBACHNORMALFORMUTILITIES_H
