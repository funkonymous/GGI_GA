#ifndef DATAUTILITIES_H
#define DATAUTILITIES_H


//+-------------- DataWord Utilities -------------------------------+
// The building block of the database. Each word is defined as a list.
// See dataword.h for more info.
struct letter{
    size_t value;
    struct letter *nextLetter;
};

typedef letter Letter;
typedef Letter *LetterPtr;
//+-----------------------------------------------------------------+


//+-------------- EnumTerminals Map Utilities ----------------------+
// The building block of the enumeration map.
// See enumterminals.h for more info.
struct symbolMap{
    size_t value;
    char letter;
    size_t timesFound;
    struct symbolMap *nextSymbol;
};

typedef symbolMap SymbolMap;
typedef symbolMap *SymbolMapPtr;
//+-----------------------------------------------------------------+


//+-------------- Database Utilities -------------------------------+
// The building block of the DataBase.
// See database.h for more info.

class DataWord;
struct wordStruct{
    DataWord *word;
    struct wordStruct *nextword;
};

typedef wordStruct WordStruct;
typedef WordStruct* WordStructPtr;
//+-----------------------------------------------------------------+

#endif // DATAUTILITIES_H
