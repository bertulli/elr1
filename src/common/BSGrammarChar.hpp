#ifndef GRAMMARCHAR_H
#define GRAMMARCHAR_H

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

#include <ostream>
#include <set>

class BSGrammarChar
{
public:
  BSGrammarChar(char m_grammarChar, int m_rePos);
  char getGrammarChar() const;
  virtual ~BSGrammarChar();
  bool operator<(const BSGrammarChar &other) const;
  static std::set<BSGrammarChar> folBSSet(std::set<std::pair<BSGrammarChar, BSGrammarChar>> digBSSet, const BSGrammarChar keyGrammChar);
  static std::set<BSGrammarChar> folBSSet(std::set<std::pair<BSGrammarChar, BSGrammarChar>> digBSSet, const char keyChar);

  //From the state `stateSet', returns the set of followers from that state of a given char
  static std::set<BSGrammarChar> genQPrime(std::set<std::pair<BSGrammarChar, BSGrammarChar>> digBSSet, std::set<BSGrammarChar> stateSet, const char keyChar);

  //Operator overload
  friend std::ostream& operator<<(std::ostream& stream, const BSGrammarChar& gramChar);
  friend std::ostream& operator<<(std::ostream& stream, const std::pair<BSGrammarChar, BSGrammarChar>& digram);
  friend bool operator==(const BSGrammarChar first, const BSGrammarChar second);
  friend std::ostream& operator<<(std::ostream& stream, std::set<BSGrammarChar> set);
protected:
  char m_grammarChar;
  int m_rePos;
};

std::set<BSGrammarChar> unionGrammarChar(std::set<BSGrammarChar> left,
                                         std::set<BSGrammarChar> right);
//std::set<BSGrammarChar> unionFollowers(std::set<

#endif /* GRAMMARCHAR_H */
