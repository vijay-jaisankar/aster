#include <bits/stdc++.h>
#include <algorithm>
#include <string.h>

#include "Token.h"
#include "Keywords.h"
#include "Operators.h"
#include "Helpers.h"

Token::Token(string filePath){
    this->filePath.assign(filePath);

    this->fd = fopen(this->filePath.c_str(), "r");
    if(this->fd == NULL){
        cout<<"File Error"<<"\n";
        exit(1);
    }

    this->kw = Keywords();
    this->op = Operators();
}
