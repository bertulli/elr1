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

#include "ASTBinaryOperator.hpp"
#include <iostream>

ASTBinaryOperator::ASTBinaryOperator(ASTGenericNode *left,
                                     ASTGenericNode *right, BinaryOperator op, char opRepr)
  : ASTInternalNode(), m_left(left), m_right(right), m_op(op), m_opRepr(opRepr) {}


void ASTBinaryOperator::print(){
  std::cout << '(' << m_opRepr << ' ';
  m_left->print();
  std::cout << ' ';
  m_right->print();
  std::cout << ')';
  return;
}
bool ASTBinaryOperator::isNullable() { return false; }

std::set<BSGrammarChar> ASTBinaryOperator::iniSet(){
  std::set<BSGrammarChar> res;
  return res;
}

std::set<BSGrammarChar> ASTBinaryOperator::finSet(){
  std::set<BSGrammarChar> res;
  return res;
}

std::set<std::pair<BSGrammarChar, BSGrammarChar>> ASTBinaryOperator::digSet(){
  std::set<std::pair<BSGrammarChar, BSGrammarChar>> res;
  return res;
}
