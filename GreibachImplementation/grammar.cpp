#include "grammar.h"
#include <iostream>

GrammarCodonPtr createNonTerm(AlgorithmVariables &V);

Grammar::Grammar(AlgorithmVariables &Vars)
    : NumberOfRules(0), GenomeLength(0)
{
    size_t length = 0;
    Genome = generateRule(Vars,LastCodon,length);
    GenomeLength += length;
    GrammarCodonPtr CurrPtr = Genome;
    while (CurrPtr->nextCodon!=NULL) {
        std::cout << CurrPtr->Symbol << " ";
        CurrPtr = CurrPtr->nextCodon;
    }
    std::cout << CurrPtr->Symbol << std::endl;
}

Grammar::~Grammar(){
    ; // Na kanw free ta structs
}

GrammarCodonPtr Grammar::generateRule(AlgorithmVariables &V, GrammarCodonPtr LastC, size_t &Len){
    // Terminal symbol of the GNF rule
    GrammarCodonPtr Term = (GrammarCodonPtr) malloc( sizeof(GrammarCodonPtr) );
    Term->Symbol = V.getTerm();
    Term->SetOrigin = Terminal;
    Term->nextCodon = NULL;
    // Head of the rule
    GrammarCodonPtr Head = (GrammarCodonPtr) malloc( sizeof(GrammarCodonPtr) );
    Head->Symbol = V.getNonTerm();
    Head->SetOrigin = NonTerminal;
    Head->nextCodon = Term;
    LastC = Term;
    Len = 2;
    for(size_t i = 0; i < 5; ++i){
        LastC->nextCodon = createNonTerm(V);
        LastC = LastC->nextCodon;
        Len++;
    }

    return Head;
}


GrammarCodonPtr createNonTerm(AlgorithmVariables &V){
    GrammarCodonPtr c = (GrammarCodonPtr) malloc( sizeof(GrammarCodonPtr) );
    c->Symbol = V.getNonTerm();
    c->SetOrigin = NonTerminal;
    c->nextCodon = NULL;
    return c;
}
