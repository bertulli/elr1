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

#include "ASTConcatOperator.hpp"
#include <iostream>

ASTConcatOperator::ASTConcatOperator(ASTGenericNode *left, ASTGenericNode *right)
  : ASTBinaryOperator(left, right, BinaryOperator::concat, '.') {}

ASTConcatOperator::~ASTConcatOperator() {}

bool ASTConcatOperator::isBSNullable() {
    return m_right->isBSNullable() && m_left->isBSNullable();
}

std::set<BSGrammarChar> ASTConcatOperator::iniBSSet(){
  std::set<BSGrammarChar> res;
  if(m_left->isBSNullable()){
    res.merge(m_left->iniBSSet());
    res.merge(m_right->iniBSSet());
  } else {
    res.merge(m_left->iniBSSet());
  }
  return res;
}

std::set<BSGrammarChar> ASTConcatOperator::finBSSet() {
  std::set<BSGrammarChar> res;
  if(m_right->isBSNullable()){
    res.merge(m_left->iniBSSet());
    res.merge(m_right->iniBSSet());
  } else {
    res.merge(m_right->iniBSSet());
  }
  return res;
}

std::set<std::pair<BSGrammarChar, BSGrammarChar>> ASTConcatOperator::digSet(){
  std::set<std::pair<BSGrammarChar, BSGrammarChar>> res;
  res.merge(m_left->digSet());
  res.merge(m_right->digSet());
  for(auto left : m_left->finBSSet()){
    for(auto right : m_right->finBSSet()){
      res.insert(std::pair<BSGrammarChar, BSGrammarChar>(left, right));
    }
  }
  return res;
}
