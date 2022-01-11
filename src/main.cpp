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

#include "fsa/Machine.hpp"
#include "fsa/MachineNet.hpp"
#include <ast/AST.hpp>

#include <iostream>
#include <parser.hpp>
#include <string>


int main(int argc, char *argv[])
{
    yyparse();
    MachineNet* net = MachineNet::getInstance();
    Machine* m=net->getMachine("S");
    ASTree* t=m->getTree();
    ASTGenericNode* root=t->getRoot();
    std::string res =root->isBSNullable() ? "true" : "false" ;
    std::cout<< "should be false (check grammar):\n" << res <<"\n";

    std::cout << "Chech for finBSSet:\n";
    for(auto i : root->finBSSet()){
      std::cout << i.getGrammarChar() << "\n";
    }
    
    std::cout << "Check per i punti e vrgola\n";
    for(auto m : net->getMachines()){
      std::cout << m.first << "\n";
    }

    m=net->getMachine("A");
    t=m->getTree();
    root=t->getRoot();

    std::cout << "Ini set:\n";
    for(auto i : root->iniBSSet()){
      std::cout << i << ' ';
    }
    std::cout << "\nFin set:\n";
    for(auto i : root->finBSSet()){
      std::cout << i << ' ';
    }
    auto digSet = root->digBSSet();
    std::cout <<"\nDig set (should not contain <b2, b2> nor <a4, $0>):\n";
    for(auto i : digSet){
      std::cout << i << ' ';
    }

    std::cout <<"\nFollowers of b2:\n";
    for(auto i : BSGrammarChar::folBSSet(digSet, BSGrammarChar('b',2))){
      std::cout << i << ' ';
    }
    std::cout <<"\nFollowers of b3:\n";
    for(auto i : BSGrammarChar::folBSSet(digSet, BSGrammarChar('b',3))){
      std::cout << i << ' ';
    }
    std::cout<<std::endl;
    return 0;
    
  // std::cout << "Hi!\n";
  // Machine simpleRegex{"simpleNameForRegex"};
  // simpleRegex.addState("q0");
  // simpleRegex.addState("q1");
  // simpleRegex.registerTransition("q0", "q1", 'a');
  // simpleRegex.printDebug();
  // return 0;
}
