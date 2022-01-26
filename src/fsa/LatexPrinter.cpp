#include "LatexPrinter.hpp"

#include "Machine.hpp"
#include <fstream>
#include <vector>

LatexPrinter::~LatexPrinter() {}

LatexPrinter *LatexPrinter::getInstance() {
  static LatexPrinter m_latexPrinter;

  return &m_latexPrinter;
}

void LatexPrinter::printOnFile(std::string filePath, Machine *machine) {
  std::ofstream file{filePath};

  file << "\\documentclass[a4paper]{article}\n"
       <<    "\\usepackage{tikz}\n"
       <<    "\\usetikzlibrary{automata, positioning, arrows}\n"
       <<    "\n"
       <<    "\\tikzset{\n"
       <<    "->, % makes the edges directed\n"
       <<    "% >=stealth’, % makes the arrow heads bold\n"
       <<    "node distance=3cm, % specifies the minimum distance between two nodes. Change if necessary.\n"
       <<    "every state/.style={thick}, % sets the properties for each ’state’ node\n"
       <<    "initial text=$ $, % sets the text that appears on the start arrow\n"
       <<    "}\n"
       <<    "\n"
       <<    "\n"
       <<    "\\begin{document}\n"
       <<    "\n"
       <<    "\\begin{figure}[ht] % ’ht’ tells LaTeX to place the figure ’here’ or at the top of the page\n"
       <<    "\\centering % centers the figure\n"
       <<    "\\begin{tikzpicture}\n"
       << "\\tikzstyle{accepting}=[accepting by arrow]\n";
  int index{0};
  int i{0};
  // for(std::string stateName = std::string(2, i) + machine->m_machineName;
  //     machine->m_states.count(stateName) == 1;
  //     i++){
  std::string stateName = std::to_string(i) + machine->m_machineName;
  while(machine->m_states.count(stateName) == 1){
    auto s = machine->m_states.at(stateName);
    file << "\\node[state";
    if(machine->getState(stateName)->isFinal()){
      file << " , accepting";
    }
    if(machine->m_initialState == stateName){
      file << ", initial";
    }
    auto coord{machine->latexCoord(index)};
    index++;
    file << "] at (" << coord.first << ", " << coord.second << ") "
	 << '(' << stateName << ") {$" << stateName << "$};\n";
    i++;
    stateName = std::to_string(i) + machine->m_machineName;
  }

  file << "\\path[->] ";
  for(auto s : machine->m_states){
    file << '(' << s.first << ") ";
    for(auto t : *s.second->getTransitions()){
      file << "edge node [above] {" << t.first << "} (" << t.second << ")\n";
    }
  }

  file << ";\n";

  file << "\\end{tikzpicture}\n"
       << "\\end{figure}\n"
       << "\\end{document}";
}

LatexPrinter::LatexPrinter()
//  : m_fileType{"pdf"}
{
  m_fileType = "pdf";
}


void LatexPrinter::setFileType(std::string fileType) {
  return;
}

bool LatexPrinter::compileFile(std::string inputFile, std::string outputFile) {
  char command[genericPrinterCommandBufferSize];
  std::vector<char> vinputFile(inputFile.c_str(), inputFile.c_str() + inputFile.size() + 1);
  std::vector<char> voutputFile(outputFile.c_str(), outputFile.c_str() + outputFile.size() + 1);
  std::vector<char> vfileType(m_fileType.c_str(), m_fileType.c_str() + m_fileType.size() + 1);

  char* cinputFile = vinputFile.data();
  char* coutputFile = voutputFile.data();
  char* cfileType = vfileType.data();
  
  sprintf(command, "pdflatex %s.tex", cinputFile);
  std::cout << "Running " << command << "...\n";
  system(command);
  std::cout << "Done\n";
  return true;
}
