#ifndef DATAUTILITIES_H
#define DATAUTILITIES_H


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

class DataWord;    // Forward declaration
struct wordStruct{
    DataWord *word; // Opaque ptr
    struct wordStruct *nextword;
};

typedef wordStruct WordStruct;
typedef WordStruct* WordStructPtr;
//+-----------------------------------------------------------------+

#endif // DATAUTILITIES_H
