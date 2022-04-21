#include <bits/stdc++.h>
#include <string.h>
using namespace std;

#include "Helpers.h"

Helpers::Helpers(){
    cout<<"Helpers Initialised"<<"\n";
}

bool Helpers::isBeginningOfIdentifier(char ch){
    return ((ch>='A' && ch<='Z') || (ch>='a' && ch<='z') || ch=='_');
}

bool Helpers::isAlpha(char ch){
    return ((ch>='A' && ch<='Z') || (ch>='a' && ch<='z'));
}

bool Helpers::isBeginningOfString(char ch){
    return (ch == '"');
}

bool Helpers::isBracket(char ch){
    return (ch == '(' || ch == ')' || ch == '{' || ch == '}');
}

bool Helpers::isMacro(char ch){
    return (ch == '#');
}

bool Helpers::isNum(char ch){
    return (ch>='0' && ch<='9');
}

bool Helpers::isSemiColon(char ch){
    return (ch == ';');
}

bool Helpers::isSlash(char ch){
    return (ch == '/');
}