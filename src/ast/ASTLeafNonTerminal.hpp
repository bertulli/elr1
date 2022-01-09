#ifndef ASTLEAFNONTERMINAL_H
#define ASTLEAFNONTERMINAL_H

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

#include "ASTLeafNode.hpp"
#include "../common/BSNonTerminal.hpp"
#include "../common/BSTerminal.hpp"

class ASTLeafNonTerminal :public ASTLeafNode
{
public:
  ASTLeafNonTerminal(char grammarChar, int rePos);
  virtual ~ASTLeafNonTerminal();
  void print() override;
  bool isNullable() override;
  std::set<BSGrammarChar> iniSet() override;
  std::set<BSGrammarChar> finSet() override;
  std::set<std::pair<BSGrammarChar, BSGrammarChar>> digSet() override;
};


#endif /* ASTLEAFNONTERMINAL_H */
