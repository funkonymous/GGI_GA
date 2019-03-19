#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "dataword.h"
#include "enumterminalsmap.h"
#include "database.h"

using namespace std;

int main()
{
    string f1("DataSets/dna_cds.dat");
    string f2("DataSets/names_txt.dat");
    string f3("ATGCNRS");
    EnumTerminalsMap M1(f2); /*
    DataWord D(f3,M1);
    D.printWord();
    for(size_t i = 0; i < D.size(); ++i) cout << D[i] << " ";
    cout << endl;*/
    DataBase Dat(f2,M1);
    return 0;
}
