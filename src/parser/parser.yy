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
#include <common/Types.hpp>
#include <fsa/MachineNet.hpp>
#include <string.h>
#include <ast/AST.hpp>

constexpr char* UNION_FORMAT = " U ";
constexpr char* CONCAT_FORMAT = " . ";

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
}
%union{
    char term;
    char nterm;
    struct expression expr;
}
			
%precedence	<term>		TERMINAL
%token	<nterm>		NONTERMINAL
%type	<expr>		expr
%token PRODSIGN
%start grammar			

%precedence LPAR RPAR
%left			UNION
%left			CONCAT
%left			STAR CROSS
%precedence             NEST
			
%%

grammar : grammar rule {}
	|	rule
;

rule : NONTERMINAL {std::string machineName{std::string(1,$1)};
                    MachineNet::getInstance()->addMachine(machineName);}

PRODSIGN expr {printf("Rule for %c: %s\n", $1, $4.pexpr);
               (*MachineNet::getInstance())[std::string(1,$1)]->addTree($4.subtree);
               std::cout << '\n';
               std::cout << "Print tree:\n";
               (*MachineNet::getInstance())[std::string(1,$1)]->getTree()->print();
               std::cout << '\n';
               }
;

expr : TERMINAL {$$.pexpr = (char*) malloc(sizeof(char) * 2);
                 $$.pexpr[0] = $1;
                 $$.pexpr[1] = '\0';

                 // create leaf node
                 $$.subtree = new ASTLeafTerminal($1);
                 }

| 	expr UNION expr {$$.pexpr = punion($1.pexpr, $3.pexpr);
                         //create union node
                         $$.subtree = new ASTBinaryOperator(BinaryOperator::alter, $1.subtree, $3.subtree);
                         }

|	expr CONCAT expr {$$.pexpr = pconcat($1.pexpr, $3.pexpr);
                          //create concat node
                          $$.subtree = new ASTBinaryOperator(BinaryOperator::concat, $1.subtree, $3.subtree);
                          }
|	expr STAR {$$.pexpr = pstar($1.pexpr);
                   //create star node
                   $$.subtree = new ASTUnaryOperator(UnaryOperator::star, $1.subtree);
                   }
|	expr CROSS {$$.pexpr = pcross($1.pexpr);
                    //create cross node
                    $$.subtree = new ASTUnaryOperator(UnaryOperator::cross, $1.subtree);
                    }
|	expr expr %prec CONCAT {$$.pexpr = pconcat($1.pexpr, $2.pexpr);
                                //create concat node
                                $$.subtree = new ASTBinaryOperator(BinaryOperator::concat, $1.subtree, $2.subtree);
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
