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

#include "Pilot.hpp"

#include "../fsa/MachineNet.hpp"
#include "../common/flags.h"

Pilot *Pilot::m_instance = nullptr;

Pilot* Pilot::getInstance(){
  if(Pilot::m_instance == nullptr){
    Pilot::m_instance = new Pilot();
  }
  //  Pilot::m_instance->print();
  return Pilot::m_instance;
}

std::unordered_map<std::string, MState *> Pilot::getMStates() {
  return m_mStates;
}

void Pilot::setPrinter(PilotPrinter* printer){
  m_printer = printer;
  return;
}

void Pilot::printOnFile(std::string filePath){
  m_printer->printOnFile(filePath);
  return;
}

void Pilot::setFileType(std::string imageFileType) {
  m_printer->setFileType(imageFileType);
  return;
}

void Pilot::compileFile(std::string sourceFile, std::string destFile) {
  m_printer->compileFile(sourceFile,destFile);
  return;
}

Pilot::~Pilot() {}

Pilot::Pilot() {
  MachineNet* net{MachineNet::getInstance()};
  char axiom{net->getAxiom()};
  Machine* initialMachine{net->getMachine(std::string(1,axiom))};
  
  std::string initialStateName{initialMachine->getInitialState()};

  Item initialItem{initialStateName, initialMachine, initialMachine->getState(initialStateName), {'$'}};

  MState* initialMState = new MState{"I0", {initialItem}, true};

  initialMState->buildClosure();

  
  addMState(initialMState);

  //  print();

  bool pilotModified{true};

  int MStateIndex{1};
  while(pilotModified){
    
    pilotModified = false;

    for(auto mStateI : m_mStates){
      MState* I{mStateI.second};
      if(!I->isMarked()){
	I->mark();
	for(auto X : MachineNet::getInstance()->getAlphabet()){
	  MState Iprime{I->delta(X)};
	  if(debugFlag){
	    std::cout<<"Iprime:"<<Iprime<<'\n';
	  }
	  Iprime.buildClosure();
	  if(debugFlag){
	    std::cout<<"Iwithclosure:"<<Iprime<<'\n';
	  }
	  if(!Iprime.isEmpty()){
	    pilotModified = true;
	    //find Iprime
	    bool IprimeBelongsToR{false};
	    std::pair<std::string, MState*> possibleAlreadyExistingState;

	  
	    for(auto mState : m_mStates){
	      if(*(mState.second) == Iprime){
		IprimeBelongsToR = true;
		possibleAlreadyExistingState = mState;
		break;
	      }
	    }

	    if(!IprimeBelongsToR){
	      std::string newStateName{"I"+std::to_string(MStateIndex)};
	      MStateIndex++;
	      MState* newIprime = new MState{newStateName, Iprime.getBase(), Iprime.getClosure()};
	      m_mStates.emplace(newStateName, newIprime);
	      I->addTransition(X, newIprime);
	    } else {
	      I->addTransition(X, possibleAlreadyExistingState.second);
	    }
	  
	  
	  }
	}
      }  
    }
    
  }

  
}

bool Pilot::addMState(MState *mState) {
  m_mStates.emplace(mState->getName(), mState);
  return true;
}

void Pilot::print() {
  std::cout << "Pilot automaton:\n";
  for(auto mState : m_mStates){
    std::cout << mState.first << '\n'
	      << *(mState.second)
	      << "Transitions:\n";
    for(auto t : mState.second->getTransitions()){
      std::cout << '-' << t.first << "-> " << t.second->getName() << '\n';
    }
  }
}
