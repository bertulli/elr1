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

#include "BSGrammarChar.hpp"
#include "flags.h"
#include <iostream>

BSGrammarChar::BSGrammarChar(char grammarChar, int rePos)
    : m_grammarChar(grammarChar), m_rePos(rePos) {}

BSGrammarChar::~BSGrammarChar() {}

char BSGrammarChar::getGrammarChar() const{ return m_grammarChar; }

bool BSGrammarChar::operator<(const BSGrammarChar& other) const {
  return m_rePos < other.m_rePos;
}

std::ostream &operator<<(std::ostream &stream, const BSGrammarChar& gramChar) {
  stream << gramChar.m_grammarChar <<gramChar.m_rePos;
  return stream;
}

std::ostream &
operator<<(std::ostream &stream,
           const std::pair<BSGrammarChar, BSGrammarChar> &digram) {
  stream << '<' << digram.first << ", "
	 << digram.second << '>';
  return stream;
}

std::ostream &operator<<(std::ostream &stream, std::set<BSGrammarChar> set) {
  for(auto i : set){
    stream << i << ' ';
  }
  stream << "\n";
  return stream;
}

bool operator==(const BSGrammarChar first, const BSGrammarChar second) {
  return first.m_grammarChar == second.m_grammarChar &&
    first.m_rePos == second.m_rePos;
}

std::set<BSGrammarChar> BSGrammarChar::folBSSet(
    const std::set<std::pair<BSGrammarChar, BSGrammarChar>> digBSSet,
    BSGrammarChar keyGrammChar) {
  std::set<BSGrammarChar> res;
  for(auto i : digBSSet){
    if(i.first == keyGrammChar){
      res.emplace(i.second);
    }
  }
  return res;
}

std::set<BSGrammarChar>
BSGrammarChar::folBSSet(std::set<std::pair<BSGrammarChar, BSGrammarChar>> digBSSet,
         const char keyChar) {
  std::set<BSGrammarChar> res;
  for(auto i : digBSSet){
    if(i.first.m_grammarChar == keyChar){
      res.emplace(i.second);
    }
  }
  return res;
}

std::set<BSGrammarChar>
BSGrammarChar::genQPrime(std::set<std::pair<BSGrammarChar, BSGrammarChar>> digBSSet,
         std::set<BSGrammarChar> stateSet, const char keyChar) {
  std::set<BSGrammarChar> res;
  if(explainFsaFlag)
    std::cout << "Generating q':\n";
  
  for(auto b_i : stateSet){

    if(b_i.m_grammarChar == keyChar){
      if(explainFsaFlag)
	std::cout << "    For BSGC " << b_i << ":\n        ";
      for(auto temp : BSGrammarChar::folBSSet(digBSSet, b_i)){
	if(explainFsaFlag)
	  std::cout << temp << ' ';
	res.emplace(temp);
      }
    }
    if(explainFsaFlag)
      std::cout << "\n";
  }
  return res;
}

std::set<BSGrammarChar> unionGrammarChar(std::set<BSGrammarChar> left, std::set<BSGrammarChar> right) {
  std::set<BSGrammarChar> res;
  for(auto i : left){
    if(res.count(i)==0){
      res.emplace(i);
    }
  }
  for(auto i : right){
    if(res.count(i)==0){
      res.emplace(i);
    }
  }
  return res;
}
