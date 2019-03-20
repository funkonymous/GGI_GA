#ifndef DATAWORD_H
#define DATAWORD_H

#include <string>
#include "datautilities.h"
#include "enumterminalsmap.h"

// A class for each word in the dataset is implemented in order for
// each word to be stored.
//
//  * Every node in a list represents a letter of the word.
//
//  * Reading a string, each letter is appended in a list top-down.
//
//  * The insertion is O(1).
//
//  * Indexing in the letters of the word starts from zero up to lenght - 1
//  * C++ - alike indexing.
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
// +----------------+                          +--------------------+ // This pointer ensures
// |LetterPtr Word  |                          |LetterPtr LastLetter| // insertion in O(1)
// +----------------+                          +--------------------+ // time complexity
// | Value = 2      |    +----------------+             |
// | NextLetter     | -> | Next LetterPtr |             |
// +----------------+    +----------------+             V
//                       | Value = 1      |    +----------------+
//                       | NextLetter     | -> | Next LetterPtr |
//                       +----------------+    +----------------+
//                                             | Value = 3      |
//                                             | NextLetter     | -> nullptr
//                                             +----------------+

class DataWord
{
public:
    DataWord(std::string w,EnumTerminalsMap &m); // Create the representation of the string
                                                 // in enumerated form
    ~DataWord();                                 // Free any allocated memory
    size_t operator[](size_t n);                 // Get the nth symbol matrix-alike style
    void printWord();                            // Print the enumerated word
    size_t size();                               // The number of letters in the word
private:
    LetterPtr word;         // Head of the list that represents the word
    LetterPtr LastLetter;   // Last letter of the list in order to append faster
    size_t wordLength;      // Length of the word
};

#endif // DATAWORD_H
