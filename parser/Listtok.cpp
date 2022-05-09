#include <bits/stdc++.h>
#include <vector>
#include "Listtok.h"
#include "token.h"

// Constructor
Listtok::Listtok(){
    this->tokens = {};
}

// Get the list of tokens
vector<token> Listtok::getListTokens(){
    return this->tokens;
}

// Add token into list
void Listtok::addToken(token t){
    this->tokens.push_back(t);
}

// Print all tokens
void Listtok::printTokens(){
    for(auto t : this->tokens){
        cout << t.lexeme << " " << t.type << endl;
    }
}