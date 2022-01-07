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

find_package(FLEX)
find_package(BISON)

flex_target(lexer lexer.ll  "${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp")

bison_target(parser
  parser.yy #bison inputfile
  ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp
  DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.hpp)

add_flex_bison_dependency(lexer parser)

#include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(parserlib STATIC
  ${BISON_parser_OUTPUTS}
  ${FLEX_lexer_OUTPUTS}
  )

target_link_libraries(parserlib fsalib astlib)

target_include_directories(parserlib PUBLIC
  "${PROJECT_BINARY_DIR}/src/parser"
  "${PROJECT_SOURCE_DIR}/src"
  "${PROJECT_SOURCE_DIR}/src/ast"
)
