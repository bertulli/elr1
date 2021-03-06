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

%{
#include <stdio.h>
#include <common/BSTerminal.hpp>
#include <common/BSNonTerminal.hpp>
#include <common/flags.h>
#include <fsa/MachineNet.hpp>
#include <fsa/Machine.hpp>
#include <string.h>
#include <ast/AST.hpp>

constexpr char* UNION_FORMAT = " U ";
constexpr char* CONCAT_FORMAT = " . ";

std::set<char>* ruleAlphabet;

int yylex();
void yyerror(char*);

char* punion(char* left, char* right);
char* psubexp(char* subexp);
char* pconcat(char* left, char* right);
char* pstar(char* subexp);
char* pcross(char* subexp);
%}

%code requires{
    #include <ast/AST.hpp>
    struct expression{
	char* pexpr;
	ASTGenericNode* subtree;
	
    };
    struct BSCharacter{
	char grammarChar;
	int rePos;
	};
}

%union{
    struct BSCharacter bsChar;
    struct expression expr;
    char axiom;
}
			

%type	<expr>		expr
%type	<axiom>		rule
%token PRODSIGN
%token SEMICOLON
%token	<bsChar>	EPSILON			
%start grammarAxiom			

%precedence LPAR RPAR
%left			UNION
%left	<bsChar>	TERMINAL
%left	<bsChar>	NONTERMINAL			
%left			CONCAT
%left			STAR CROSS
%precedence             NEST

						
%%

grammarAxiom : rule {MachineNet* net{MachineNet::getInstance()};
		     net->setAxiom($1);}
		grammar {MachineNet::getInstance()->syncAlphabets();};
		
grammar : grammar SEMICOLON rule {}
	|	rule
;

rule : NONTERMINAL {std::string machineName{std::string(1, $1.grammarChar)};
                    MachineNet::getInstance()->addMachine(machineName);
                    $<axiom>$ = $1.grammarChar;
		    ruleAlphabet = new std::set<char>();}

PRODSIGN expr {
               if(debugFlag){
                	printf("Rule for %c: %s\n", $1, $4.pexpr);
	       }
               ASTLeafTerminal* terminalNode = new ASTLeafTerminal('$', 0);
               ASTGenericNode* terminatedRoot = new ASTConcatOperator($4.subtree, terminalNode);
	       ruleAlphabet->emplace('$');
               (*MachineNet::getInstance())[std::string(1,$1.grammarChar)]->addTree(terminatedRoot);
	       (*MachineNet::getInstance())[std::string(1,$1.grammarChar)]->addAlphabet(ruleAlphabet);
	       if(debugFlag){
		   std::cout << '\n';
		   std::cout << "Print tree:\n";
		   (*MachineNet::getInstance())[std::string(1,$1.grammarChar)]->getTree()->print();
	       }	       
	       if(debugFlag)
		std::cout << '\n';
               }
	|	/*empty*/
;

expr : TERMINAL {$$.pexpr = (char*) malloc(sizeof(char) * 2);
                 $$.pexpr[0] = $1.grammarChar;
                 $$.pexpr[1] = '\0';
                 ruleAlphabet->emplace($1.grammarChar);


                 // create leaf node
                 $$.subtree = new ASTLeafTerminal($1.grammarChar, $1.rePos);
                 }

	|	NONTERMINAL {
                 $$.pexpr = (char*) malloc(sizeof(char) * 2);
                 $$.pexpr[0] = $1.grammarChar;
                 $$.pexpr[1] = '\0';
                 ruleAlphabet->emplace($1.grammarChar);


                 // create leaf node
                 $$.subtree = new ASTLeafNonTerminal($1.grammarChar, $1.rePos);
                 }
|	EPSILON {$$.pexpr = (char*) malloc(sizeof(char) * 2);
                 $$.pexpr[0] = $1.grammarChar;
		 $$.pexpr[1] = '\0';

		 //create leaf node
		 $$.subtree = new ASTLeafEpsilon($1.rePos);
		 }
    

| 	expr UNION expr {$$.pexpr = punion($1.pexpr, $3.pexpr);
                         //create union node
                         $$.subtree = new ASTUnionOperator($1.subtree, $3.subtree);
                         }

|	expr CONCAT expr {$$.pexpr = pconcat($1.pexpr, $3.pexpr);
                          //create concat node
                          $$.subtree = new ASTConcatOperator($1.subtree, $3.subtree);
                          }
|	expr STAR {$$.pexpr = pstar($1.pexpr);
                   //create star node
                   $$.subtree = new ASTStarOperator($1.subtree);
                   }
|	expr CROSS {$$.pexpr = pcross($1.pexpr);
                    //create cross node
                    $$.subtree = new ASTCrossOperator($1.subtree);
                    }
|	expr expr %prec CONCAT {$$.pexpr = pconcat($1.pexpr, $2.pexpr);
                                //create concat node
                                $$.subtree = new ASTConcatOperator($1.subtree, $2.subtree);
                                }
|	LPAR expr RPAR %prec NEST {$$.pexpr = $2.pexpr;
                                   //link the subtree
                                   $$.subtree = $2.subtree;
                                   }
;

%%

void yyerror(char * msg){
    printf("%s\n", msg);
    return;
    }

 char* punion(char* left, char* right){
     int newSize = strlen(left) + strlen(right) + strlen(UNION_FORMAT) + 3; //counting terminator, ( and )
     char * res = (char*) malloc(sizeof(char) * newSize);
     sprintf(res, "(%s%s%s)", left, UNION_FORMAT, right);
     return res;
     }
 
 char* pconcat(char* left, char* right){
     int newSize = strlen(left) + strlen(right) + strlen(CONCAT_FORMAT) + 3; //counting terminator, ( and )
     char * res = (char*) malloc(sizeof(char) * newSize);
     sprintf(res, "(%s%s%s)", left, CONCAT_FORMAT, right);
     return res;
     }
 
 char* pstar(char* subexp){
     int newSize = strlen(subexp) + 4; //counting terminator, *, ( and )
     char * res = (char*) malloc(sizeof(char) * newSize);
     sprintf(res, "(%s*)", subexp);
     return res;
     }
 
 char* pcross(char* subexp){
     int newSize = strlen(subexp) + 4; //counting terminator, +, ( and )
     char * res = (char*) malloc(sizeof(char) * newSize);
     sprintf(res, "(%s+)", subexp);
     return res;
     }

char* psubexp(char* subexp){
    int newSize = strlen(subexp) + 3; //counting terminator, ( and )
    char * res = (char*) malloc(sizeof(char) * newSize);
    sprintf(res, "(%s)", subexp);
    return res;
    }
