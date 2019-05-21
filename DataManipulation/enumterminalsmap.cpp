#include "enumterminalsmap.h"

// Headers for TerminalsMap
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

enum{DONTADD = 0, ADD = 1};

// Helpful functions for the back-end of the class
void insertMappedSymbol(SymbolMapPtr *Map, char Letter, size_t Value); // Push a new node in the map
void printMap(SymbolMapPtr Map);                                       // Print enumeration map
size_t findInMap(SymbolMapPtr *Map, char c, bool add = DONTADD);       // Search symbol in a map

using namespace std;

EnumTerminalsMap::EnumTerminalsMap(){
    ;
}
//Constructor
EnumTerminalsMap::EnumTerminalsMap(std::string fname) : Map(NULL), MapSize(0)
{
    string line;
    ifstream infile(fname); // open dataset
    // Find all the unique terminals for the grammar
    if(infile.is_open()){
        std::cout << "Reading file : " << fname << std::endl;
        while(getline(infile,line)){
            for(size_t i = 0;i<line.size();++i){
                if(!findInMap(&Map,line[i],ADD)){             // search symbol and ADD if found
                    MapSize++;                                // else create new integer and
                    insertMappedSymbol(&Map,line[i],MapSize); // append the enumeration map
                    //std::cout << line[i] << std::endl;      // Print the new symbol
                }
            }
        }
    }
    cout << "Enumeration terminals map created with " << MapSize << " symbols." << endl;
    printMap(Map);
}

size_t EnumTerminalsMap::returnEnum(char c){
    return findInMap(&Map, c);
}

size_t EnumTerminalsMap::getMapSize(){
    return MapSize;
}

void EnumTerminalsMap::appendMapWithData(std::string fname){
    string line;
    ifstream infile(fname);
    // Find all the unique terminals for the grammar
    if(infile.is_open()){
        std::cout << "Reading more files : " << fname << std::endl;
        while(getline(infile,line)){
            for(size_t i = 0;i<line.size()-1;++i){
                if(!findInMap(&Map,line[i],ADD)){
                    MapSize++;
                    insertMappedSymbol(&Map, (char) line[i],MapSize);
                }
            }
        }
    }
    cout << "Enumeration terminals map possibly appended. Size of map is " << MapSize << " symbols." << endl;
    printMap(Map);
}

//Destructor
EnumTerminalsMap::~EnumTerminalsMap(){
    SymbolMapPtr currPtr;
    SymbolMapPtr head = Map;
    while ((currPtr = head) != NULL) { // set curr to head, stop if list empty.
        head = head->nextSymbol;       // advance head to next element.
        free (currPtr);                // delete saved pointer.
    }
    cout << "Freed memory for terminals map" << endl;
}

void insertMappedSymbol(SymbolMapPtr *Map, char Letter, size_t Value){
    SymbolMapPtr newPtr = (SymbolMapPtr) malloc( sizeof(SymbolMap) ); // New node
    SymbolMapPtr currPtr = *Map;
    if(newPtr != NULL){
        newPtr->letter = Letter;
        newPtr->value = Value;
        newPtr->timesFound = 1;
        newPtr->nextSymbol = NULL;
        if(*Map == NULL ) *Map = newPtr;
        else{
            while (currPtr->nextSymbol) currPtr = currPtr->nextSymbol;
            currPtr->nextSymbol = newPtr;  // Push new node
        }
    }
    else cout << "Out of memory...(Terminals Map creation)" << endl;
}

void EnumTerminalsMap::print() const{
    printMap(Map);
}

void printMap(SymbolMapPtr Map){
    if(Map == NULL){
        cout << "Enumeration map is empty!!" << endl;
        return;
    }
    SymbolMapPtr currPtr = Map;
    cout << "Enumerated terminal symbols mapping :" << endl <<
            "Symbol <-> Enumeration & Times Found" << endl;
    cout << "__________________________________________________________________________________" << endl;
    cout << "| ";
    while (currPtr){
        cout << currPtr->letter << " <->" << setw(4) << currPtr->value << " & " << setw(12) <<
             currPtr->timesFound << " | ";
        if((!(currPtr->value%3))&&(currPtr->nextSymbol)) cout << endl << "| ";
        currPtr = currPtr->nextSymbol;
    }
    cout << "\n----------------------------------------------------------------------------------" << endl;
}

size_t findInMap(SymbolMapPtr *Map, char c, bool add){
    SymbolMapPtr currPtr = *Map;
    if(currPtr == NULL) return 0;
    do{
        if(currPtr->letter == c){           // If symbol c is found
            if(add) currPtr->timesFound ++; // and add == ADD, count
            return currPtr->value;          // the occurence and return true
        }
        if(currPtr->nextSymbol != NULL) currPtr = currPtr->nextSymbol;
        else currPtr = NULL;
    }while(currPtr);
    return 0;
}
