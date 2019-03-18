#ifndef DATAUTILITIES_H
#define DATAUTILITIES_H

//+-------------- DataWord Utilities -------------------------------+
// The building block of the database. Each word is defined as a list.
// See dataword.h for more info.
struct letter{
    int value;
    struct letter *nextLetter;
};

typedef letter Letter;
typedef Letter *LetterPtr;
//+-----------------------------------------------------------------+


//+-------------- EnumTerminals Map Utilities ----------------------+
// The building block of the enumeration map.
// See enumterminals.h for more info.
struct symbolMap{
    int value;
    char letter;
    int timesFound;
    struct symbolMap *nextSymbol;
};

typedef symbolMap SymbolMap;
typedef symbolMap *SymbolMapPtr;
//+-----------------------------------------------------------------+

#endif // DATAUTILITIES_H
