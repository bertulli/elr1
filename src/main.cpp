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
											  
#include "fsa/Machine.hpp"

#include <iostream>
#include <parser.hpp>

int main(int argc, char *argv[])
{

    yyparse();
    return 0;
    
  // std::cout << "Hi!\n";
  // Machine simpleRegex{"simpleNameForRegex"};
  // simpleRegex.addState("q0");
  // simpleRegex.addState("q1");
  // simpleRegex.registerTransition("q0", "q1", 'a');
  // simpleRegex.printDebug();
  // return 0;
}
