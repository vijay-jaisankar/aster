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


    // write the output into file
    ofstream outfile;
    outfile.open("output.txt");
    for(auto x: t->getTokensList()){
        outfile<<x.lexeme<<" "<<x.type<<endl;
    }
    outfile.close();

    return 0;
}
