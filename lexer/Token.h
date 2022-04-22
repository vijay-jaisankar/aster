#include <bits/stdc++.h>
#include <string.h>
#include "Operators.h"
#include "Keywords.h"
using namespace std;


#ifndef TOKEN_H
#define TOKEN_H

struct token{
    int type;
    string lexeme;
};

class Token{
    private:
        FILE* fd;
        string filePath;
        char ch;
        Operators op;
        Keywords kw;
        vector<token> tokenslist;
        struct token tokens;
    public:
        Token(string);
        void LexicalAnalysis();

        void scanIdentifier();
        void scanMacro();
        void scanString();
        void scanSlash();
        void scanNum();
        void scanBracket();
        void scanOperators();
        void scanDelimiter();
        void getlistoftokens();
};



#endif
