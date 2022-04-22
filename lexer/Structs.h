#include <bits/stdc++.h>
#include <string>
using namespace std;

#ifndef STRUCTS_H
#define STRUCTS_H

// Encoding for Token Types
#define Kw 1
#define Op 2
#define Id 3
#define Str 4
#define Num 5
#define Spc 6
#define Hdr 7
#define Comm 8


// Token Properties
struct token{
    int type;
    string lexeme;
};


#endif