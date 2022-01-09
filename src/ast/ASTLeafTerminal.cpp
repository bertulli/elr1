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

#include "ASTLeafTerminal.hpp"
#include <iostream>
#include <set>

bool ASTLeafTerminal::isNullable() { return false; }

std::set<BSGrammarChar> ASTLeafTerminal::iniSet() {
  std::set<BSGrammarChar> res = {BSTerminal{m_grammarChar, m_rePos}};
  return res;
}

std::set<BSGrammarChar> ASTLeafTerminal::finSet() {
  BSTerminal leaf{m_grammarChar, m_rePos};
  std::set<BSGrammarChar> res = {leaf};
  return res;
}

std::set<std::pair<BSGrammarChar, BSGrammarChar>> ASTLeafTerminal::digSet(){
  std::set<std::pair<BSGrammarChar, BSGrammarChar>> emptyRes;
  return emptyRes;
}

ASTLeafTerminal::ASTLeafTerminal(char grammarChar, int rePos)
    : ASTLeafNode{grammarChar, rePos} {}

ASTLeafTerminal::~ASTLeafTerminal() {}

void ASTLeafTerminal::print(){
  std::cout << m_grammarChar<<m_rePos;
  return;
}
