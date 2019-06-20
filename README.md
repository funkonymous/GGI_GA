# Greibach Grammatical Inference with Genetic Algorithm

This is a project in development. The goal of this project is to 
create context-free grammars from datasets using genetic algorithms.
The conventions used are that each grammar representation follows 
the [Greibach Normal Form](https://en.wikipedia.org/wiki/Greibach_normal_form)
formalism. Goal is from a file containing words that should belong
to a context-free grammar and a file that contains data that should not belong
in the same context-free grammar, to generate the corresponding CFG.

## Getting Started

This project is completely developed in C/C++ and Python in Ubuntu 18.04
. The C++ compiler used for building this project was [PGCC](https://www.pgroup.com/products/pgi-tools.htm).
Though, there has been no testing in other systems, this project should build
in any Unix system.

### Prerequisites
For this project to build you need ```pgi compilers and tools``` and a working python installation, 
including development headers. 

On Ubuntu:

    sudo apt-get install python-matplotlib python-numpy python2.7-dev

Then, follow the installation process from [PGI](https://www.pgroup.com/products/community.htm)
to install the C/C++ compilers.

### Installing

On Ubuntu's terminal run

    git clone https://github.com/funkonymous/GGI_GA.git
    cd GGI_GA
    cmake .
    make
    
Now, on the directory ``` GGI_GA/bin ``` has been created the executable file.
Note that because the project is still under development there are several warnings
while building the project (mainly because of the nested comments).

If CMake cannot find the pgcc compiler and opts for another compiler try setting the enviromenal
variables of the PGI tools. This is something like :

    export PGI=/opt/pgi;
    export PATH=/opt/pgi/linux86-64/19.4/bin:$PATH;
    export MANPATH=$MANPATH:/opt/pgi/linux86-64/19.4/man;
    export LM_LICENSE_FILE=$LM_LICENSE_FILE:/opt/pgi/license.dat; 
    
These instructions depend on your current distibution of the PGI compilers and tools.
Re-run 

    cmake .
    make

in the /GGI_GA directory if you couldn't manage to compile with pgcc the first time.

Note that if you do not use pgcc the project should be able to build with GCC or Clang
just by commenting the 

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -o4 -Mconcur=allcores -mp")

flags set in the CMakeLists.txt file but many optimizations will not be performed.

After this, type

    cd bin
    ./GGI_ACCEL

and the help menu will be printed in the terminal. The executable runs with command
line options described in the Testing/Experimenting paragraph.

## Algorithm Description

### General Idea

This project was my thesis in ECE UPatras, the part describing the algorithm
is [here](./GreibachGrammaticalInference.pdf). If you want to read the full thesis
(note that this is the same idea but all the code is re-written) you can find it
[here](http://nemertes.lis.upatras.gr/jspui/bitstream/10889/12175/1/GreibachGrammaticalInferenceThesis228268.pdf)

### Algorithm options

The algorithm options are, as described in the documentation, these :

    -h Print the help screen
    -p Define the path to the positive dataset
    -n Define the path to the negative dataset
    -g Define the maximum number of generations (Default 500)
    -m Define the mutation rate (Default 0.03)
    -P Define the size of the population (Default 1000)
    -f Define the convergence fitness (0.0 ~ 1.0). (Default 0.9) \n\t if bestIndividualfitness > f * maxEstimatedFitness, then algorithm halts.
    -N Define the size of the non-Terminals set (Default 20)
    -t Define the rate of individuals that can be selected as parents (Default 0.85)
    -e Define the elitism rate (Default 0.03)
    -r Define the maximum rule length in the initial population (Default 5)
    -R Define the maximum number of rules in the initial population (Default 50, at least 2)
    -l Define the max genome length for all gens (Default Max rule length * Max number of rules)
    -s Define the subparse variable (Default 0.01)
    -c Define the confusion matrix (Default "tp = 1.0 fp = 1.0 fn = 1.0 tn = 1.0\")
    -o Define the output file (Default \"log.txt\")
    -i Define the output graph file (Default \"log.png\")

You must at least define at least the arguments ``` -p "Path/To/Positive" -n "Path/To/Negative" ```
or the programm will not initiate the genetic algorithm.

Note that the majority of the arguments have been tested under normal circumstances. If somebody finds
a strange value like ```-N 0```, then you may fall into undefined behaviour. Check beforehands that each 
argument has a valid value or do not mess with predefined values.

Also, some output and log files have not been implented yet as there are more important things during
this phase of the development. Feel free to implement your own logging files.

### Dataset convention

In the datasets, each line of text is read as a string. Every individual character of the string,
(a Terminal to be precise with the convention of formal grammars) should be inside parenthensis.

e.g. A dataset :

1. Heinz
2. Doofenshmirtz
3. Evil
4. Incorporated

should be written inside an ASCII file as :

    (H)(e)(i)(n)(z)
    (D)(o)(o)(f)(e)(n)(s)(h)(m)(i)(r)(t)(z)
    (E)(v)(i)(l)  
    (I)(n)(c)(o)(r)(p)(o)(r)(a)(t)(e)(d)
    
This convention was selected in order to help somebody who does complex analysis of text
to have datasets in the form of

    (adjective)(noun)(proposition)
    etc...

### Testing/Experimenting

In order to run simple experiments, open a terminal inside the /bin directory
and run

    ./GGI_ACCEL -p "Path/To/Positive" -n "Path/To/Negative"
    
or add any other flags you wish for. At the end of the execution you will find a new
.png file in your /bin directory, this will be the graph of the fitness of the SGA
implemented.

During the execution of the code, every major step prints various things in the terminal. For
more information about the initialization process and the convergence of the algorithm try

    ./GGI_ACCEL -p "Path/To/Positive" -n "Path/To/Negative" > A_File.txt
   
and the terminal output will be writen to "A_File.txt" in ASCII format.

There are two datasets provided for minor experimenting, a 
[positive dataset](https://github.com/funkonymous/GGI_GA/blob/master/DataFromRegex/RegexDataSets/PosData.txt) and a 
[negative dataset](https://github.com/funkonymous/GGI_GA/blob/master/DataFromRegex/RegexDataSets/NegData.txt).

These datasets were created by a 
[python script]https://github.com/funkonymous/GGI_GA/blob/master/DataFromRegex/generateRegexDataSets.py using
the [exrex](https://github.com/asciimoo/exrex) module. For more information about the module visit the corresponding
repository.

For the two datasets, random strings were generated from these regular expressions :

    [a-f]{6,7}[a-c]{2,3}[a-f]{4,7}[a-c]{1,3} <- Positive dataset
    [a-f]{6,7}[d-f]{2,3}[a-f]{4,7}[d-f]{1,3} <- Negative dataset

Note, that it is important the the intersection of the two sets is a '''NULL''' set, else, the estimated
maximum fitness will be false and the algorithm will not halt even if it should !

There are 300 instances (strings) in each dataset. Note that, because of the complexity of the algorithm,
a quick experiment may run for multiple hours.

To run an experiment, type :

    ./GGI_ACCEL -p "RegexDataSets/PosData.txt" -n "RegexDataSets/NegData.txt" -r 5 -R 30 -N 5 -P 1000 -s 0.1 -g 500

These options should be sufficient.

1. -r 5 -> maximum rule length = 5
2. -R 30 -> maximum number of rules = 30
3. -N 5 -> number of non-terminal symbols = 5
4. -P 1000 -> population size = 1000
5. -s 0.1 -> subparse variable = 0.1
6. -g 500 -> maximum iterations (generations) = 500

Finally, feel free to send any successful testing conducted as validation for this software. 

### Interpreting the results

After, the halt of the algorithm, a CFG will be printed in the terminal. Note that the formation
of the output is like

    0 -> 2 14 15  4
    14 -> 1  2
    15 -> 3  2
    
Only the first number in the body of each rule represents a terminal symbol. 0 represents
the starting symbol. The correspondence of enumerated symbols and the datasets is printed 
at the beginning of the execution of the program. Each line represents a production rule.
The last number in every line is the production rule length in symbols and is printed just
to ensure that is individual grammar is stored correctly.

In a typical experiment for the datasets explained in the previous paragraph, the results 
printed in the terminal should look like this :

![Alt text](derivedCFG.png?raw=true "Title")

This is a CFG and the meaning of the symbols is printed at the start of the algorithm in the 
terminal like this :

![Alt text](enumMap.png?raw=true "Title")

Every number that does not have a corresponding symbol is a non-terminal symbol.

Finally, the progress of the algorithm is also stored as a graph in the /bin directory
after the conclusion of the algorithm.

![Alt text](log.png?raw=true "Title")

All the results are also stored in a log file in ASCII form.

## Known bugs/issues

1. As of the first working commits this project has been checked with [Valgrind](http://valgrind.org/) and there
seems to be no issue with memory leaks etc.

2. There seem to be no logic errors with the project as of the latest commit.

3. The oprimization of the code has been done through [PgProf](https://www.pgroup.com/resources/pgprof-quickstart.htm)

## Work on progress

There are still several things on development.

### Active development

1. Accelerate and optimize the algorithm, preferably on GPUs
2. Implement a more efficient parsing method
3. Create random negative data
4. Integrate the software in a library

### TODO list

1. Finish the writing of log files
2. Make a readable representation of the derived GNF grammar
3. Have multiple checks for the validity of the offsprings on demand
4. Make an official release of the software on github

## Additional information

1. This software was written in [QT creator](https://www.qt.io/) and [VIM](https://www.vim.org/)
2. Many thanks to everyone whose code was used for this project
3. The original idea was inspired by Prof. [Evangelos Dermatas](https://scholar.google.com/citations?user=ireNT3QAAAAJ&hl=en)
4. Contact the author of this software [here](https://www.linkedin.com/in/anastasopoulosnikolas/)
5. Definetely feel free to share any improvements for this software by commiting them

## Licensing
This project is licensed under the GNU GPL v3.0 license. Check [LICENSE.md](LICENSE.md) for more info.
