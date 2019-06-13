#include "dataword.h"
#include <string>

// Headers
#include <iostream>


//Constructors
DataWord::DataWord(size_t maxLen,EnumTerminalsMap &m){
    wordLength = rand()%(maxLen) + 1;
    word = (size_t *) malloc(wordLength * sizeof(size_t) );
    for(size_t i = 0; i < wordLength; ++i){
        word[i] = rand()%(m.getMapSize()) + 1;
    }
}

DataWord::DataWord(std::string w,EnumTerminalsMap &m) : wordLength(0)
{
    for(size_t i = 0; i < w.size();++i){
        if(w[i] == '(') wordLength++;
    }
    std::string Letter;
    size_t offset = 0;
    word = (size_t *) malloc(wordLength*sizeof(size_t));              // allocate needed memory
    for(size_t i = 0;i<w.size();++i){                                 // save enumerated word in
                                                                      // the allocated memory
        if((char) w[i] == '(' ){
            Letter.clear();
        }
        else if ( (char) w[i] == ')' ){
            word[offset] = m.returnEnum(Letter);
            offset++;
        }
        else{
            Letter.push_back(w[i]);
        }
    }
}

//Destructor
DataWord::~DataWord(){
    free(word);  // free any allocated memory
}

//Operator overloading
size_t DataWord::operator[](size_t n){
    if(n >= wordLength){                                                  // index out of bounds
        std::cout << "DataWord index out of bounds. Operator Word[n] " << // exception handling
                     "ignored and returned zero instead!!" << std::endl;
        //getchar();
        return 0;
    }
    return word[n];
}

void DataWord::printWord() const{
    for(size_t i = 0; i < wordLength;++i){
        std::cout << word[i] << " ";
    }
    std::cout << std::endl;
}

size_t DataWord::size() const{
    return wordLength;
}


