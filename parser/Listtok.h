#ifndef LISTTOK_H
#define LISTTOK_H

#include "token.h"
#include <vector>
#include <string>

using namespace std;

class Listtok {
    private:
        vector<token> tokens;
    
    public:
        Listtok();
        vector<token> getListTokens();
        void addToken(token);
        void printTokens();
};

#endif