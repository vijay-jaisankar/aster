#include <bits/stdc++.h>
#include <string>
#include <algorithm>
#include "Keywords.h"
using namespace std;

Keywords::Keywords(){
    this->listKeywords = {"auto", "break", "case", "char", "const", "continue", 
    "default", "do", "double", "else", "enum", "extern", 
    "float", "for", "goto", "if", "int", "long", "register", "return", 
    "short", "signed", "sizeof", "static", "struct", "switch", 
    "typedef", "union", "unsigned", "void", "volatile", "while"};
}

vector<string> Keywords::getListKeywords(){
    return this->listKeywords;
}

bool Keywords::isKeyword(string word){
    return (find(this->listKeywords.begin(), this->listKeywords.end(), word) != this->listKeywords.end());
}
