#include <bits/stdc++.h>
#include <string.h>
using namespace std;


#ifndef TOKEN_H
#define TOKEN_H

class Token{
    private:
        FILE* fd;
        string filePath;
        char ch;
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