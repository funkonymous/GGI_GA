#ifndef ENUMTERMINALSMAP_H
#define ENUMTERMINALSMAP_H

#include <string>

#include "datautilities.h"

// A map for corresponding terminal symbols and their enumerated form
// is stored.
//
//  * Every node in a list represents a symbol, its corresponding integer
//  * and how many times found.
//
//  * Reading a data file, every new symbol found is assigned an integer
//  * value and is pushed back in the list
//
//  * The enumeration starts from 1 and reaches an arbitrary integer. No
//  * integers are skipped during the enumeration.
//
// Example:
//                           Enumeration map
//            +-------------++-----+-----+-----+
//            | Symbol      ||  a  |  b  |  c  |
//            +-------------++-----+-----+-----+
//            | Integer     ||  1  |  2  |  3  |
//            +-------------++-----+-----+-----+
//            | Times Found ||  8  |  7  |  9  |
//            +-------------++-----+-----+-----+
//
//
//  Is represented as:
// +-----------------+
// |SymbolNodePtr Map|
// +-----------------+
// | Symbol = a      |
// | Value = 1       |
// | Times Found = 9 |    +------------------+
// | NextSymbol      | -> |Next SymbolNodePtr|
// +-----------------+    +------------------+
//                        | Symbol = b       |
//                        | Value = 2        |
//                        | Times Found = 7  |    +------------------+
//                        | NextSymbol       | -> |Next SymbolNodePtr|
//                        +------------------+    +------------------+
//                                                | Symbol = c       |
//                                                | Value = 3        |
//                                                | Times Found = 9  |
//                                                | NextSymbol       | -> nullptr
//                                                +------------------+

class EnumTerminalsMap
{
public:
    EnumTerminalsMap();                         // Dummy constructor
    EnumTerminalsMap(std::string fname);        // Constructor from a file
    ~EnumTerminalsMap();                        // Free any allocated memory
    void appendMapWithData(std::string fname);  // Read more data
    void print() const;                         // Print the map
    size_t returnEnum(std::string c);           // Integer value for a Symbol
    size_t getMapSize();                        // Get the max Symbol value
private:
    SymbolMapPtr Map;                           // List structure for the map
    size_t MapSize;                             // Size of the list
};

#endif // ENUMTERMINALSMAP_H
