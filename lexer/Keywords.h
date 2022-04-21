#include <bits/stdc++.h>
#include <string.h>

#ifndef KEYWORDS_H
#define KEYWORDS_H

class Operators{

    private:
        vector<string> listKeywords;

    public:
        Operators();
        vector<string> getListKeywords();
        bool isKeyword(string);
};



#endif