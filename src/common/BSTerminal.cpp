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

#include "BSTerminal.hpp"
#include "BSGrammarChar.hpp"

BSTerminal::BSTerminal(char term, int erPos)
  : BSGrammarChar{term,erPos} {}

BSTerminal::~BSTerminal() {}

bool operator==(const BSTerminal &term1, const BSTerminal &term2) {
  return term1.m_grammarChar == term2.m_grammarChar &&
    term1.m_rePos == term2.m_rePos;
}

std::set<BSTerminal> unionTerminal(std::set<BSTerminal> left,
                                 std::set<BSTerminal> right) {
  std::set<BSTerminal> res;
  for(auto i : left){
    if(res.count(i)==0){
      res.emplace(i);
    }
  }
  for (auto i : right) {
    if(res.count(i)==0){
      res.emplace(i);
    }
  }
  return res;
}
