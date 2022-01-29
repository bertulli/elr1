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

#include "PilotDotPrinter.hpp"
#include "Pilot.hpp"

#include <fstream>

PilotDotPrinter* PilotDotPrinter::getInstance(){
  static PilotDotPrinter m_dotPrinter;

  return &m_dotPrinter;
}

PilotDotPrinter::PilotDotPrinter() {}

PilotDotPrinter::~PilotDotPrinter() {}

void PilotDotPrinter::printOnFile(std::string filePath){
  std::ofstream file{filePath};
  
  file << "digraph pilot{\n"
       << "node [shape=record];\n"
       << "rankdir=LR;\n"
       << "\"\" [shape=none];\n";
  
  for(auto mState : Pilot::getInstance()->getMStates()){
    bool basePrinted{false};

    file << mState.first << " [label=<\n"
	 << "<TABLE border=\"0\">\n";
    for(auto baseItem : mState.second->getBase()){
      file << "<TR> <TD>" << baseItem.getStateName() << "</TD>\n"
	   << "<TD>" << baseItem.getLookaheads() << "</TD></TR>\n";
      basePrinted=true;
    }
    if(basePrinted && !mState.second->getClosure().empty()){
      file <<"<HR/>";
    }
    for(auto closureItem : mState.second->getClosure()){
      file << "<TR> <TD>" << closureItem.getStateName() << "</TD>\n"
	   << "<TD>" << closureItem.getLookaheads() << "</TD></TR>\n";
    }
    file << "</TABLE> >];\n";
  }

  file << "\"\" -> \"I0\";\n";
  for(auto mState : Pilot::getInstance()->getMStates()){
    for(auto t : mState.second->getTransitions()){
      file << '"' << mState.first << '"'
	   << " -> " << '"' << t.second->getName() << '"' << " [label=\" " << t.first << " \"];\n";
    }

  }
  file << '}';
}
