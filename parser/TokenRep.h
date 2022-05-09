#include "token.h"
#include <vector>
#include <string>

using namespace std;

class TokenRep {
    private:
        vector<token> tokens;
    
    public:
        TokenRep();
        vector<token> getListTokens();
        void addToken(token);
        void printTokens();
};