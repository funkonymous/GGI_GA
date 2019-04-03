#include "grammar.h"
#include <iostream>

GrammarCodonPtr createNonTerm(AlgorithmVariables &V);

Grammar::Grammar(AlgorithmVariables &Vars)
    : NumberOfRules(0), GenomeLength(0)
{
    size_t length = 0; // This variable will be returned by reference

    // Generate the first rule as every grammar must have at least one rule
    Genome = generateRule(Vars,&LastCodon,length);
    GenomeLength+=length;
    GrammarCodonPtr CurrLastPtr = LastCodon;
    NumberOfRules++;

    // Generate the rest of the rules
    for(size_t i = 0; i < Vars.getMaxNoRules()-1; ++i){
        CurrLastPtr->nextCodon = generateRule(Vars,&LastCodon,length);
        CurrLastPtr = LastCodon;
        GenomeLength += length;
    }

    GrammarCodonPtr CurrPtr = Genome;
    while (CurrPtr!=LastCodon) {
        std::cout << CurrPtr->Symbol << " ";
        CurrPtr = CurrPtr->nextCodon;
    }
    std::cout << CurrPtr->Symbol << std::endl;
    std::cout << GenomeLength << " " << NumberOfRules << std::endl;
}

Grammar::~Grammar(){
    ; // Na kanw free ta structs
}

GrammarCodonPtr Grammar::generateRule(AlgorithmVariables &V, GrammarCodonPtr *LastC, size_t &Len){
    // The two first symbols are explicitely written in order to preserve the GNF of the rules
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
    *LastC = Term;
    Len = 2;
    for(size_t i = 0; i < V.getMaxRuleLen() - 2; ++i){
        if(!(rand()%(V.getMaxRuleLen()-1-i))) break; // Equal probability to break for every
                                                     // possible rule length
        (*LastC)->nextCodon = createNonTerm(V);
        (*LastC) = (*LastC)->nextCodon;
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
