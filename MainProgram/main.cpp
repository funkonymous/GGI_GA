#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "dataword.h"
#include "enumterminalsmap.h"

using namespace std;

int main()
{
    string f1("DataSets/dna_cds.dat");
    string f2("names.txt");
    EnumTerminalsMap M1(f1);
    return 0;
}
