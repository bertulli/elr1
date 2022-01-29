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

#include "MState.hpp"

MState::MState(std::string name, std::set<Item> set, bool isClosure)
  : m_name{name}, m_marked{false} {
  if(isClosure){
    m_closure=set;
  } else{
    m_base=set;
  }
}

MState::MState(std::string name, std::set<Item> base, std::set<Item> closure)
  : m_name{name}, m_base{base}, m_closure{closure}, m_marked{false} {}

MState::~MState() {}

std::string MState::getName() { return m_name; }

std::set<Item> MState::getBase() { return m_base; }

std::set<Item> MState::getClosure(){return m_closure;}

std::unordered_map<char, MState *> MState::getTransitions() {
  return m_transitions;
}

void MState::addTransition(char label, MState* destState) {
  m_transitions.emplace(label, destState);
  return;
}

void MState::mark() { m_marked = true; }

bool MState::isMarked() { return m_marked; }

bool MState::isEmpty(){return m_base.empty() && m_closure.empty();}

MState::MState()
  : m_marked{false} {}

MState MState::delta(char label) {
  MState res;

  for(auto item : m_base){
    MachineState* itemState{item.getMachine()->getState(item.getStateName())};
    if(itemState->getTransitions()->count(label) == 1){
      std::string stateName{itemState->getTransitions()->at(label)};
      MachineState* destStateAddr{item.getMachine()->getState(stateName)};
      res.addBaseItem(Item{stateName, item.getMachine(), destStateAddr, item.getLookaheads()});
    }
  }

  for(auto item : m_closure){
    MachineState* itemState{item.getMachine()->getState(item.getStateName())};
    if(itemState->getTransitions()->count(label) == 1){
      std::string stateName{itemState->getTransitions()->at(label)};
      MachineState* destStateAddr{item.getMachine()->getState(stateName)};
      res.addBaseItem(Item{stateName, item.getMachine(), destStateAddr, item.getLookaheads()});
    }
  }
  
  return res;
}

bool MState::addBaseItem(Item newItem) {
  bool itemAlreadyPresent{false};
  bool mStateModified{false};
  
  for(auto baseItem : m_base){
    if(baseItem.getStateName() == newItem.getStateName()){
      itemAlreadyPresent = true;
      mStateModified = baseItem.addLookahead(newItem.getLookaheads());
      break;
    }
  }

  //this should not be necessary, as this method should take care only of the base
  
  // if(!itemAlreadyPresent){
  //   for(auto closureItem : m_closure){
  //     if(closureItem.getStateName() == newItem.getStateName()){
  // 	itemAlreadyPresent = true;
  // 	itemModified = closureItem.addLookahead(newItem.getLookaheads());
  // 	break;
  //     }
  //   }
  // }

  if(!itemAlreadyPresent){
    m_base.emplace(newItem);
    mStateModified =true;
  }

  return mStateModified;
    
}

bool MState::addBaseItem(std::set<Item> newItems) {
  bool mStateModified{false};
  
  for(auto newItem : newItems){
    mStateModified |= addBaseItem(newItem);
  }
  return mStateModified;
}

bool operator==(const MState &first, const MState &second) {
  return first.m_base == second.m_base &&
    first.m_closure == second.m_closure;
}

bool MState::addClosure(std::set<Item> newClosure) {
  bool closureModified{false};
  for(auto currNewItem : newClosure){
    bool stateAlreadyPresent{false};
    
    for(auto existingClosureState : m_closure){
      if(existingClosureState.getStateName() == currNewItem.getStateName()){
	stateAlreadyPresent = true;
	if(existingClosureState.addLookahead(currNewItem.getLookaheads())){
	  closureModified=true;
	  break;
	}
      }
    }

    if(! stateAlreadyPresent){
      m_closure.emplace(currNewItem);
      closureModified=true;
    }
  }

  return closureModified;
}

void MState::buildClosure() {
  bool closureHasChanged{false};
  
  for(auto baseState : m_base){
    m_closure.merge(baseState.closure());
  }
  if(!m_closure.empty()){
    closureHasChanged = true;
  }
  
  while(closureHasChanged){
    closureHasChanged=false;
    for(auto closState : m_closure){
      if(addClosure(closState.closure())){
	closureHasChanged=true;
	break;
      }
    }
  }
}

std::ostream &operator<<(std::ostream &stream, const MState &mState) {
  stream << "Temporary print for mstate" << mState.m_name<<"\n"
	 << "Base:\n";
  for(auto baseItem : mState.m_base){
    stream << baseItem << '\n';
  }
  stream << "Closure:\n";
  for(auto closureItem :mState.m_closure){
    stream << closureItem << '\n';
  }
  return stream;
}
