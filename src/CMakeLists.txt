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

add_subdirectory(fsa)
add_subdirectory(ast)
add_subdirectory(parser)
add_subdirectory(common)
add_subdirectory(pilot)
#to create a library

#include_directories(${CMAKE_CURRENT_BINARY_DIR})


# add the executable
add_executable(elr1 main.cpp)

#set(CMAKE_CXX_STANDARD 11)
#set_target_properties(elr1 PROPERTIES CXX_STANDARD 17)


target_include_directories(elr1 PUBLIC
  "${PROJECT_BINARY_DIR}"
  "${PROJECT_BINARY_DIR}/src/parser"
  )

#target_link_libraries(elr1 ${FLEX_LIBRARIES})


target_link_libraries(elr1 #target in which link
  #  PUBLIC #mode
  fsalib #library name
  astlib
  parserlib
  commonlib
  pilotlib
  )
