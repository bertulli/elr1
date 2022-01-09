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

#include "ASTStarOperator.hpp"
#include "ASTGenericNode.hpp"
#include "ASTUnaryOperator.hpp"
#include "ASTInternalNode.hpp"

ASTStarOperator::ASTStarOperator(ASTGenericNode *child)
    : ASTUnaryOperator(child, UnaryOperator::star, '*') {}

ASTStarOperator::~ASTStarOperator() {}

bool ASTStarOperator::isNullable() { return true; }

std::set<BSGrammarChar> ASTStarOperator::iniSet() { return m_child->iniSet(); }

std::set<BSGrammarChar> ASTStarOperator::finSet() { return m_child->finSet(); }

std::set<std::pair<BSGrammarChar, BSGrammarChar>> ASTStarOperator::digSet() {
  std::set<std::pair<BSGrammarChar, BSGrammarChar>> res;
  res.merge(m_child->digSet());
  for(auto left : m_child->finSet()){
    for(auto right : m_child->iniSet()){
      res.insert(std::pair<BSGrammarChar, BSGrammarChar>(left, right));
    }
  }
  return res;
}
