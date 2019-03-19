#include "dataword.h"

// Headers
#include <iostream>

// Helpful functions for the back-end of the class
void insertLetter(LetterPtr *word, char c,EnumTerminalsMap &m);  // Push a letter in the word
void printWord(LetterPtr word);                                  // Print enumerated word

//Constructor
DataWord::DataWord(std::string w,EnumTerminalsMap &m) : word(NULL), wordLength(w.size())
{
    for(size_t i = 0;i<wordLength;++i) insertLetter(&word, w[i], m);
}

//Destructor
DataWord::~DataWord(){
    LetterPtr currPtr;
    LetterPtr head = word;
    while ((currPtr = head) != NULL) {             // set curr to head, stop if list empty.
        head = head->nextLetter;                   // advance head to next element.
        free (currPtr);                            // delete saved pointer.
    }
    //std::cout << "Freed memory for data word" << std::endl;
}

//Operator overloading
size_t DataWord::operator[](size_t n){
    if(n >= wordLength){                                                  // index out of bounds
        std::cout << "DataWord index out of bounds. Operator Word[n] " << // exception handling
                     "ignored and returned zero instead!!" << std::endl;
        return 0;
    }
    LetterPtr currPtr = word;
    for(size_t i = 0; i < n; ++i){
        if(currPtr->nextLetter == NULL) std::cout << "Bad memory read!!"  // exception handling
                                                  << std::endl;
        currPtr = currPtr->nextLetter;
    }
    return currPtr->value;                                                // return nth letter
}

void DataWord::printWord(){
    LetterPtr currPtr = word;
    for(size_t i = 0; i < wordLength; ++i){
        std::cout << currPtr->value << " ";
        currPtr = currPtr->nextLetter;
    }
    std::cout << std::endl;
}

size_t DataWord::size(){
    return wordLength;
}

void insertLetter(LetterPtr *word, char c,EnumTerminalsMap &m){
    LetterPtr newPtr = (LetterPtr) malloc( sizeof(Letter) );           // New letter
    LetterPtr currPtr = *word;                                         // Ptr to the word structure
    if(newPtr != NULL){                                                // Memory allocated
        newPtr->value = m.returnEnum(c);                               // letter value
        newPtr->nextLetter = NULL;                                     // end of struct
        if(*word == NULL ) *word = newPtr;                             // first symbol
        else{
            while (currPtr->nextLetter) currPtr = currPtr->nextLetter; // find last letter in word
            currPtr->nextLetter = newPtr;                              // Push new letter
        }
    }
    else std::cout << "Out of memory...(Word creation)" << std::endl;  // Failed to allocate memory
}
