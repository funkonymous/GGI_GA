#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "dataword.h"
#include "enumterminalsmap.h"
#include "database.h"
#include "greibachsets.h"

using namespace std;

int main()
{
    string f1("DataSets/dna_cds.dat");
    string f2("DataSets/names_txt.dat");
    EnumTerminalsMap M1(f1);
    DataBase Dat(f1,M1);
    GreibachSets Sets(M1,10);
    Sets.printSets();
    return 0;
}
