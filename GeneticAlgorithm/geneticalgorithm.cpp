#include "geneticalgorithm.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/stat.h>
#include <string>
#include <fstream>
#include <algorithm>
#include "matplotlibcpp.h"

#include "sgautilities.h"

/* getopt required short options */
const char *short_options="hp:n:g:m:P:f:N:t:r:R:l:s:c:o:i:e:";
void print_usage();
inline bool checkfile(const std::string name);

namespace ggi {


GeneticAlgorithm::GeneticAlgorithm(int argc, char **argv) : iterations(0)
{
    Vars = new AlgorithmVariables();
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
        switch(next_option){
            case 'p' :
                if(!checkfile(std::string(optarg))){
                    std::cout << "Could not find positive dataset. Program terminated." << std::endl;
                    exit(1);
                }
                std::cout << "Configuring input argument : -p = " << optarg << std::endl;
                Pos = true;
                PosData = std::string(optarg);
                break;
            case 'n' :
                if(!checkfile(std::string(optarg))){
                    std::cout << "Could not find negative dataset. Program terminated." << std::endl;
                    exit(1);
                }
                Neg = true;
                std::cout << "Configuring input argument : -n = " << optarg << std::endl;
                NegData = std::string(optarg);
                break;
            case 'g' :
                std::cout << "Configuring input argument : -g = " << optarg << std::endl;
                Vars->setMaxGenerations(atoi(optarg));
                break;
            case 'm' :
                std::cout << "Configuring input argument : -m = " << optarg << std::endl;
                if(atof(optarg)>100.0){
                    std::cout << "Mutation rate can not exceed 100 %. Program terminated." << std::endl;
                    exit(1);
                }
                Vars->setMutationRate(atof(optarg));
                break;
            case 'P' :
                std::cout << "Configuring input argument : -P = " << optarg << std::endl;
                if(atoi(optarg)<1){
                    std::cout << "Set a valid pool size. Program terminated." << std::endl;
                    exit(1);
                }
                Vars->setPoolSize(atoi(optarg));
                break;
            case 'N' :
                std::cout << "Configuring input argument : -N = " << optarg << std::endl;
                if(atoi(optarg)<1){
                    std::cout << "Set a valid size for non-terminals set. Program terminated." << std::endl;
                    exit(1);
                }
                Vars->setNoNterms(atoi(optarg));
                break;
            case 't' :
                std::cout << "Configuring input argument : -t = " << optarg << std::endl;
                if(atof(optarg)>=1.0 || atof(optarg)<=0.0){
                    std::cout << "Parental portion not in (0.0, 1.0). Invalid value. Program terminated." << std::endl;
                    exit(1);
                }
                Vars->setParentalPortion(atof(optarg));
                break;
            case 'r' :
                std::cout << "Configuring input argument : -r = " << optarg << std::endl;
                if(atoi(optarg) < 2){
                    std::cout << "Rule length cannot be less than 2. Program terminated" << std::endl;
                    exit(1);
                }
                Vars->setMaxRuleLen(atoi(optarg));
                break;
            case 'R' :
                std::cout << "Configuring input argument : -R = " << optarg << std::endl;
                if(atoi(optarg) < 2){
                    std::cout << "A grammar must have at least 2 rules! Program terminated" << std::endl;
                    exit(1);
                }
                Vars->setMaxNofRules(atoi(optarg));
                break;
            case 's' :
                std::cout << "Configuring input argument : -s = " << optarg << std::endl;
                if(atof(optarg)<0.0||atof(optarg)>1.0){
                    std::cout << "Subparse varible must be in [0, 1]. Program terminted." << std::endl;
                    exit(1);
                }
                Vars->setSubParse(atof(optarg));
                break;
            case 'c' :
                std::cout << "Configuring input argument : -c = " << optarg << std::endl;
                float fp,fn,tp,tn;
                if(sscanf(optarg,"%f %f %f %f",&tp,&fp,&fn,&tn)!=4){
                    std::cout << "Invalid confusion matrix. Program terminated" << std::endl;
                    exit(1);
                }
                Vars->setConfMatrix(tp,fp,fn,tn);
                break;
            case 'e' :
                std::cout << "Configuring input argument : -e = " << optarg << std::endl;
                if(atof(optarg)>=1.0||atof(optarg)<0){
                    std::cout << "Invalid elitism value. Program terminated." << std::endl;
                    exit(1);
                }
                Vars->setElitism(atof(optarg));
                break;
            case 'f' :
                std::cout << "Configuring input argument : -f = " << optarg << std::endl;
                if(atof(optarg)>=1.0||atof(optarg)<0){
                    std::cout << "Invalid convergence fitness value. Program terminated." << std::endl;
                    exit(1);
                }
                Vars->setConvergenceFit(atof(optarg));
                break;
            case 'l' :
                std::cout << "Configuring input argument : -l = " << optarg << std::endl;
                if(atoi(optarg)<2){
                    std::cout << "Invalid maximum genome length. Program terminated." << std::endl;
                    exit(1);
                }
                Vars->setMaxGenLength(atoi(optarg));
                break;
            case 'o' :
                std::cout << "Configuring input argument : -o = " << optarg << std::endl;
                Vars->setLogFile(std::string(optarg));
                break;
            case 'i' :
                std::cout << "Configuring input argument : -i = " << optarg << std::endl;
                Vars->setLogImage(std::string(optarg));
                break;
            case 'h' :
                std::cout << " ~ HELP MENU ~" << std::endl;
                print_usage();
                break;
            case -1 :
                std::cout << "Unknown argument." << std::endl;
                print_usage();
                break;
            case '?':
                std::cout << "Unknown argument." << std::endl;
                print_usage();
                exit(1);
                break;
            default:
                std::cout << "Unknown argument." << std::endl;
                print_usage();
                exit(1);
                break;
        }
    }

    if(!(Pos && Neg)){
        std::cout << "Could not open both datasets. Program terminated." << std::endl;
        exit(1);
    }

    Map = new EnumTerminalsMap(PosData);
    Map->appendMapWithData(NegData);
    Vars->setGNFsets(*Map);

    PositiveData = new DataBase(PosData,*Map);
    NegativeData = new DataBase(NegData,*Map);

    Vars->calculateConvFitness(PositiveData->size(),NegativeData->size());

    Pool = new Population(*Vars);

    bestFit.reserve(Vars->getMaxGens());
    elitFit.reserve(Vars->getMaxGens());

    Vars->print();
}

GeneticAlgorithm::~GeneticAlgorithm(){
    matplotlibcpp::clf();
    matplotlibcpp::named_plot("Best fitness",bestFit);
    matplotlibcpp::named_plot("Average elite fitness",elitFit);
    matplotlibcpp::grid(true);
    matplotlibcpp::xlim(0, (int) iterations);
    matplotlibcpp::ylim(NegativeData->size()-PositiveData->size() - 1, (int) (Vars->getMaxFit() * 1.2));
    matplotlibcpp::title("Algorithm runtime results");
    matplotlibcpp::legend();
    matplotlibcpp::save((Vars->ImageName()).c_str());
    delete Vars;
    delete Map;
    delete PositiveData;
    delete NegativeData;
    delete Pool;
}

void GeneticAlgorithm::iterate(){
    std::cout << "Positive data parsing..." << std::endl;
    Pool->parse(*PositiveData,*Vars,Positive);
    std::cout << "Negative data parsing..." << std::endl;
    Pool->parse(*NegativeData,*Vars,Negative);
    Pool->nextPool(*Vars);
    bestFit.push_back(Pool->getBestFit());
    elitFit.push_back(Pool->getElitFit());
    ++iterations;
    //*
    matplotlibcpp::clf();
    matplotlibcpp::named_plot("Best fitness",bestFit);
    matplotlibcpp::named_plot("Average elite fitness",elitFit);
    matplotlibcpp::grid(true);
    matplotlibcpp::xlim(0, (int) iterations);
    matplotlibcpp::ylim(NegativeData->size()-PositiveData->size() - 1, (int) (Vars->getMaxFit() * 1.2));
    matplotlibcpp::title("Algorithm runtime results");
    matplotlibcpp::legend();
    matplotlibcpp::pause(0.001);//*/
}

void GeneticAlgorithm::run(){
    do{
        iterate();
        Pool->printBestFit();
    }while( Pool->getBestFit() < Vars->getMaxFit() && iterations < Vars->getMaxGens());
}

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
                 "\t-f Define the convergence fitness (0.0 ~ 1.0). (Default 0.9) \n\t if bestIndividualfitness > f * maxEstimatedFitness, then algorithm halts." << "\n" <<
                 "\t-N Define the size of the non-Terminals set (Default 20)" << "\n" <<
                 "\t-t Define the rate of individuals that can be selected as parents (Default 0.85)" << "\n" <<
                 "\t-e Define the elitism rate (Default 0.03)" << "\n" <<
                 "\t-r Define the maximum rule length in the initial population (Default 5)" << "\n" <<
                 "\t-R Define the maximum number of rules in the initial population (Default 50, at least 2)" << "\n" <<
                 "\t-l Define the max genome length for all gens (Default Max rule length * Max number of rules)" << "\n" <<
                 "\t-s Define the subparse variable (Default 0.01)" << "\n" <<
                 "\t-c Define the confusion matrix (Default \"1.0 1.0 1.0 1.0\")" << "\n" <<
                 "\t-o Define the output file (Default \"log.txt\")" << "\n" <<
                 "\t-i Define the output graph file (Default \"log.png\")" << "\n";
    std::cout << " >> Least arguments are ./GGI_ACCEL -p \"Positive.txt\" -n \"Negative.txt\" " << std::endl;
}

inline bool checkfile(const std::string name) {
    std::ifstream f(name.c_str());
    return f.good();
}
