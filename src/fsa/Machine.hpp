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
#include "DotPrinter.hpp"
#include "LatexPrinter.hpp"
#include "../ast/ASTGenericNode.hpp"
#include "../ast/ASTree.hpp"
#include <unordered_map>
#include <string>

class DotPrinter; //for compiler
class MachinePrinter;
class LatexPrinter;

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
  bool addState(std::set<BSGrammarChar> BSSet, std::string stateName = "", bool finalState = false, bool initialState = false);

  bool addState(MachineState* statePtr);

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
  bool registerTransition(std::string sourceState, std::string destState, char label);

  //bool generateBSMachine();

  int addTree(ASTGenericNode* subtree);

  bool addAlphabet(std::set<char>* alphabet);

  ASTree* getTree();

  std::set<char>* getAlphabet();

  MachineState * getState(std::string state);

  std::string getInitialState();

  bool BSBuild();

  //taken form https://en.wikipedia.org/wiki/Pairing_function
  int index(int x, int y);

  std::pair<int, int> coord(int index);

  std::pair<int, int> latexCoord(int index);

  //  bool produceDot(std::string fileName);

  //  bool compileDot(std::string inputFile, std::string outputFile, std::string fileType = "png");

  std::set<char> iniPilotInitialStateSet();

  void printDebug();

  void setPrinter(MachinePrinter* printer);

  void print(std::string filePath);

  void setFileType(std::string fileType);
  
  bool compileFile(std::string inputFile, std::string outputFile);

  friend void DotPrinter::printOnFile(std::string fileName, Machine* machine);
  friend void LatexPrinter::printOnFile(std::string fileName, Machine* machine);
private:
  void finalizeBSStates();
  std::unordered_map<std::string, MachineState*> m_states;
  ASTree* m_tree;
  std::set<char>* m_alphabet;
  std::string m_initialState;
  std::string m_machineName;
  MachinePrinter* m_printer;
};

#endif /* FSA_H */
