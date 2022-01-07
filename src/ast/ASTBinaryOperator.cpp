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

ASTBinaryOperator::ASTBinaryOperator(BinaryOperator op, ASTGenericNode *left,
                                     ASTGenericNode *right)
    : ASTInternalNode(), m_op(op), m_left(left), m_right(right) {
  if(m_op == BinaryOperator::alter)
    m_opRepr = 'U';
  else if(m_op == BinaryOperator::concat)
    m_opRepr = '.';
}

void ASTBinaryOperator::print(){
  std::cout << '(' << m_opRepr << ' ';
  m_left->print();
  std::cout << ' ';
  m_right->print();
  std::cout << ')';
  return;
}