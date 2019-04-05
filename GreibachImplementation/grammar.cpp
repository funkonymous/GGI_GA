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
    for(size_t i = 0; i < NumberOfRules; ++i){
        printRule(i);
    }
}

void Grammar::printRule(size_t Rule) const{
    if(Rule >= NumberOfRules){  // Exception handling
        std::cout << "Cannot access and print rule " << Rule <<
                     " of grammar" << std::endl;
        return;
    }
    if(Rule == NumberOfRules - 1){
        GrammarCodonPtr currPtr = Rules[Rule];
        std::cout << currPtr->Symbol << " -> ";
        while (currPtr->nextCodon != NULL) {
            currPtr = currPtr->nextCodon;
            std::cout << currPtr->Symbol << " ";
        }
        std::cout << std::endl;
        return;
    }
    else if(Rule < NumberOfRules - 1){
        GrammarCodonPtr currPtr = Rules[Rule];
        std::cout << currPtr->Symbol << " -> ";
        while (currPtr->nextCodon != Rules[Rule+1]) {
            currPtr = currPtr->nextCodon;
            std::cout << currPtr->Symbol << " ";
        }
        std::cout << std::endl;
        return;
    }
}

size_t Grammar::ruleLength(size_t Rule) const{
    if(Rule>=NumberOfRules){   // Exception handling
        std::cout << "Invalid index in rules accessing of Grammar" << std::endl;
        return 0;
    }
    return RulesLen[Rule];
}

size_t Grammar::ruleHead(size_t Rule) const{
    if(Rule>=NumberOfRules){   // Exception handling
        std::cout << "Invalid index in rules accessing of Grammar" << std::endl;
        return 0;
    }
    return Rules[Rule]->Symbol;
}

size_t Grammar::ruleTerminal(size_t Rule) const{
    if(Rule>=NumberOfRules){   // Exception handling
        std::cout << "Invalid index in rules accessing of Grammar" << std::endl;
        return 0;
    }
    return (Rules[Rule]->nextCodon)->Symbol;
}

void Grammar::ruleBody(size_t Rule, GrammarCodonPtr *Start, GrammarCodonPtr *End){
    if(Rule>=NumberOfRules){   // Exception handling
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

bool Grammar::parse(DataWord &data){
    std::cout << "Parser initialized" << std::endl;
    return true;
}

bool Grammar::parse(DataWord &w, size_t wStart, size_t wEnd, size_t Head, size_t &depth){
    bool found = false;
    if(wStart + 1 == wEnd){ // case that the word length = 1
        for(size_t i = 0; i < NumberOfRules; ++i){
            if( (ruleHead(i) == Head)&&(ruleTerminal(i) == w[wStart])&&(ruleLength(i) == 2) ){
                depth = 0;
                return true;
            }
        }
    }
    else{
        GrammarCodonPtr BodyS, BodyE;
        for(size_t i = 0; i < NumberOfRules; ++i){
            if( (ruleHead(i) == Head)&&(ruleTerminal(i) == w[0]) ){
                if( ruleLength(i) == 2 ) found = true;
                else if (ruleLength(i) == 3){
                    ruleBody(i, &BodyS, &BodyE);
                    if(BodyS != NULL)
                        if(parse(w,wStart+1,wEnd,BodyS->Symbol,depth)) return true;
                }
                else if (ruleLength(i) > 3){
                    if(wEnd-wStart >= ruleLength(i) - 2){ // a little smart prunning
                        ruleBody(i,&BodyS,&BodyE);
                        if( BodyS!=NULL && BodyE!=NULL && BodyE!=BodyS){
                            if(parse(w,wStart+1,wEnd,BodyS,BodyE,depth)) return true;
                        }
                    }
                }
            }
        }
    }
    if(found && depth>0) depth--;
    return false;
}

bool Grammar::parse(DataWord &w, size_t wStart, size_t wEnd, GrammarCodonPtr FirstHead, GrammarCodonPtr LastHead, size_t &depth){
    if(FirstHead->nextCodon == LastHead){ // 2 terminals
        size_t depth1,depth2;
        for(size_t i = wStart + 1; i < wEnd; ++i){
            depth1 = i - wStart;
            depth2 = wEnd - i;
            if( parse(w,wStart,wStart+i,FirstHead->Symbol,depth1) &&
                    parse(w,wStart+i,wEnd,LastHead->Symbol,depth2)){
                depth = 0;
                return true;
            }
            if(depth1+depth2<depth) depth = depth1 + depth2;
        }
    }
    return false;
}

GrammarCodonPtr createNonTerm(AlgorithmVariables &V){
    GrammarCodonPtr c = (GrammarCodonPtr) malloc( sizeof(GrammarCodonPtr) );
    c->Symbol = V.getNonTerm();
    c->SetOrigin = NonTerminal;
    c->nextCodon = NULL;
    return c;
}
