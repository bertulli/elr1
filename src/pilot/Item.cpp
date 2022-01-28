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

#include "Item.hpp"
#include "../fsa/MachineNet.hpp"
#include "../common/flags.h"

Item::Item(std::string stateName, Machine* machineAddr, MachineState* stateAddr, std::set<char> lookaheads)
  : m_stateName{stateName}, m_machine{machineAddr}, m_machineState{stateAddr}, m_lookaheadSet{lookaheads} {}

Item::~Item() {}

bool Item::addLookahead(char lookahead) {
  if(m_lookaheadSet.count(lookahead) ==0){//lookahead is not already present
    m_lookaheadSet.emplace(lookahead);
    return true;
  } else {
    return false;
  }
}

bool Item::addLookahead(std::set<char> lookaheads) {
  bool lookaheadSetModified{false};
  for(auto i : lookaheads){
    if(m_lookaheadSet.count(i)==0){//lookahead was not already present
      m_lookaheadSet.emplace(i);
      lookaheadSetModified=true;
    }
  }
  return lookaheadSetModified;
}

std::string Item::getStateName() const { return m_stateName; }

std::set<char> Item::getLookaheads() const { return m_lookaheadSet; }

bool Item::operator<(const Item &other) const {
  return (m_stateName < other.m_stateName) ||
    (m_lookaheadSet < other.m_lookaheadSet);
}

std::ostream &operator<<(std::ostream &stream,
                         const std::set<char> &lookaheads) {
  for(auto i : lookaheads){
    stream << i << ' ';
  }
  return stream;
}

std::ostream & operator<<(std::ostream & stream, const Item &item) {
  stream << "<" << item.m_stateName << ", {" << item.m_lookaheadSet << "}>";
  return stream;
}

std::ostream &operator<<(std::ostream &stream, const std::set<Item> &items) {
  for(auto i : items){
    stream << i << ' ';
  }
  return stream;
}

std::set<Item> Item::closure() {
  std::set<Item> res;
  MachineNet* net = MachineNet::getInstance();
  for(auto currTransition : *(m_machineState->getTransitions())){
    char B = currTransition.first;
    if(B > 'A' && B < 'Z'){ //is a non terminal
      Machine *newMachine = net->getMachine(std::string(1, B));
      std::string newInitialState = newMachine->getInitialState();

      if(debugFlag){
	std::cout << "Building closure starting from " << *this << "\n"
		  << "analizing transition from " << m_machineState->getName()
		  << " -" << B << "-> " << currTransition.second <<"\n";
      }
      
      std::set<char> iniOfR = m_machine->getState(currTransition.second)->iniPilotSet();
      if(debugFlag){
	std::cout << "iniOfR for item " << *this << " and state " << ": " << iniOfR << "\n";
      }
       if(iniOfR.count('&') == 1) { //having an epsilon means state R is nulable:inherit lookahead
	iniOfR.erase('&');
	customMerge(iniOfR, m_lookaheadSet);
      }
      if(! iniOfR.empty()){ //normal
	res.emplace(newInitialState, newMachine, newMachine->getState(newInitialState), iniOfR);
      }
    }
  }
  if(debugFlag){
    std::cout << "closure is " << res << '\n';
  }
  return res;
}

void customMerge(std::set<char> &dest, std::set<char> &source) {
  for(char c : source){
    dest.emplace(c);
  }
  return;
}
