######################################################################
# Copyright 2022 Alessandro Bertulli                                 #
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
    
cmake_minimum_required(VERSION 3.10)

# set the project name
project(elr1 VERSION 0.1)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src)
