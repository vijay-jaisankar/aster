%{
	
	
%}

%union {
	int num;
	char sym;
}

%token EOL 
%token<num> NUMBER
%type<num> exp
%token PLUS

%%

input: 
	exp EOL {printf("%d \n", $1);} 
|	 EOL
;

exp:
	NUMBER {$$ = $1;}
| 	exp PLUS NUMBER {$$ = $1 + $3;}
;

%%


int main(){
	yyparse();
	return 0;
}

yyerror(char* s){
	printf("ERROR %s", s);
	return 0;
}
