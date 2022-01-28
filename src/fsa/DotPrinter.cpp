/*************************************************************************/
/* Copyright Alessandro Bertulli 2022                                    */
/* This file is part of ExpLaineR1.					 */
/* 									 */
/* ExpLaineR1 is free software: you can redistribute it and/or modify it */
/* under the terms of the GNU General Public License as published by	 */
/* the Free Software Foundation, either version 3 of the License, or	 */
/* (at your option) any later version.					 */
/* 									 */
/* ExpLaineR1 is distributed in the hope that it will be useful, but	 */
/* WITHOUT ANY WARRANTY; without even the implied warranty of		 */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU	 */
/* General Public License for more details.				 */
/* 									 */
/* You should have received a copy of the GNU General Public License	 */
/* along with ExpLaineR1. If not, see <https://www.gnu.org/licenses/>.	 */
/*************************************************************************/

#include "DotPrinter.hpp"

#include "Machine.hpp"

#include <fstream>
#include <vector>

DotPrinter::DotPrinter() {}
DotPrinter::~DotPrinter() {}

DotPrinter* DotPrinter::getInstance(){
  static DotPrinter m_dotPrinter;

  return &m_dotPrinter;
}

void DotPrinter::printOnFile(std::string filePath, Machine *machine) {
  std::ofstream file{filePath};
  file << "digraph{\n"
       << "node [shape=circle];\n"
       << "rankdir=LR;\n";

  file << "\"\" [shape=none]\n"; //adding initial arrow
  for(auto state : machine->m_states){
    std::string machineId{state.first.substr(state.first.size() - 1)};
    std::string stateId{state.first.substr(0, state.first.size() - 1)};
    file << '"' << state.first << '"';
    file << " [";
    if(state.second->isFinal()){
      file << "shape=doublecircle ";
    }
    file << "label=<" << stateId << "<SUB>" << machineId << "</SUB>>];\n";
  }

  file << "\"\" -> \"" << machine->m_initialState << "\";\n";
  for(auto state : machine->m_states){
    for(auto transition : *state.second->getTransitions()){
      file << '"' << state.first << '"' << " -> " << '"' << transition.second << '"' << " [label=\" "
	   << transition.first << " \"];\n";
    }
  }
  file << "}";
}

void DotPrinter::setFileType(std::string fileType) {
  m_fileType = fileType;
  return;
}

bool DotPrinter::compileFile(std::string inputFile, std::string outputFile) {
  char command[genericPrinterCommandBufferSize];
  std::vector<char> vinputFile(inputFile.c_str(), inputFile.c_str() + inputFile.size() + 1);
  std::vector<char> voutputFile((outputFile + '.' + m_fileType).c_str(), outputFile.c_str() + outputFile.size() + 1);
  std::vector<char> vfileType(m_fileType.c_str(), m_fileType.c_str() + m_fileType.size() + 1);

  char* cinputFile = vinputFile.data();
  char* coutputFile = voutputFile.data();
  char* cfileType = vfileType.data();
  
  sprintf(command, "dot -T%s -o %s %s.dot", cfileType, coutputFile, cinputFile);
  std::cout << "Running " << command << "...\n";
  system(command);
  std::cout << "Done\n";
  return true;
}
