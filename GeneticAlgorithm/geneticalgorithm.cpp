#include "geneticalgorithm.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/stat.h>
#include <string>
#include <fstream>

/* getopt required short options */
const char *short_options="hp:n:g:m:P:n:t:r:R:s:c:o:i:e:";
void print_usage();
inline bool checkfile(const std::string name);

GeneticAlgorithm::GeneticAlgorithm(int argc, char **argv)
{
    //std::cout << argc << std::endl;
    if(argc < 5){
        std::cout << "Algorithm was not given enough arguments. See help below." << std::endl;
        print_usage();
        exit(1);
    }
    int next_option = 0;
    std::string PosData, NegData;
    bool Pos = false, Neg = false; // check if datasets exist
    std::cout << "Checking command line arguments" << std::endl;
    while ((next_option  = getopt(argc, argv, short_options)) != -1){
        //next_option = getopt(argc,argv,short_options);
        //if(next_option == -1) break;
        switch(next_option){
            case 'p' :
                if(!checkfile(std::string(optarg))){
                    std::cout << "Could not find positive dataset. Program terminated." << std::endl;
                    exit(1);
                }
                std::cout << "Configuring input argument : " << optarg << std::endl;
                Pos = true;
                PosData = std::string(optarg);
                break;
            case 'n' :
                if(!checkfile(std::string(optarg))){
                    std::cout << "Could not find negative dataset. Program terminated." << std::endl;
                    exit(1);
                }
                Neg = true;
                std::cout << "Configuring input argument : " << optarg << std::endl;
                NegData = std::string(optarg);
                break;
            case 'h':
                print_usage();
                break;
            case -1 :
                print_usage();
                break;
            case '?':
                print_usage();
                exit(1);
                break;
            default:
                print_usage();
                exit(1);
                break;
        }
    }//while(next_option != -1);
    std::cout << PosData << " " << NegData << std::endl;
    Map = new EnumTerminalsMap(PosData);
    Map->appendMapWithData(NegData);
}

GeneticAlgorithm::~GeneticAlgorithm(){
    delete Map;
}
/* Print the program help */
void print_usage()
{
    std::cout << "\t-h Print the help screen" << "\n" <<
                 "\t-p Define the positive dataset" << "\n" <<
                 "\t-n Define the negative dataset" << "\n" <<
                 "\t-g Define the maximum number of generations (Default 500)" << "\n" <<
                 "\t-m Define the mutation rate (Default 0.03)" << "\n" <<
                 "\t-P Define the size of the population (Default 1000)" << "\n" <<
                 "\t-n Define the size of the non-Terminals se (Default 20)" << "\n" <<
                 "\t-t Define the rate of individuals that can be selected as parents (Default 0.85)" << "\n" <<
                 "\t-e Define the elitism rate (Default 0.03)" << "\n" <<
                 "\t-r Define the maximum rule length in the initial population (Default 5)" << "\n" <<
                 "\t-R Define the maximum number of rules in the initial population (Default 50)" << "\n" <<
                 "\t-r Define the subparse variable (Default 0.01)" << "\n" <<
                 "\t-c Define the confusion matrix (Default \"1.0 1.0 1.0 1.0\")" << "\n" <<
                 "\t-o Define the output file (Default \"log.txt\")" << "\n" <<
                 "\t-i Define the output graph file (Default \"log.png\")" << "\n";
    std::cout << " >> Least arguments are ./GGI_ACCEL -p \"Positive.txt\" -n \"Negative.txt\" " << std::endl;
}

inline bool checkfile(const std::string name) {
    std::ifstream f(name.c_str());
    return f.good();
}
