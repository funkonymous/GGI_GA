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
#include "sgautilities.h"
#include "population.h"
#include "geneticalgorithm.h"


using namespace std;

// TODO 1) getTickets not crashing, 2) validGNFs, 3) mutation
// TODO LAVA github ~ live plots

// Na ftiaksw to crossover !!! (Nomizw to eftiaksa)
// Na grapsw to mutation

int main(int argc, char **argv)
{
    srand(time(NULL));
    printMemory();

    ggi::GeneticAlgorithm *G = new ggi::GeneticAlgorithm(argc,argv);
    G->run();
    delete G;

    printMemory();//*/
    /*
    string f1("DataSets/smalldata.dat");
    string f2("DataSets/smalldata2.dat");
    EnumTerminalsMap M1(f1);
    M1.appendMapWithData(f2);
    DataBase D(f2,M1);
    M1.print();
    for(size_t i = 0; i < D.size();++i){
        D[i].printWord();
    }
    DataBase D2(10,3,M1);
    for(size_t i = 0; i < D2.size();++i){
        std::cout << i << " -> ";
        D2[i].printWord();
    }
    std::cout << "Parsed??" << std::endl;
    printMemory();//*/
    /*
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
    //Population p(Vars);*/

    return 0; //*/
}
