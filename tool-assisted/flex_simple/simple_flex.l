/*
	Definitions
*/

%{

%}


/*
	Rules
	
	- Priority Order
	- yytext attribute
*/

%%
if {printf("Keyword \n");}
[a-z0-9.]{3,}@[a-z0-9.-]+ {printf("Valid email address \n");}
[6-9][0-9]{9} {printf("Valid phone number \n");}
[a-zA-Z_][a-zA-Z0-9_]* {printf("Valid Identifier \n");}
.+ {printf("Invalid \n");}	
\n {return 0;}
%%

/*
	Wrapper function
*/

yywrap() {}

/*
	Driver function 

	- yylex() performs the rule matching 
*/

int main(){
	printf("Enter string: ");
	yylex();
	return 0; 
}
