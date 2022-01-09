#ifndef FSA_H
#define FSA_H

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
#include "../ast/ASTGenericNode.hpp"
#include "../ast/ASTree.hpp"
#include <unordered_map>
#include <string>

class Machine{
public:
  /**
   * @brief      Constructor
   *
   * @details    Creates a Machine with no state
   *
   * @param      machineName name of the Machine
   *
   * @return     no
   */
  Machine(std::string machineName);

  /**
   * @brief      Add a state to the Machine
   *
   * @param      stateName name of the state
   * @param      finalState true if the state to be added is final
   * @param      initialState true if the state to be added is the initial one
   *
   * @return     true if successful
   */
  bool addState(std::string stateName, bool finalState = false, bool initialState = false);

  /**
   * @brief      add a transition to the Machine
   *
   * @details    add a transition from one state to the other, labelled with the correct terminal
   *
   * @param      sourceState name of the source state
   * @param      destState name of the destination state
   * @param      label terminal that labels the transition
   *
   * @return     true if successful
   */
  bool registerTransition(std::string sourceState, std::string destState, BSTerminal label);

  int addTree(ASTGenericNode* subtree);

  ASTree* getTree();

  void printDebug();
private:
  std::unordered_map<std::string, MachineState*> m_states;
  ASTree* m_tree;
  std::string m_initialState;
  std::string m_machineName;
};

#endif /* FSA_H */
