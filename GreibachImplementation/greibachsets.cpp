#include "greibachsets.h"

// Headers for printing sets in nice form
#include <iostream>
#include <iomanip>

// Constructor
GreibachSets::GreibachSets(EnumTerminalsMap &m, size_t NonTermSize)
    : StartSymbol(0), TerminalsStart(1), TerminalsEnd(m.getMapSize())
{
    NonTerminalStart = TerminalsEnd + 1;
    NonTerminalEnd = TerminalsEnd + NonTermSize;
}

// Dummy destructor
GreibachSets::~GreibachSets(){
    ;
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
