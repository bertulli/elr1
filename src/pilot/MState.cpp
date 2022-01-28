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

MState::MState(std::set<Item> set, bool isClosure) {
  if(isClosure){
    m_closure=set;
  } else{
    m_base=set;
  }
}

MState::~MState() {}

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
  stream << "Temporary print for mstate\n"
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
