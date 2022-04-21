#include <bits/stdc++.h>
#include <string>
#include "Operators.h"
using namespace std;

Operators::Operators(){
    this->listOperators = {"!", "&", "~", "^", "*", "/", "%", "+", "-", "<", ">", "=", 
    "|", "?", ":", ";", ",", ".", "[", "]", "(", ")", "{", "}" 
    "->", "++", "--", "<<", ">>", "<=", ">=", "==", "!=", "&&",
    "||", "+=", "-=", "*=", "/=", "%=", "&=", "^="};
}

vector<string> Operators::getListOperators(){
    return this->listOperators;
}
