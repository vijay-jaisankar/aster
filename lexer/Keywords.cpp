#include <bits/stdc++.h>
#include <string>
#include <algorithm>
#include "Keywords.h"
using namespace std;

Operators::Operators(){
    this->listKeywords = {"auto", "break", "case", "char", "const", "continue", 
    "default", "do", "double", "else", "enum", "extern", 
    "float", "for", "goto", "if", "int", "long", "register", "return", 
    "short", "signed", "sizeof", "static", "struct", "switch", 
    "typedef", "union", "unsigned", "void", "volatile", "while"};
}

vector<string> Operators::getListKeywords(){
    return this->listKeywords;
}

bool Operators::isKeyword(string word){
    return (find(this->listKeywords.begin(), this->listKeywords.end(), word) != this->listKeywords.end());
}
