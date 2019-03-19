#ifndef DATABASE_H
#define DATABASE_H

// headers for the class
#include <string>
#include "dataword.h"
#include "enumterminalsmap.h"
#include "datautilities.h"

// This is the database of the algorithm. Every instance in the ASCII file that is
// represented by a line is stored in this class
//
// * Non-linear internal structure which is dynamicaly allocated while parsing the file.
//
// * No restriction other than the heap size of the machine running the code. Every row
// * of data may have arbitrary length.
//
// * In an instance (e.g. Database DB(file,map)), DB[n][m] returns the mth letter of the
// * nth word in an enumerated file. Matrix-alike manipulation of the data.

class DataBase
{
public:
    DataBase(std::string fname, EnumTerminalsMap &m); // Construct a DB for a corresponding ASCII
                                                      // file with an enumeration map
    ~DataBase();                                      // Free any allocated memory
    size_t size();                                    // Get the number of instances in the DB
private:
    WordStructPtr data;                               // The data struct
    WordStructPtr lastData;                           // For faster insertion
    size_t numberOfData;                              // Number of instances in the DB
};

#endif // DATABASE_H
