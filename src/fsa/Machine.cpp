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
#include "../common/BSGrammarChar.hpp"
#include <utility>
#include <iostream>

Machine::Machine(std::string machineName)
  : m_machineName{machineName}
{};

int Machine::addTree(ASTGenericNode *subtree){
  m_tree = new ASTree(subtree);
  return 1;
}

bool Machine::addAlphabet(std::set<char>* alphabet) {
  m_alphabet = alphabet;
  return true;
}

ASTree *Machine::getTree() { return m_tree; }

std::set<char>* Machine::getAlphabet(){ return m_alphabet; }

bool Machine::addState(std::set<BSGrammarChar> BSSet, std::string stateName, bool finalState, bool initialState){
  MachineState *newStatePtr = new MachineState{BSSet, stateName};
  std::pair<std::string, MachineState*> newPair{stateName, newStatePtr};
  m_states.insert(newPair);
  if(initialState){
    m_initialState = stateName;
  }
  return true;
}

bool Machine::addState(MachineState* statePtr) {
  m_states.emplace(statePtr->getName(), statePtr);
  return true;
}

bool Machine::registerTransition(std::string sourceState, std::string destState, char label){
  MachineState* sourceMachineState = m_states[sourceState];
  std::cout << "adding transition " << sourceState << " -" << label << "-> " << destState << "\n";
  sourceMachineState->addTransition(label, destState);
  return true;
}

void Machine::printDebug(){
  std::cout << m_machineName << " debug informations\n"
	    << "States of the machine:\n";
  for(const auto& state_i : m_states){
    std::cout << state_i.first << ":\n";
    std::unordered_map<char, std::string>& state_iTrans = (*state_i.second->getTransitions());
    for (const auto& trans_i : state_iTrans) {
      std::cout << "\t" << trans_i.first << " -> " << trans_i.second << "\n";
    	}
      }
  return;
}

bool Machine::BSBuild() {
  //q0 = ini(e'$)
  MachineState* q0 = new MachineState{getTree()->getRoot()->iniBSSet(), "q0"};
  addState(q0);
  std::set <std::pair<BSGrammarChar, BSGrammarChar>> digSet = getTree()->getRoot()->digBSSet();
  int stateCounter{1};
  bool finished{false};
  while(!finished){
    finished=true;
    for(auto pairq : m_states){
      MachineState*& q = pairq.second;
      if(! q->isMarked()){               //if there's still one state not marked
	finished=false;                  //continue the algorithm at the next iteration
	q->mark();                       //and mark the state as marked

	std::cout << "\nprocessing and marking state " << q->getName() << ":\n";
	std::cout << "its stateset is " << q->getBSState() << "\n";
	for(char b : q->getStateAlphabet()){           //for every possible alphabet character
	  std::cout << "\nCharacter b is " << b << ":\n";
	  std::set<BSGrammarChar> qprime = BSGrammarChar::genQPrime(digSet, q->getBSState(), b);

	  std::cout << "q' is: " << qprime << "\n";
	  ///////////////////////////////////////////////////

	  
	  if(! qprime.empty()){
	    std::cout << "q' is not empty\n";
	    //if(qprime is not in m_states)
	    bool belongs{false};
	    std::string destState;
	    for(auto i : m_states){
	      if(i.second->getBSState() == qprime){
		destState = i.second->getName();
		belongs = true;
		break;
	      }
	    }
	    std::string stateNameQPrime = "q" + std::to_string(stateCounter);
	    if(!belongs){//then
	      std::cout << "q' is a new state. Calling it " << stateNameQPrime << "\n";
	      m_states.emplace(stateNameQPrime, new MachineState{qprime, stateNameQPrime});
	      destState = stateNameQPrime;
	      stateCounter++;
	    } else {
	      std::cout << "q' is not a new state\n";
	    }
	    registerTransition(pairq.first, destState, b);
	  }
	}
      }
    }
  }
  return true;
}
