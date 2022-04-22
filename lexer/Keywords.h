#include <bits/stdc++.h>
#include <string.h>
#include <vector>
using namespace std;

#ifndef KEYWORDS_H
#define KEYWORDS_H

class Keywords{

    private:
        vector<string> listKeywords;

    public:
        Keywords();
        vector<string> getListKeywords();
        bool isKeyword(string);
};



#endif