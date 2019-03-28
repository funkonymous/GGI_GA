#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "enumterminalsmap.h"
#include "database.h"
#include "greibachsets.h"
#include "algorithmvariables.h"

using namespace std;


// Seira ekteleshs
// 1. Enumeration map
// 2. Datasets
// 3. Set algorithm variables
//    - Greibach sets is the only without defaults
// 4. Initialize population
// 5. SGA
int main()
{
    string f1("DataSets/dna_cds.dat");
    string f2("DataSets/names_txt.dat");
    EnumTerminalsMap M1(f1);
    DataBase Dat(f1,M1);
    AlgorithmVariables Vars;
    GreibachSets Sets(M1,Vars);
    Sets.printSets();
    return 0;
}
