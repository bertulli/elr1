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

#include "Machine.hpp"
#include "MachineState.hpp"
#include "../ast/ASTGenericNode.hpp"
#include "../ast/ASTree.hpp"
#include <utility>
#include <iostream>

Machine::Machine(std::string machineName)
  : m_machineName{machineName}
{};

int Machine::addTree(ASTGenericNode *subtree){
  m_tree = new ASTree(subtree);
  return 1;
}

ASTree *Machine::getTree() {
  return m_tree;  
}

bool Machine::addState(std::string stateName, bool finalState, bool initialState){
  MachineState *newStatePtr = new MachineState{stateName, finalState};
  std::pair<std::string, MachineState*> newPair{stateName, newStatePtr};
  m_states.insert(newPair);
  if(initialState){
    m_initialState = stateName;
  }
  return true;
}

bool Machine::registerTransition(std::string sourceState, std::string destState, Terminal label){
  m_states[sourceState]->addTransition(label, destState);
  return true;
}

void Machine::printDebug(){
  std::cout << m_machineName << " debug informations\n"
	    << "States of the machine:\n";
  for(const auto& state_i : m_states){
    std::cout << state_i.first << ":\n";
    std::unordered_map<Terminal, std::string>& state_iTrans = state_i.second->getTransitions();
    for (const auto& trans_i : state_iTrans) {
      std::cout << "\t" << trans_i.first << " -> " << trans_i.second << "\n";
    	}
      }
  return;
}

