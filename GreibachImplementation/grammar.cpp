#include "grammar.h"
#include <iostream>

GrammarCodonPtr createNonTerm(AlgorithmVariables &V);

Grammar::Grammar(AlgorithmVariables &Vars)
    : NumberOfRules(0), GenomeLength(0)
{
    size_t length = 0; // This variable will be returned by reference
    Rules = (GrammarCodonPtr*) malloc( Vars.getMaxNoRules()*sizeof(GrammarCodonPtr) ); // Pointers to rules
    RulesLen = (size_t *) malloc( Vars.getMaxNoRules()*sizeof(size_t) ); // Rules length

    // Generate the first rule as every grammar must have at least one rule
    Genome = generateRule(Vars,&LastCodon,length);
    GenomeLength+=length;
    GrammarCodonPtr CurrLastPtr = LastCodon; // This pointer is used for appending the genome
    Rules[0] = Genome;
    RulesLen[0] = length;
    NumberOfRules++;

    // Generate the rest of the rules
    for(size_t i = 0; i < Vars.getMaxNoRules()-1; ++i){
        if(!(rand()%(Vars.getMaxNoRules()-i)));                        // equal probability to break for every number of rules
        CurrLastPtr->nextCodon = generateRule(Vars,&LastCodon,length); // generate rule
        Rules[NumberOfRules] = CurrLastPtr->nextCodon;                 // Update rules pointer
        RulesLen[NumberOfRules] = length;                              // Update length of each rule
        CurrLastPtr = LastCodon;                                       // Update Last Symbol Pointer
        GenomeLength += length;                                        // | Update counters
        NumberOfRules++;                                               // |
    }

}

Grammar::~Grammar(){
    GrammarCodonPtr currPtr;
    GrammarCodonPtr head = Genome;
    while ((currPtr = head) != NULL) {             // set curr to head, stop if list empty.
        head = head->nextCodon;                    // advance head to next element.
        free (currPtr);                            // delete saved pointer.
    }
    free(Rules);
    free(RulesLen);
    std::cout << "Freed memory for " << GenomeLength
              << " Symbols in the genome" << std::endl;
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

void Grammar::print() const{
    GrammarCodonPtr currPtr;
    for(size_t i = 0; i < NumberOfRules; ++i){
        currPtr = Rules[i];
        for(size_t j = 0; j < RulesLen[i] - 1 ; ++j){
            std::cout << currPtr->Symbol << " ";
            currPtr = currPtr->nextCodon;
        }
        std::cout << currPtr->Symbol << std::endl;
    }

}

size_t Grammar::ruleLength(size_t Rule) const{
    if(Rule>=NumberOfRules){
        std::cout << "Invalid index in rules accessing of Grammar" << std::endl;
        return 0;
    }
    return RulesLen[Rule];
}

size_t Grammar::ruleHead(size_t Rule) const{
    if(Rule>=NumberOfRules){
        std::cout << "Invalid index in rules accessing of Grammar" << std::endl;
        return 0;
    }
    return Rules[Rule]->Symbol;
}

size_t Grammar::ruleTerminal(size_t Rule) const{
    if(Rule>=NumberOfRules){
        std::cout << "Invalid index in rules accessing of Grammar" << std::endl;
        return 0;
    }
    return (Rules[Rule]->nextCodon)->Symbol;
}

void Grammar::ruleBody(size_t Rule, GrammarCodonPtr *Start, GrammarCodonPtr *End){
    if(Rule>=NumberOfRules){
        std::cout << "Invalid index in rules accessing of Grammar" << std::endl;
        *Start = NULL;
        *End = NULL;
        return;
    }
    if(Rule == NumberOfRules - 1 && RulesLen[Rule] > 2){
        *Start = (Rules[Rule]->nextCodon)->nextCodon; // Head -> next = Terminal -> next = Body
        *End = LastCodon;
        return;
    }
    else if(Rule < NumberOfRules - 1 && RulesLen[Rule] > 2){
        *Start = (Rules[Rule]->nextCodon)->nextCodon; // Head -> next = Terminal -> next = Body
        *End = *Start;
        for(size_t i = 0; i < RulesLen[Rule] - 3; ++i){
            *End = (*End)->nextCodon;
        }
        return;
    }
    std::cout << "There are no non-terminal symbols to return in the body of the accessed rule" <<
                 std::endl;
    *Start = NULL;
    *End = NULL;
}

GrammarCodonPtr createNonTerm(AlgorithmVariables &V){
    GrammarCodonPtr c = (GrammarCodonPtr) malloc( sizeof(GrammarCodonPtr) );
    c->Symbol = V.getNonTerm();
    c->SetOrigin = NonTerminal;
    c->nextCodon = NULL;
    return c;
}
