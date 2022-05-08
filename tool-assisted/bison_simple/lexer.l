%{
	#include "parser.tab.h"
%}



%%

[0-9]+ { yyval.atoi(yytext); return NUMBER;}
\n {return EOL;}
. {}


%%


yywrap() {}
