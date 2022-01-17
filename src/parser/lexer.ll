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
#include <parser.hpp>
int reCurrentPos = 0;
%}

PRODSIGN                    ":"|"::="|"=>"
			
%option noyywrap
%option header-file="lexer.hpp"

%x COMMENT			
			
%%
<INITIAL>[a-z]                       {yylval.bsChar.grammarChar = yytext[0];
                             yylval.bsChar.rePos = reCurrentPos;
                             reCurrentPos++; return TERMINAL;}

<INITIAL>[A-Z]                       {yylval.bsChar.grammarChar = yytext[0];
                                      yylval.bsChar.rePos = reCurrentPos;
                             reCurrentPos++; return NONTERMINAL;}

<INITIAL>"&"                         {yylval.bsChar.grammarChar = ' ';
                                      yylval.bsChar.rePos = reCurrentPos;
                                      reCurrentPos++; return EPSILON;}

<INITIAL>{PRODSIGN}                  {reCurrentPos = 1; return PRODSIGN;}
<INITIAL>"|"                         {return UNION;}
<INITIAL>"*"                         {return STAR;}
<INITIAL>"+"                         {return CROSS;}
<INITIAL>"."                         {return CONCAT;}
<INITIAL>"("                         {return LPAR;}
<INITIAL>")"                         {return RPAR;}
<INITIAL>";"                         {return SEMICOLON;}
<INITIAL>[ \n\t\r]                   { /*do nothing*/ }
<INITIAL>.                           { /*do nothing*/ }

<INITIAL>"//"                        { BEGIN(COMMENT); }
<COMMENT>.                           { /*do nothing*/ }
<COMMENT>[\n\r]                      { BEGIN(INITIAL); }

%%
