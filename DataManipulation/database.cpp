#include "database.h"
#include <fstream>
#include <iostream>

// Helpful functions for the back-end of the class
WordStructPtr insertWord(WordStructPtr *word, WordStructPtr last, std::string w, EnumTerminalsMap &m);  // Push a word in the DB
                                                                                                        // and return a pointer to                                                                                                     // the last element
using namespace std;

//Constructors

DataBase::DataBase(size_t instances, size_t wordLength, EnumTerminalsMap &m)
    : data(NULL), numberOfData(instances)
{
    dataPtrs = (WordStructPtr*) malloc(numberOfData * sizeof(WordStructPtr));
    WordStructPtr firstWord = (WordStructPtr) malloc( sizeof(WordStruct) );
    firstWord->word = new DataWord(wordLength,m);
    data = lastData = dataPtrs[0] = firstWord;
    for(size_t i = 1; i < numberOfData; ++i){
        WordStructPtr newWord = (WordStructPtr) malloc( sizeof(WordStruct) );
        newWord->word = new DataWord(wordLength,m);
        newWord->nextword = NULL;
        lastData->nextword = newWord;
        dataPtrs[i] = newWord;
        lastData = lastData->nextword;
    }
}

DataBase::DataBase(std::string fname, EnumTerminalsMap &m) : data(NULL), numberOfData(0)
{
    const clock_t begin_time = clock();                       // Count time for DB generation
    string line;
    ifstream infile(fname); // open dataset
    // Find all the unique terminals for the grammar
    if(infile.is_open()){
        std::cout << "Reading file : " << fname << std::endl;
        while(getline(infile,line)){                          // Reading all lines
            lastData = insertWord(&data, lastData, line, m);  // Insert a line in the DB while
                                                              // getting the last element pointer
            numberOfData++;                                   // Add to instance counter
        }
    }
    else cout << "Could not open file " << fname << "!!" << endl;
    dataPtrs = (WordStructPtr*) malloc(numberOfData * sizeof(WordStructPtr));
    WordStructPtr tempPtr = data;
    for(size_t i = 0; i < numberOfData;++i){
        dataPtrs[i] = tempPtr;
        tempPtr = tempPtr->nextword;
    }
    cout << numberOfData << " instances read in " <<
            float( clock () - begin_time ) /  CLOCKS_PER_SEC << " seconds" << endl;
}

//Destructor
DataBase::~DataBase(){
    WordStructPtr currPtr;
    WordStructPtr head = data;
    while ((currPtr = head) != NULL) {             // set curr to head, stop if list empty.
        head = head->nextword;                     // advance head to next element.
        delete currPtr->word;                      // delete word in struct
        free (currPtr);                            // delete saved pointer.
    }
    free(dataPtrs);
    std::cout << "Freed memory for " << numberOfData
              << " database instances" << std::endl;
}

size_t DataBase::size() const{
    return numberOfData;
}

DataWord &DataBase::operator[](size_t n){
    WordStructPtr CurrPtr;
    CurrPtr = data;
    if(n>=numberOfData){              //exception handling [returns NULL]
        std::cout << "Trying to access non-existent data in DB..." << std::endl;
        return *(CurrPtr->word);
    }
    /*
    for(size_t i = 0; i < n; ++i){   // search for the nth instance of the DB
        CurrPtr = CurrPtr->nextword;
    }
    return *(CurrPtr->word);         // Return a reference to the instance*/
    return *(dataPtrs[n]->word);
}


WordStructPtr insertWord(WordStructPtr *wordM, WordStructPtr last, std::string w, EnumTerminalsMap &m){
    WordStructPtr newPtr = (WordStructPtr) malloc( sizeof(WordStruct) ); // Gnerate a new word node
    DataWord *d1 = new DataWord(w,m);                                    // Generate a word instance for
                                                                         // the new node

    WordStructPtr currPtr = *wordM;
    if(newPtr != NULL && d1 != NULL){           // Check if memory was allocated
        newPtr->word = d1;                      // Bind the instance to the struct
        newPtr->nextword = NULL;                // At the end of the DB
        if(*wordM == NULL){                     // DB was empty
            *wordM = newPtr;
            return *wordM;                      // First = Last in this case
        }
        else{
            last->nextword = newPtr;            // Push new word
            return newPtr;                      // Return the last element of the DB
        }

    }
    else{                                       // Out of memory exception
        free(newPtr);                           // Any memory leaks deleted
        delete d1;
        cout << "Out of memory in DataBase creation!!" << endl;
        return last;
    }
}
