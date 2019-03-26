#ifndef DATAWORD_H
#define DATAWORD_H

#include <string>
#include "datautilities.h"
#include "enumterminalsmap.h"

// A class for each word in the dataset is implemented in order for
// each word to be stored.
//
//  * Dynamic allocation of memory needed for each instance but in
//  * vectorized way.
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
//      +----------------+----------+----------+----------+
//      | Memory Pointer | word     | word + 1 | word + 2 |
//      +----------------+----------+----------+----------+
//      | Value          | 2        | 1        | 3        |
//      +----------------+----------+----------+----------+

class DataWord
{
public:
    DataWord(std::string w,EnumTerminalsMap &m); // Create the representation of the string
                                                 // in enumerated form
    ~DataWord();                                 // Free any allocated memory
    size_t operator[](size_t n);                 // Get the nth symbol matrix-alike style
    void printWord() const;                      // Print the enumerated word
    size_t size() const;                         // The number of letters in the word
private:
    size_t *word;           // ponter to the word
    size_t wordLength;      // Length of the word
};

#endif // DATAWORD_H
