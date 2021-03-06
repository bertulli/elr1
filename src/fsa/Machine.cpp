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
#include "MachinePrinter.hpp"
#include "MachineState.hpp"
#include "../ast/ASTGenericNode.hpp"
#include "../ast/ASTree.hpp"
#include "../common/BSGrammarChar.hpp"
#include "../common/flags.h"
#include <cstdlib>
#include <vector>
#include <utility>
#include <iostream>
#include <fstream>
#include <math.h>



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

std::set<char> *Machine::getAlphabet() { return m_alphabet; }

MachineState *Machine::getState(std::string state) { return m_states[state]; }

std::string Machine::getInitialState() {
  return m_initialState;
}

bool Machine::addState(std::set<BSGrammarChar> BSSet, std::string stateName, bool finalState, bool initialState){
  MachineState *newStatePtr = new MachineState{BSSet, this, stateName};
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
  if(explainFsaFlag)
    std::cout << "adding transition " << sourceState << " -" << label << "-> " << destState << "\n";
  sourceMachineState->addTransition(label, destState);
  return true;
}


int Machine::index(int x, int y) {
  return ((x + y) * (x + y + 1)) / 2 + y;
}

std::pair<int, int> Machine::coord(int index) {
  int w = (int) ((sqrt(8 * index + 1) - 1) / 2);
  int t = (w * w + w) / 2;
  int y = index - t;
  int x = w - y;
  return std::make_pair(x, y);
}

std::pair<int, int> Machine::latexCoord(int index) {
  constexpr int scaleFactor{3};
  auto pair = coord(index);
  return std::make_pair(pair.first * scaleFactor, -pair.second * scaleFactor);
}

void Machine::setPrinter(MachinePrinter *printer) {
  m_printer = printer;
}

void Machine::print(std::string filePath) {
  std::cout << "Printing " << filePath << "... ";
  m_printer->printOnFile(filePath, this);
  std::cout << "done\n";
  return;
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

std::set<char> Machine::iniPilotInitialStateSet() {
  return m_states[m_initialState]->iniPilotSet();
}

bool Machine::BSBuild() {
  //q0 = ini(e'$)
  std::string initialStateName = "0" + m_machineName;
  MachineState* q0 = new MachineState{getTree()->getRoot()->iniBSSet(), this, initialStateName, true};
  addState(q0);
  m_initialState = initialStateName;
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

	if(explainFsaFlag){
	  std::cout << "\nprocessing and marking state " << q->getName() << ":\n";
	  std::cout << "its stateset is " << q->getBSState() << "\n";
	}
	for(char b : q->getStateAlphabet()){           //for every possible alphabet character
	  if(explainFsaFlag)
	    std::cout << "\nCharacter b is " << b << ":\n";
	  std::set<BSGrammarChar> qprime = BSGrammarChar::genQPrime(digSet, q->getBSState(), b);

	  if(explainFsaFlag)
	    std::cout << "q' is: " << qprime << "\n";
	  
	  if(! qprime.empty()){
	    if(explainFsaFlag)
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
	    std::string stateNameQPrime = std::to_string(stateCounter) + m_machineName;
	    if(!belongs){//then
	      if(explainFsaFlag)
		std::cout << "q' is a new state. Calling it " << stateNameQPrime << "\n";
	      m_states.emplace(stateNameQPrime, new MachineState{qprime, this, stateNameQPrime});
	      destState = stateNameQPrime;
	      stateCounter++;
	    } else {
	      if(explainFsaFlag)
		std::cout << "q' is not a new state\n";
	    }
	    registerTransition(pairq.first, destState, b);
	  }
	}
      }
    }
  }
  finalizeBSStates();
  return true;
}

void Machine::finalizeBSStates() {
  for(auto state : m_states){
    std::set<BSGrammarChar> BSState{state.second->getBSState()};
    BSGrammarChar terminator{'$', 0};
    if(BSState.count(terminator) > 0){
      state.second->makeFinal();
    }
  }
  return;
}

// bool Machine::produceDot(std::string fileName) {
  
//   return true;
// }

// bool Machine::compileDot(std::string inputFile, std::string outputFile,
//                          std::string fileType) {
//   return true;
// }

void Machine::setFileType(std::string fileType){
  m_printer->setFileType(fileType);
  return;
}

bool Machine::compileFile(std::string inputFile, std::string outputFile){
  return m_printer->compileFile(inputFile, outputFile);
}
