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

#include "ASTCrossOperator.hpp"
#include "ASTInternalNode.hpp"

ASTCrossOperator::ASTCrossOperator(ASTGenericNode *child)
    : ASTUnaryOperator(child, UnaryOperator::cross, '+') {}

ASTCrossOperator::~ASTCrossOperator() {}

bool ASTCrossOperator::isBSNullable() { return m_child->isBSNullable(); }

std::set<BSGrammarChar> ASTCrossOperator::iniBSSet() { return m_child->iniBSSet(); }

std::set<BSGrammarChar> ASTCrossOperator::finBSSet() { return m_child->finBSSet(); }

std::set<std::pair<BSGrammarChar, BSGrammarChar>> ASTCrossOperator::digBSSet(){
  std::set<std::pair<BSGrammarChar, BSGrammarChar>> res;
  res.merge(m_child->digBSSet());
  for(auto left : m_child->finBSSet()){
    for(auto right : m_child->iniBSSet()){
      res.insert(std::pair<BSGrammarChar, BSGrammarChar>(left, right));
    }
  }
  return res;
}
