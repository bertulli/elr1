######################################################################
# Copyright Alessandro Bertulli 2022                                 #
# This file is part of ExpLaineR1.				     #
# 								     #
# ExpLaineR1 is free software: you can redistribute it and/or modify #
# it under the terms of the GNU General Public License as published  #
# by the Free Software Foundation, either version 3 of the License,  #
# or (at your option) any later version.			     #
# 								     #
# ExpLaineR1 is distributed in the hope that it will be useful, but  #
# WITHOUT ANY WARRANTY; without even the implied warranty of	     #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU   #
# General Public License for more details.			     #
# 								     #
# You should have received a copy of the GNU General Public License  #
# along with ExpLaineR1. If not, see				     #
# <https://www.gnu.org/licenses/>.				     #
######################################################################

add_library(astlib
  STATIC #for now
  ASTBinaryOperator.cpp
  ASTBinaryOperator.hpp
  ASTConcatOperator.cpp
  ASTConcatOperator.hpp
  ASTCrossOperator.cpp
  ASTCrossOperator.hpp
  ASTGenericNode.cpp
  ASTGenericNode.hpp
  AST.hpp
  ASTInternalNode.cpp
  ASTInternalNode.hpp
  ASTLeafEpsilon.cpp
  ASTLeafEpsilon.hpp
  ASTLeafNode.cpp
  ASTLeafNode.hpp
  ASTLeafNonTerminal.cpp
  ASTLeafNonTerminal.hpp
  ASTLeafTerminal.cpp
  ASTLeafTerminal.hpp
  ASTree.cpp
  ASTree.hpp
  ASTStarOperator.cpp
  ASTStarOperator.hpp
  ASTUnaryOperator.cpp
  ASTUnaryOperator.hpp
  ASTUnionOperator.cpp
  ASTUnionOperator.hpp
  )
target_link_libraries(astlib commonlib)

target_include_directories(astlib PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  )
