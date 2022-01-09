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

#include "ASTLeafNonTerminal.hpp"
#include "../fsa/MachineNet.hpp"
#include <iostream>
#include <string>

ASTLeafNonTerminal::ASTLeafNonTerminal(char grammarChar, int rePos)
  : ASTLeafNode{grammarChar, rePos}{}

void ASTLeafNonTerminal::print(){
  std::cout << m_grammarChar <<m_rePos;
  return;
}

bool ASTLeafNonTerminal::isNullable() {
  return MachineNet::getInstance()->getMachine(std::string(1,m_grammarChar))->getTree()->getRoot()->isNullable();
}

std::set<BSGrammarChar> ASTLeafNonTerminal::iniSet() {
  return MachineNet::getInstance()->getMachine(std::string(1,m_grammarChar))->getTree()->getRoot()->iniSet();
}

std::set<BSGrammarChar> ASTLeafNonTerminal::finSet() {
  return MachineNet::getInstance()->getMachine(std::string(1,m_grammarChar))->getTree()->getRoot()->finSet();
}

std::set<std::pair<BSGrammarChar, BSGrammarChar>> ASTLeafNonTerminal::digSet(){
  return MachineNet::getInstance()->getMachine(std::string(1,m_grammarChar))->getTree()->getRoot()->digSet();
}
