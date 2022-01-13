#ifndef TERMINAL_H
#define TERMINAL_H

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

#include <functional>
#include <set>
#include "BSGrammarChar.hpp"

// struct BSTerminal_hash
// {
//   template <class T1>
//   std::size_t operator () (T1 const &v) const
//   {
//     return std::hash<char>()(v.getGrammarChar());    
//   }
// };

class BSTerminal : public BSGrammarChar
{
  // add Cents + Cents using a friend function
  friend bool operator==(const BSTerminal &term1, const BSTerminal &term2);
public:
  BSTerminal(char term, int erPos);
  virtual ~BSTerminal();
};

std::set<BSTerminal> unionTerminal(std::set<BSTerminal> left, std::set<BSTerminal> right);

#endif /* TERMINAL_H */
