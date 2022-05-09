#include <bits/stdc++.h>
#include <vector>
#include "TokenRep.h"
#include "token.h"

// Constructor
TokenRep::TokenRep(){
    this->tokens = {};
}

// Get the list of tokens
vector<token> TokenRep::getListTokens(){
    return this->tokens;
}

// Add token into list
void TokenRep::addToken(token t){
    this->tokens.push_back(t);
}

// Print all tokens
void TokenRep::printTokens(){
    for(auto t : this->tokens){
        cout << t.lexeme << " " << t.type << endl;
    }
}