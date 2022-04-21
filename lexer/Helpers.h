#include <bits/stdc++.h>
#include <string.h>


#ifndef HELPERS_H
#define HELPERS_H

class Helpers{
    public:
        Helpers();
        static bool isBeginningOfIdentifier(char);
        static bool isAlpha(char);
        static bool isNum(char);
        static bool isMacro(char);
        static bool isBeginningOfString(char);
        static bool isSlash(char);
        static bool isBracket(char);
        static bool isSemiColon(char);
        static bool isEndFile(char);
};



#endif