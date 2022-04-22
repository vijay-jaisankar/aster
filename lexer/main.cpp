#include <bits/stdc++.h>
#include <string.h>
#include <vector>

#include "Helpers.h"
#include "Keywords.h"
#include "Operators.h"
#include "Token.h"

int main(int argc, char const *argv[]){
    
    if(argc < 2){
        cout<<"Invalid Operation."<<"\n";
        exit(1);
        return 1;
    }

    // Initialising Token Object
    string input(argv[1]);
    Token* t = new Token(input);

    // Performing Lexical Analysis
    t->LexicalAnalysis();

    // Printing out the tokens
    // cout<<"Tokens List: "<<"\n"; 
    // t->printTokensList();

    return 0;
}
