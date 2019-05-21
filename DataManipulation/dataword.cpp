#include "dataword.h"

// Headers
#include <iostream>


//Constructor
DataWord::DataWord(std::string w,EnumTerminalsMap &m) : wordLength(w.size())
{
    word = (size_t *) malloc(wordLength*sizeof(size_t));              // allocate needed memory
    for(size_t i = 0;i<wordLength;++i) word[i] = m.returnEnum(w[i]);  // save enumerated word in
}                                                                     // the allocated memory


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


