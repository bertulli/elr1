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
       << "node [shape=circle];\n";

  file << "\"\" [shape=none]\n"; //adding initial arrow
  for(auto state : machine->m_states){
    file << '"' << state.first << '"';
    if(state.second->isFinal()){
      file << " [shape=doublecircle]";
    }
    file << ";\n";
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
