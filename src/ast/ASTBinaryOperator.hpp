
#ifndef ASTBINARYOPERATOR_H
#define ASTBINARYOPERATOR_H

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


#include "ASTInternalNode.hpp"
#include "ASTGenericNode.hpp"

class ASTBinaryOperator :public ASTInternalNode
{
public:
  ASTBinaryOperator(ASTGenericNode* left, ASTGenericNode* right, BinaryOperator op, char opRepr);
  void print() override;
protected:
  BinaryOperator m_op;
  char m_opRepr;
  ASTGenericNode* m_left;
  ASTGenericNode* m_right;
};



#endif /* ASTBINARYOPERATOR_H */
