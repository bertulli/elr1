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

void ASTConcatOperator::print(){
  std::cout << '(' << m_opRepr << ' ';
  m_left->print();
  std::cout << ' ';
  m_right->print();
  std::cout << ')';
  return;
}

bool ASTConcatOperator::isNullable() {
    return m_right->isNullable() && m_left->isNullable();
}

std::set<BSGrammarChar> ASTConcatOperator::iniSet(){
  std::set<BSGrammarChar> res;
  if(m_left->isNullable()){
    res.merge(m_left->iniSet());
    res.merge(m_right->iniSet());
  } else {
    res.merge(m_left->iniSet());
  }
  return res;
}

std::set<BSGrammarChar> ASTConcatOperator::finSet() {
  std::set<BSGrammarChar> res;
  if(m_right->isNullable()){
    res.merge(m_left->iniSet());
    res.merge(m_right->iniSet());
  } else {
    res.merge(m_right->iniSet());
  }
  return res;
}

std::set<std::pair<BSGrammarChar, BSGrammarChar>> ASTConcatOperator::digSet(){
  std::set<std::pair<BSGrammarChar, BSGrammarChar>> res;
  res.merge(m_left->digSet());
  res.merge(m_right->digSet());
  for(auto left : m_left->finSet()){
    for(auto right : m_right->finSet()){
      res.insert(std::pair<BSGrammarChar, BSGrammarChar>(left, right));
    }
  }
  return res;
}