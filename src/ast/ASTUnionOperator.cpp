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

#include "ASTUnionOperator.hpp"
#include <iostream>

ASTUnionOperator::ASTUnionOperator(ASTGenericNode *left, ASTGenericNode *right)
  : ASTBinaryOperator(left, right, BinaryOperator::alter, 'U') {}

ASTUnionOperator::~ASTUnionOperator() {}

void ASTUnionOperator::print(){
  std::cout << '(' << m_opRepr << ' ';
  m_left->print();
  std::cout << ' ';
  m_right->print();
  std::cout << ')';
  return;
}

bool ASTUnionOperator::isNullable() {
    return m_right->isNullable() || m_left->isNullable();
}

std::set<BSGrammarChar> ASTUnionOperator::iniSet(){
  std::set<BSGrammarChar> res;
  res.merge(m_right->iniSet());
  res.merge(m_left->iniSet());
  return res;
}

std::set<BSGrammarChar> ASTUnionOperator::finSet() {
  std::set<BSGrammarChar> res;
  res.merge(m_right->iniSet());
  res.merge(m_left->iniSet());
  return res;
}

std::set<std::pair<BSGrammarChar, BSGrammarChar>> ASTUnionOperator::digSet(){
  std::set<std::pair<BSGrammarChar, BSGrammarChar>> res;
  res.merge(m_left->digSet());
  res.merge(m_right->digSet());
  return res;
}
