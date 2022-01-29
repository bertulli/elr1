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

#include "fsa/Machine.hpp"
#include "fsa/MachineNet.hpp"
#include "fsa/LatexPrinter.hpp"
#include "fsa/DotPrinter.hpp"
#include <ast/AST.hpp>
#include "common/flags.h"
#include "pilot/Item.hpp"
#include "pilot/MState.hpp"
#include "pilot/Pilot.hpp"
#include "pilot/PilotDotPrinter.hpp"

#include <iostream>
#include <parser.hpp>
#include "parser/lexer.hpp"
#include <string>
//#include <unistd.h>
#include <getopt.h>

void initializeFlags();
void printusage();

//to keep synchronized with common/flags.h
int explainFsaFlag;
int explainPilotFlag;
int printPilotFlag;
int latexFlag;
int graphvizFlag;
int debugFlag;

int main(int argc, char *argv[])
{
  //Helper variable to describe the required functions to perform, as well as the previous static flags
  //empty means no function needed
  std::string dotGraphFileType{"png"};
  std::string graphToBePrinted;
  std::string grammarName;
  char c;            //char returned as short options
  int optionIndex;   //index of the long options

  static const struct option longOptions[] =
    {
      {"print-machine", required_argument, nullptr, 'G'},
      {"latex", no_argument, nullptr, 'L'},
      {"graphviz", no_argument, nullptr, 'g'},
      {"pilot", no_argument, &printPilotFlag, 1},
      {"image-type", required_argument, nullptr, 'T'},
      {"help", no_argument, nullptr, 'h'},
      {"explain-fsa", no_argument, &explainFsaFlag, 1},
      {"explain-pilot", no_argument, nullptr, 'v'},
      {"debug", no_argument, nullptr, 'd'},
      {0, 0, 0, 0}
    };
  
  while ((c = getopt_long(argc, argv, "G:T:phvd", longOptions, &optionIndex)) != -1) {
    switch (c) {
    case 0:
      std::cout << "Setting " <<  longOptions[optionIndex].name << "\n";
      break;
    case 'G':
      std::cout << "Requesting Graph for machine " << optarg << "\n";
      graphToBePrinted = optarg;
      break;
    case '?':
    case 'h':
      std::cout << "help\n";
      printusage();
      break;
    case 'T':
      std::cout << "Setting image output type " << optarg << "...\n";
      dotGraphFileType = optarg;
      break;
    case 'L':
      latexFlag = 1;
      graphvizFlag = 0;
      break;
    case 'g':
      graphvizFlag = 1;
      latexFlag = 0;
      break;
    case 'v':
      std::cout << "Requesting explaining pilot automaton contruction.\n";
      explainPilotFlag = 1;
      break;
    case 'p':
      printPilotFlag=1;
      break;
    case 'd':
      std::cout << "Enabling debugging informations...\n";
      debugFlag = 1;
      explainFsaFlag = 1;
      explainPilotFlag = 1;
      break;
    }
  }

  if(debugFlag){
    for(int index = optind; index < argc; index++){
      std::cout << "Debug: Non option argument: " << argv[index] << "\n";
    }
  }
  
  if(optind < argc){
    grammarName=argv[optind];
    yyin = fopen(argv[optind], "r");
    if(!yyin){
      std::cout << "Error reading file " << argv[optind] << "\n";
      return 1;
    }
    std::cout << "reading grammar " << argv[optind] << "\n";
  } else {
    grammarName="stdin";
    std::cout << "Reading grammar from stdin...\n";
    yyin = stdin;
  }
    
  yyparse();
  MachineNet* net = MachineNet::getInstance();

  for(auto m : net->getMachines()){
    m.second->BSBuild();
  }
  
  Machine* m; //=net->getMachine("S");
  ASTree* t; //=m->getTree();
  ASTGenericNode* root; //=t->getRoot();

  

  
  if(debugFlag){
    std::cout<<"axiom:"<<net->getAxiom()<<'\n';
    //    m = net->getMachine("S");
    //    Item initial{"0S", m, m->getState("0S"), {'$'}};
    //    MState I0{"I0",{initial}};
    //    MState I3{"I3",{Item{"1S", m, m->getState("1S"), {'b'}}}};
    //    I3.buildClosure();
    //    I0.buildClosure();
    //std::cout << I0<<I3;
    Pilot* pilot{Pilot::getInstance()};
    pilot->print();
    pilot->setPrinter(PilotDotPrinter::getInstance());
    pilot->printOnFile("pilot.dot");
    
  }
  

    
  if(graphToBePrinted != ""){
    m=net->getMachine(graphToBePrinted);
    t=m->getTree();
    root=t->getRoot();
    m->BSBuild();
    // m->printDebug();
    if(latexFlag){
      m->setPrinter(LatexPrinter::getInstance());
      m->print(graphToBePrinted + ".tex");
      m->setFileType("whatever");
      m->compileFile(graphToBePrinted, graphToBePrinted);
    } else if(graphvizFlag){
      m->setPrinter(DotPrinter::getInstance());
      m->print(graphToBePrinted + ".dot");
      m->setFileType(dotGraphFileType);
      m->compileFile(graphToBePrinted, graphToBePrinted);
    }
    
    
    //m->produceDot(graphToBePrinted + ".dot");
    //    system("dot -Tpng -o A.png A.dot");
    //m->compileDot(graphToBePrinted + ".dot", graphToBePrinted + "." + fsaGraphFileType, fsaGraphFileType);
  }
  if(printPilotFlag){
      Pilot* p{Pilot::getInstance()};
      p->setPrinter(PilotDotPrinter::getInstance());
      p->printOnFile(grammarName+".dot");
      p->setFileType(dotGraphFileType);
      p->compileFile(grammarName, grammarName);
    }
  return 0;


}

// std::string searchGraphFileType(std::string &fsaGraphFileType,
//                                 std::string commandFlag, char** argv) {
//   for(auto s : argv)
// }

void initializeFlags() {
  explainFsaFlag = 0;
  explainPilotFlag = 0;
  debugFlag = 0;
}

void printusage() {
  std::cout << "Usage:\n"
	    << "-h --help \t prints this message\n"
	    << "-G --print-machine <machine name> \t prints a .dot file of the machine <machine name>\n"
	    << "-T --image-type <type> \t specifies the file type of the image produced by dot\n"
	    << "--explain-fsa \t\t explains the construction of the FSA machines uing the Berry-Sethi algorithm\n"
	    << "-v --explain-pilot \t explains the construction of the pilot automaton for the given grammar (TO BE IMPLEMENTED)\n"
	    << "-d --debug \t prints all kinds of informations, useful to debug\n";
}
