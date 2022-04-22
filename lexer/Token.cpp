#include <bits/stdc++.h>
#include <algorithm>
#include <string.h>

#include "Token.h"
#include "Keywords.h"
#include "Operators.h"
#include "Helpers.h"

// Constructor
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

// Scanning for Identifier
void Token::scanIdentifier(){
    string s = "";
    if(Helpers::isBeginningOfIdentifier(this->ch)){
        while(Helpers::isBeginningOfIdentifier(this->ch) || Helpers::isNum(this->ch)){
            s += this->ch;
            this->ch = fgetc(this->fd);
        }

        if(this->kw.isKeyword(s)){
            cout<<"Keyword: "<<s<<"\n";
            return;
        }

        else{
            cout<<"Identifier: "<<s<<"\n";
        }
    }
}


// Scanning for Macro
void Token::scanMacro(){
    string s = "";
    if(Helpers::isMacro(this->ch)){
        while(this->ch != '\n' && !Helpers::isEndFile(this->ch)){
            s += this->ch;
            this->ch = fgetc(this->fd);
        }

        cout<<"Macro: "<<s<<"\n";
    }
}

// Scanning for String Literal
void Token::scanString(){
    string s = "";
    if(Helpers::isBeginningOfString(this->ch)){
        this->ch = fgetc(this->fd);
        while(this->ch != '\n' && !Helpers::isEndFile(this->ch)){
            s += this->ch;
            this->ch = fgetc(this->fd);
        }

        cout<<"String: "<<s<<"\n";
    }
}

// Scanning for Slash(/)
void Token::scanSlash(){
    if(Helpers::isSlash(this->ch)){
        this->ch = fgetc(this->fd);

        // Single Line Comments
        if(Helpers::isSlash(this->ch)){
            string s = "";
            while(this->ch != '\n' && !Helpers::isEndFile(this->ch)){
                s += this->ch;
                this->ch = fgetc(this->fd);
            }

            cout<<"Comment: "<<s<<"\n";
            return;   
        }

        // Multi Line Comments
        else if(this->ch == '*'){
            string s = "";
            s += this->ch;
            this->ch = fgetc(this->fd);
            
            while(this->ch != '*' && !Helpers::isEndFile(this->ch)){
                s += this->ch;
                this->ch = fgetc(this->fd);
            }

            this->ch = fgetc(this->fd);

            while(this->ch != '/' && !Helpers::isEndFile(this->ch)){
                this->ch = fgetc(this->fd);
            }

            cout<<"Comment: "<<s<<"\n";
            return; 
        }

        // Handle the "/-=" operator
        else if(this->ch == '='){
            cout<<"Operator : /="<<"\n";
            return;
        }

        // Standalong "/" operator
        else{
            cout<<"Operator: /"<<"\n";
            return;
        }
    }
}

// Scanning for Numbers
void Token::scanNum(){
    if(Helpers::isNum(this->ch)){
        string s = "";

        while(Helpers::isNum(this->ch)){
            s += this->ch;
            this->ch = fgetc(this->fd);

            if(Helpers::isBeginningOfIdentifier(this->ch)){
                cout<<"Error: Invalid Number"<<"\n";
                exit(1);
                return;
            }
        }

        cout<<"Number: "<<s<<"\n";
    }
}

// Scanning for Parentheses
void Token::scanBracket(){
    if(Helpers::isBracket(this->ch)){
        cout<<"Brackets: "<<this->ch<<"\n";
    }
}

// Scanning for Delimiter
void Token::scanDelimiter(){
    if(Helpers::isSemiColon(this->ch)){
        cout<<"Delimiter: "<<this->ch<<"\n";
    }
}

// Scanning for Operators
void Token::scanOperators(){
    if(this->ch == '+'){
        this->ch = fgetc(this->fd);

        // "++" Operator
        if(this->ch == '+'){
            cout<<"Operator: ++"<<"\n";
            return;
        }

        // "+= Operator"
        else if(this->ch == '='){
            cout<<"Operator: +="<<"\n";
            return;
        }

        // Standalone "+" Operator
        else{
            cout<<"Operator: +"<<"\n";
            fseek(this->fd, -1, SEEK_CUR);
            return;
        }
    }

    if(this->ch == '-'){
        this->ch = fgetc(this->fd);

        // "--" Operator
        if(this->ch == '-'){
            cout<<"Operator: --"<<"\n";
            return;
        }

        // "-= Operator"
        else if(this->ch == '='){
            cout<<"Operator: -="<<"\n";
            return;
        }

        // Standalone "-" Operator
        else{
            cout<<"Operator: -"<<"\n";
            fseek(this->fd, -1, SEEK_CUR);
            return;
        }
    }

    if(this->ch == '*'){
        this->ch = fgetc(this->fd);

        // "*=" Operator
        if(this->ch == '='){
            cout<<"Opeator: *="<<"\n";
            return;
        }

        // Standalone "*" Operator
        else{
            cout<<"Operator: *"<<"\n";
            fseek(this->fd, -1, SEEK_CUR);
            return;
        }
    }

    if(this->ch == '='){
        this->ch = fgetc(this->fd);

        // "==" Operator
        if(this->ch == '='){
            cout<<"Opeator: =="<<"\n";
            return;
        }

        // Standalone "=" Operator
        else{
            cout<<"Operator: ="<<"\n";
            fseek(this->fd, -1, SEEK_CUR);
            return;
        }
    }

    if(this->ch == '^'){
        this->ch = fgetc(this->fd);

        // "^=" Operator
        if(this->ch == '='){
            cout<<"Opeator: ^="<<"\n";
            return;
        }

        // Standalone "^" Operator
        else{
            cout<<"Operator: ^"<<"\n";
            fseek(this->fd, -1, SEEK_CUR);
            return;
        }
    }

    if(this->ch == '%'){
        this->ch = fgetc(this->fd);

        // "%=" Operator
        if(this->ch == '='){
            cout<<"Opeator: %="<<"\n";
            return;
        }

        // Standalone "%" Operator
        else{
            cout<<"Operator: %"<<"\n";
            fseek(this->fd, -1, SEEK_CUR);
            return;
        }
    }

    if(this->ch == '&'){
        this->ch = fgetc(this->fd);

        // "&&" Operator
        if(this->ch == '&'){
            cout<<"Operator: &&"<<"\n";
            return;
        }

        // "&=" Operator
        else if(this->ch == '='){
            cout<<"Opeator: &="<<"\n";
            return;
        }

        // Standalone "&" Operator
        else{
            cout<<"Operator: &"<<"\n";
            fseek(this->fd, -1, SEEK_CUR);
            return;
        }
    }

    if(this->ch == '|'){
        this->ch = fgetc(this->fd);

        // "||" Operator
        if(this->ch == '|'){
            cout<<"Operator: ||"<<"\n";
            return;
        }

        // "|=" Operator
        else if(this->ch == '='){
            cout<<"Opeator: |="<<"\n";
            return;
        }

        // Standalone "|" Operator
        else{
            cout<<"Operator: |"<<"\n";
            fseek(this->fd, -1, SEEK_CUR);
            return;
        }
    }

    if(this->ch == '>'){
        this->ch = fgetc(this->fd);

        // ">>" Operator
        if(this->ch == '>'){
            cout<<"Operator: >>"<<"\n";
            return;
        }

        // ">=" Operator
        else if(this->ch == '='){
            cout<<"Opeator: >="<<"\n";
            return;
        }

        // Standalone ">" Operator
        else{
            cout<<"Operator: >"<<"\n";
            fseek(this->fd, -1, SEEK_CUR);
            return;
        }
    }

    if(this->ch == '<'){
        this->ch = fgetc(this->fd);

        // "<<" Operator
        if(this->ch == '<'){
            cout<<"Operator: <<"<<"\n";
            return;
        }

        // "<=" Operator
        else if(this->ch == '='){
            cout<<"Opeator: <="<<"\n";
            return;
        }

        // Standalone "<" Operator
        else{
            cout<<"Operator: <"<<"\n";
            fseek(this->fd, -1, SEEK_CUR);
            return;
        }
    }

    if(this->ch == '!'){
        this->ch = fgetc(this->fd);

        // "!=" Operator
        if(this->ch == '='){
            cout<<"Opeator: !="<<"\n";
            return;
        }

        // Standalone "!" Operator
        else{
            cout<<"Operator: !"<<"\n";
            fseek(this->fd, -1, SEEK_CUR);
            return;
        }
    }

    if(this->ch == '~'){
        this->ch = fgetc(this->fd);

        // "~=" Operator
        if(this->ch == '='){
            cout<<"Opeator: ~="<<"\n";
            return;
        }

        // Standalone "~" Operator
        else{
            cout<<"Operator: ~"<<"\n";
            fseek(this->fd, -1, SEEK_CUR);
            return;
        }
    }
}



// Main Lexer Function 
void Token::LexicalAnalysis(){
    this->ch = fgetc(this->fd);

    while(!Helpers::isEndFile(this->ch)){

        // Perform Matching Algorithms
        this->scanIdentifier();
        this->scanMacro();
        this->scanString();
        this->scanSlash();
        this->scanNum();
        this->scanOperators();
        this->scanBracket();
        this->scanDelimiter();

        // Update Pointer
        this->ch = fgetc(this->fd);
    }

    fclose(this->fd);
}