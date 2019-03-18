#ifndef DATAWORD_H
#define DATAWORD_H

#include <string>
#include "enumterminalsmap.h"
#include "datautilities.h"

// A class for each words in the dataset is implemented in order for
// each word to be stored.
//
//  * Every node in a list represents a letter of the word.
//
//  * Reading a string, each letter is appended in a list top-down.
//
// Example:
//            +--------------------------------+        +-----------+
//            |            Enumeration map     |        |  String   |
//            +-------------++-----+-----+-----+        +-----------+
//            | Symbol      ||  a  |  b  |  c  |        |   B A D   |
//            +-------------++-----+-----+-----+        +-----------+
//            | Integer     ||  1  |  2  |  3  |
//            +-------------++-----+-----+-----+
//
//
//  Is represented as:
// +----------------+
// |LetterPtr Word  |
// +----------------+
// | Value = 2      |    +----------------+
// | NextLetter     | -> | Next LetterPtr |
// +----------------+    +----------------+
//                       | Value = 1      |    +----------------+
//                       | NextSymbol     | -> | Next LetterPtr |
//                       +----------------+    +----------------+
//                                             | Value = 3      |
//                                             | NextSymbol     | -> nullptr
//                                             +----------------+

class DataWord
{
public :
    DataWord(std::string w,EnumTerminalsMap &m); // Create the representation of the string
                                                 // in enumerated form
    ~DataWord();                                 // Free any allocated memory
    size_t operator[](size_t n);                 // Get the nth symbol matrix-alike style
private :
    LetterPtr word = NULL;  // Head of the list that represents the word
    int wordLength;         // Length of the word
};

#endif // DATAWORD_H
