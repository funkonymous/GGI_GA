#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>


#include "enumterminalsmap.h"
#include "database.h"
#include "greibachsets.h"
#include "algorithmvariables.h"
#include "grammar.h"
//#include "sgautilities.h"
#include "population.h"
#include "geneticalgorithm.h"


using namespace std;


// Seira ekteleshs
// 1. Enumeration map
// 2. Datasets
// 3. Set algorithm variables
//    - Greibach sets is the only without defaults
// 4. Initialize population
// 5. SGA

// TODO command line arguments ~ getopt()
// TODO LAVA github ~ live plots
int main(int argc, char **argv)
{
    /* get options */
    GeneticAlgorithm G(argc,argv);
    /*
    srand(time(NULL));
    //string f1("DataSets/dna_cds.dat");
    //string f1("DataSets/smalldata.dat");
    string f1("DataSets/names_txt.dat");
    EnumTerminalsMap M1(f1);
    DataBase Dat(f1,M1);
    AlgorithmVariables Vars;
    Vars.setGNFsets(M1);
    //Vars.setMaxRuleLen(50);
    //Vars.setMaxNofRules(500);
    Vars.setPoolSize(1000);
    //printMemory();

    Population p(Vars);
    //printMemory();
    //Population p(Vars);

    return 0; //*/
}
