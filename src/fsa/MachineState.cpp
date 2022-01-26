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

#include "MachineState.hpp"
#include "MachineNet.hpp"
#include <unordered_map>
#include <utility>

MachineState::MachineState(std::string name, bool finalState, Machine* machine)
  : m_name{name}, m_final{finalState}, m_machine{machine}, m_BSMarked{false} {
  m_transitions = new std::unordered_map<char, std::string>;
}

MachineState::MachineState(std::set<BSGrammarChar> BSState, Machine* machine, std::string name, bool initial)
  : m_BSState{BSState}, m_machine{machine}, m_BSMarked{false}, m_name{name}, m_initial{initial} {
  m_transitions = new std::unordered_map<char, std::string>;
  for(auto b_i : m_BSState){
    m_stateAlphabet.emplace(b_i.getGrammarChar());
  }
}

void MachineState::mark() { m_BSMarked = true; }

bool MachineState::addTransition(char grammarChar, std::string dest){
  m_transitions->emplace(std::make_pair(grammarChar, dest));
  return true;
}

std::unordered_map<char, std::string>* MachineState::getTransitions(){
  return m_transitions;
}

std::string MachineState::getName(){ return m_name; }

std::set<BSGrammarChar> MachineState::getBSState() { return m_BSState; }

std::set<char> MachineState::getStateAlphabet() { return m_stateAlphabet; }

std::set<char> MachineState::iniPilotSet() {
  std::set<char> res;
  for(auto t : *m_transitions){
    char c = t.first;
    if(c > 'a' && c < 'z'){  //is lowercase, therefore a terminal
      res.emplace(c);
    } else {  //is capital, therefore a non terminal
      std::set<char> iniB = MachineNet::getInstance()->getMachine(std::string(1,c))->iniPilotInitialStateSet();
      if(! iniB.empty()){ //ini(B) non nullable
	res.merge(iniB);
      } else { //ini(B) nullable
	res.merge(m_machine->getState(t.second)->iniPilotSet());
      }
    }
  }
  return res;
}

bool MachineState::isMarked(){ return m_BSMarked; }

bool MachineState::isFinal() { return m_final; }

void MachineState::makeFinal() {
  m_final = true;
  return;
}
