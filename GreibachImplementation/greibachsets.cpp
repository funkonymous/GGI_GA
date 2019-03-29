#include "greibachsets.h"

// Headers for printing sets in nice form
#include <iostream>
#include <iomanip>

// Constructor <- Assign values to sets S, N, T
GreibachSets::GreibachSets(EnumTerminalsMap &m, size_t NtSize)
    : StartSymbol(0), TerminalsStart(1), TerminalsEnd(m.getMapSize()) // Fixed values
{
    NonTerminalStart = TerminalsEnd + 1;                  // Start of Non-Terminal Symbols set
    NonTerminalEnd = TerminalsEnd + NtSize;               // End of Non-Terminals Symbols set after
                                                          // selected length
}

GreibachSets::GreibachSets(){
    ; // Dummy constructor
}
// Dummy destructor
GreibachSets::~GreibachSets(){
    ;   // No memory dynamically allocated
}

size_t GreibachSets::getRandomTerminal() const{
    return rand() % TerminalsEnd + 1;
}

size_t GreibachSets::getRandomNonTerminal() const{
    return ( rand() % ( NonTerminalEnd - NonTerminalStart + 2 ) + NonTerminalStart ) %
            (NonTerminalEnd + 1);
}

void GreibachSets::printSets() const{
    std::cout << "+----------------------+--------------+------------+" << std::endl;
    std::cout << "| Set Name             | Start number | End number |" << std::endl;
    std::cout << "+----------------------+--------------+------------+" << std::endl;
    std::cout << "| Starting Symbol      |            0 |          0 |" << std::endl;
    std::cout << "+----------------------+--------------+------------+" << std::endl;
    std::cout << "| Terminal Symbols     |" << std::setw(13) << TerminalsStart <<
                 " |" << std::setw(11) << TerminalsEnd << " |" << std::endl;
    std::cout << "+----------------------+--------------+------------+" << std::endl;
    std::cout << "| Non Terminal Symbols |" << std::setw(13) << NonTerminalStart <<
                 " |" << std::setw(11) << NonTerminalEnd << " |" << std::endl;
    std::cout << "+----------------------+--------------+------------+" << std::endl;
}
