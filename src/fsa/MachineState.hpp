#ifndef MACHINESTATE_H
#define MACHINESTATE_H

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

#include <string>
#include <unordered_map>
#include "../common/BSTerminal.hpp"



class MachineState{
public:
  MachineState(std::string name, bool finalState);
  MachineState(std::set<BSGrammarChar> BSState, std::string name = "", bool initial = false);
  bool addTransition(char grammarChar, std::string dest);
  std::unordered_map<char, std::string>* getTransitions();
  std::string getName();
  std::set<BSGrammarChar> getBSState();
  std::set<char> getStateAlphabet();
  bool isFinal();
  bool isMarked();
  void mark();
  void makeFinal();
private:
  std::string m_name;
  std::unordered_map<char, std::string>* m_transitions;
  std::set<BSGrammarChar> m_BSState;
  std::set<char> m_stateAlphabet;
  bool m_initial;
  bool m_final;
  bool m_BSMarked;
};

#endif /* MACHINESTATE_H */
