#include <bits/stdc++.h>
#include <algorithm>
#include <string.h>

#include "Token.h"
#include "Keywords.h"
#include "Operators.h"
#include "Helpers.h"
#include "Structs.h"
using namespace std;



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

    // struct token tokens;
    this->tokenslist = {};
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
            tokens.type = KW;
            tokens.lexeme = s;
            tokenslist.push_back(tokens);
            return;
        }

        else{
            cout<<"Identifier: "<<s<<"\n";
            tokens.type = ID;
            tokens.lexeme = s;
            tokenslist.push_back(tokens);
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
        tokens.type = HDR;
        tokens.lexeme = s;
        tokenslist.push_back(tokens);
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

        cout<<"String: "<<s <<"\n";
        tokens.type = STR;
        tokens.lexeme = s;
        tokenslist.push_back(tokens);
    }
}

// Scanning for Slash(/)
void Token::scanSlash(){

    if(Helpers::isSlash(this->ch)){ 
        
        this->ch = fgetc(this->fd);
        // Single Line Comments
        if(Helpers::isSlash(this->ch)){
            string s = "";
            s += this->ch;
            while(this->ch != '\n' && !Helpers::isEndFile(this->ch)){
                s += this->ch;
                this->ch = fgetc(this->fd);
            }

            cout<<"Comment: "<<s <<"\n";
            tokens.type = COMM;
            tokens.lexeme = s;
            tokenslist.push_back(tokens);
            return;   
        }
        
        // Multi Line Comments
        else if(this->ch == '*'){
            string s = "/";
            s += this->ch;
            this->ch = fgetc(this->fd);
            
            while(this->ch != '*' && !Helpers::isEndFile(this->ch)){
                s += this->ch;
                this->ch = fgetc(this->fd);
            }
            s += this->ch;
            this->ch = fgetc(this->fd);

            while(this->ch != '/' && !Helpers::isEndFile(this->ch)){
                this->ch = fgetc(this->fd);
            }
            s += this->ch;
            cout<<"Comment: "<<s <<"\n";
            tokens.type = COMM;
            tokens.lexeme = s;
            tokenslist.push_back(tokens);
            return; 
        }

        // Handle the "/=" operator
        else if(this->ch == '='){
            cout<<"Operator : /="<<"\n";
            tokens.type = DIVISION_EQUAL;
            tokens.lexeme = "/=";
            tokenslist.push_back(tokens);
            return;
        }

        // Standalong "/" operator
        else{
            cout<<"Operator: /"<<"\n";
            tokens.type = DIVISION;
            tokens.lexeme = "/";
            tokenslist.push_back(tokens);
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
        tokens.type = NUM;
        tokens.lexeme = s;
        tokenslist.push_back(tokens);
    }
}

// Scanning for Parentheses
void Token::scanBracket(){
    if(Helpers::isBracket(this->ch)){
        cout<<"Brackets: "<<this->ch<<"\n";
        tokens.type = LEFT_PARENTHESIS;
        tokens.lexeme = this->ch;
        tokenslist.push_back(tokens);
    }
}

// Scanning for Delimiter
void Token::scanDelimiter(){
    if(Helpers::isSemiColon(this->ch)){
        cout<<"Delimiter: "<<this->ch<<"\n";
        tokens.type = SEMICOLON;
        tokens.lexeme = this->ch;
        tokenslist.push_back(tokens);
    }
}

// Scanning for Operators
void Token::scanOperators(){
    if(this->ch == '+'){
        this->ch = fgetc(this->fd);

        // "++" Operator
        if(this->ch == '+'){
            cout<<"Operator: ++"<<"\n";
            tokens.type = INCREMENT;
            tokens.lexeme = "++";
            tokenslist.push_back(tokens);
            return;
        }

        // "+= Operator"
        else if(this->ch == '='){
            cout<<"Operator: +="<<"\n";
            tokens.type = ADDITION_EQUAL;
            tokens.lexeme = "+=";
            tokenslist.push_back(tokens);
            return;
        }

        // Standalone "+" Operator
        else{
            cout<<"Operator: +"<<"\n";
            tokens.type = ADDITION;
            tokens.lexeme = "+";
            tokenslist.push_back(tokens);
            fseek(this->fd, -1, SEEK_CUR);
            return;
        }
    }

    if(this->ch == '-'){
        this->ch = fgetc(this->fd);

        // "--" Operator
        if(this->ch == '-'){
            cout<<"Operator: --"<<"\n";
            tokens.type = DECREMENT;
            tokens.lexeme = "--";
            tokenslist.push_back(tokens);
            return;
        }

        // "-= Operator"
        else if(this->ch == '='){
            cout<<"Operator: -="<<"\n";
            tokens.type = SUBTRACTION_EQUAL;
            tokens.lexeme = "-=";
            tokenslist.push_back(tokens);
            return;
        }

        // Standalone "-" Operator
        else{
            cout<<"Operator: -"<<"\n";
            tokens.type = SUBTRACTION;
            tokens.lexeme = "-";
            tokenslist.push_back(tokens);
            fseek(this->fd, -1, SEEK_CUR);
            return;
        }
    }

    if(this->ch == '*'){
        this->ch = fgetc(this->fd);

        // "*=" Operator
        if(this->ch == '='){
            cout<<"Opeator: *="<<"\n";
            tokens.type = MULTIPLICATION_EQUAL;
            tokens.lexeme = "*=";
            tokenslist.push_back(tokens);
            return;
        }

        // Standalone "*" Operator
        else{
            cout<<"Operator: *"<<"\n";
            tokens.type = MULTIPLICATION;
            tokens.lexeme = "*";
            tokenslist.push_back(tokens);
            fseek(this->fd, -1, SEEK_CUR);
            return;
        }
    }

    if(this->ch == '='){
        this->ch = fgetc(this->fd);

        // "==" Operator
        if(this->ch == '='){
            cout<<"Opeator: =="<<"\n";
            tokens.type = EQUAL_TO;
            tokens.lexeme = "==";
            tokenslist.push_back(tokens);
            return;
        }

        // Standalone "=" Operator
        else{
            cout<<"Operator: ="<<"\n";
            tokens.type = EQUAL;
            tokens.lexeme = "=";
            tokenslist.push_back(tokens);
            fseek(this->fd, -1, SEEK_CUR);
            return;
        }
    }

    if(this->ch == '^'){
        this->ch = fgetc(this->fd);

        // "^=" Operator
        if(this->ch == '='){
            cout<<"Opeator: ^="<<"\n";
            tokens.type = BITWISE_XOR_EQUAL;
            tokens.lexeme = "^=";
            tokenslist.push_back(tokens);
            return;
        }

        // Standalone "^" Operator
        else{
            cout<<"Operator: ^"<<"\n";
            tokens.type = BITWISE_XOR;
            tokens.lexeme = "^";
            tokenslist.push_back(tokens);
            fseek(this->fd, -1, SEEK_CUR);
            return;
        }
    }

    if(this->ch == '%'){
        this->ch = fgetc(this->fd);

        // "%=" Operator
        if(this->ch == '='){
            cout<<"Opeator: %="<<"\n";
            tokens.type = MODULO_EQUAL;
            tokens.lexeme = "%=";
            tokenslist.push_back(tokens);
            return;
        }

        // Standalone "%" Operator
        else{
            cout<<"Operator: %"<<"\n";
            tokens.type = MODULO;
            tokens.lexeme = "%";
            tokenslist.push_back(tokens);
            fseek(this->fd, -1, SEEK_CUR);
            return;
        }
    }

    if(this->ch == '&'){
        this->ch = fgetc(this->fd);

        // "&&" Operator
        if(this->ch == '&'){
            cout<<"Operator: &&"<<"\n";
            tokens.type = AND;
            tokens.lexeme = "&&";
            tokenslist.push_back(tokens);
            return;
        }

        // "&=" Operator
        else if(this->ch == '='){
            cout<<"Opeator: &="<<"\n";
            tokens.type = BITWISE_AND_EQUAL;
            tokens.lexeme = "&=";
            tokenslist.push_back(tokens);
            return;
        }

        // Standalone "&" Operator
        else{
            cout<<"Operator: &"<<"\n";
            tokens.type = BITWISE_AND;
            tokens.lexeme = "&";
            tokenslist.push_back(tokens);
            fseek(this->fd, -1, SEEK_CUR);
            return;
        }
    }

    if(this->ch == '|'){
        this->ch = fgetc(this->fd);

        // "||" Operator
        if(this->ch == '|'){
            cout<<"Operator: ||"<<"\n";
            tokens.type = OR;
            tokens.lexeme = "||";
            tokenslist.push_back(tokens);
            return;
        }

        // "|=" Operator
        else if(this->ch == '='){
            cout<<"Opeator: |="<<"\n";
            tokens.type = BITWISE_OR_EQUAL;
            tokens.lexeme = "|=";
            tokenslist.push_back(tokens);
            return;
        }

        // Standalone "|" Operator
        else{
            cout<<"Operator: |"<<"\n";
            tokens.type = BITWISE_OR;
            tokens.lexeme = "|";
            tokenslist.push_back(tokens);
            fseek(this->fd, -1, SEEK_CUR);
            return;
        }
    }

    if(this->ch == '>'){
        this->ch = fgetc(this->fd);

        // ">>" Operator
        if(this->ch == '>'){
            cout<<"Operator: >>"<<"\n";
            tokens.type = RIGHT_SHIFT;
            tokens.lexeme = ">>";
            tokenslist.push_back(tokens);
            return;
        }

        // ">=" Operator
        else if(this->ch == '='){
            cout<<"Opeator: >="<<"\n";
            tokens.type = GREATER_THAN_OR_EQUAL;
            tokens.lexeme = ">=";
            tokenslist.push_back(tokens);
            return;
        }

        // Standalone ">" Operator
        else{
            cout<<"Operator: >"<<"\n";
            tokens.type = GREATER_THAN;
            tokens.lexeme = ">";
            tokenslist.push_back(tokens);
            fseek(this->fd, -1, SEEK_CUR);
            return;
        }
    }

    if(this->ch == '<'){
        this->ch = fgetc(this->fd);

        // "<<" Operator
        if(this->ch == '<'){
            cout<<"Operator: <<"<<"\n";
            tokens.type = LEFT_SHIFT;
            tokens.lexeme = "<<";
            tokenslist.push_back(tokens);
            return;
        }

        // "<=" Operator
        else if(this->ch == '='){
            cout<<"Opeator: <="<<"\n";
            tokens.type = LESS_THAN_OR_EQUAL;
            tokens.lexeme = "<=";
            tokenslist.push_back(tokens);
            return;
        }

        // Standalone "<" Operator
        else{
            cout<<"Operator: <"<<"\n";
            tokens.type = LESS_THAN;
            tokens.lexeme = "<";
            tokenslist.push_back(tokens);
            fseek(this->fd, -1, SEEK_CUR);
            return;
        }
    }

    if(this->ch == '!'){
        this->ch = fgetc(this->fd);

        // "!=" Operator
        if(this->ch == '='){
            cout<<"Opeator: !="<<"\n";
            tokens.type = NOT_EQUAL;
            tokens.lexeme = "!=";
            tokenslist.push_back(tokens);
            return;
        }

        // Standalone "!" Operator
        else{
            cout<<"Operator: !"<<"\n";
            tokens.type = NOT;
            tokens.lexeme = "!";
            tokenslist.push_back(tokens);
            fseek(this->fd, -1, SEEK_CUR);
            return;
        }
    }

    if(this->ch == '~'){
        this->ch = fgetc(this->fd);

        // "~=" Operator
        if(this->ch == '='){
            cout<<"Opeator: ~="<<"\n";
            tokens.type = BITWISE_NOT_EQUAL;
            tokens.lexeme = "~=";
            tokenslist.push_back(tokens);
            return;
        }

        // Standalone "~" Operator
        else{
            cout<<"Operator: ~"<<"\n";
            tokens.type = BITWISE_NOT;
            tokens.lexeme = "~";
            tokenslist.push_back(tokens);
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

void Token::printTokensList(){
    for(auto x: this->tokenslist){
        cout<<x.lexeme<<" "<<x.type<<endl;
    }
}

vector<token> Token::getTokensList(){
    return this->tokenslist;
}
