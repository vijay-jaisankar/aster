#include <bits/stdc++.h>
#include <string.h>
#include "Operators.h"
#include "Keywords.h"
using namespace std;


#ifndef TOKEN_H
#define TOKEN_H

class Token{
    private:
        FILE* fd;
        string filePath;
        char ch;
        Operators op;
        Keywords kw;
    public:
        Token(string);
        void LexicalAnalysis();

        void scanIdentifier();
        void scanMacro();
        void scanString();
        void scanSlash();
        void scanNum();
        void scanPlus();
        void scanMinus();
        void scanMultiply();
        void scanBracket();
        void scanEquals();
        void scanSemicolon();
};



#endif