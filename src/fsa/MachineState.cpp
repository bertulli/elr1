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
#include <unordered_map>
#include <utility>

MachineState::MachineState(std::string name, bool finalState)
    : m_name{name}, m_final{finalState} {
  m_transitions = new std::unordered_map<BSTerminal, std::string, BSTerminal_hash>;
}

bool MachineState::addTransition(BSTerminal term, std::string dest){
  m_transitions->insert(std::make_pair(term, dest));
  return true;
}

std::unordered_map<BSTerminal, std::string, BSTerminal_hash>* MachineState::getTransitions(){
  return m_transitions;
}
