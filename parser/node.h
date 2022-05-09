#ifndef NODE_H
#define NODE_H

#include <string>
#include <bits/stdc++.h>
#include "token.h"

using namespace std;

enum {
    KW=1, ID, STR, NUM, HDR, COMM,
    
    NOT=10, BITWISE_AND, BITWISE_NOT, BITWISE_XOR, MULTIPLICATION, DIVISION, MODULO, ADDITION, SUBTRACTION, 
    LESS_THAN, GREATER_THAN, EQUAL, BITWISE_OR, QUESTION, COLON, SEMICOLON, COMMA, DOT, 
    LEFT_SQUARE_BRACKET, RIGHT_SQUARE_BRACKET, LEFT_PARENTHESIS, RIGHT_PARENTHESIS,
    LEFT_CURLY_BRACKET, RIGHT_CURLY_BRACKET, POINTER, INCREMENT, DECREMENT,
    LEFT_SHIFT, RIGHT_SHIFT, LESS_THAN_OR_EQUAL, GREATER_THAN_OR_EQUAL,
    EQUAL_TO, NOT_EQUAL, AND, OR, ADDITION_EQUAL, SUBTRACTION_EQUAL,
    MULTIPLICATION_EQUAL, DIVISION_EQUAL, MODULO_EQUAL, BITWISE_AND_EQUAL,
    BITWISE_XOR_EQUAL, BITWISE_OR_EQUAL, BITWISE_NOT_EQUAL, ERROR, END_OF_TEXT
};


// Structure to store AST Nodes
typedef struct node {
    int type;
    string lexeme;
    struct node *left, *right;
}*ast_node;

// Post order traversal of the AST
void postOrder(ast_node root, int indent =0){
    if(root!=NULL){
        if(root->right){
            postOrder(root->right, indent+4);
        }
        if (indent) {
            cout << setw(indent) << ' ';
        }
        if (root->right) cout<<" /\n" << setw(indent) << ' ';
        cout<< root->lexeme << "\n ";
        if(root->left){
            cout<<setw(indent) << ' ' <<" \\\n";
            postOrder(root->left, indent+4);
        }
    }
}


// preorder
void preOrder(ast_node root, int indent =0){
    if(root!=NULL){
        if (indent) {
            cout << setw(indent) << ' ';
        }
        cout<< root->lexeme << "\n ";
        if(root->left){
            preOrder(root->left, indent+4);
        }
        if(root->right){
            preOrder(root->right, indent+4);
        }
    }
}


// inorder
void inOrder(ast_node root, int indent =0){
    if(root!=NULL){
        if(root->left){
            inOrder(root->left, indent+4);
        }
        if (indent) {
            cout << setw(indent) << ' ';
        }
        cout<< root->lexeme << "\n ";
        if(root->right){
            inOrder(root->right, indent+4);
        }
    }
}



// pretty printing the abstract syntax tree
void printBT(const std::string& prefix, ast_node node, bool isLeft)
{
    if (node != nullptr)
    {
        std::cout << prefix;
        std::cout << (isLeft ? "|--" : "L--");
        // print the value of the node
        std::cout << node->lexeme << std::endl;
        // enter the next tree level - left and right branch
        printBT(prefix + (isLeft ? "|   " : "    "), node->left, true);
        printBT(prefix + (isLeft ? "|   " : "    "), node->right, false);
    }
}

void printBT(ast_node node)
{
    printBT("", node, false);
}




// Create and return new node
ast_node newNode(int type, string lexeme){
    ast_node n = new node;
    n->type = type;
    n->lexeme = lexeme;
    n->left = n->right = nullptr;
    return n;
}

// Create AST
ast_node createAST(vector<token> tokens){
    
    stack<ast_node> stN;
    stack<token> stT;
    ast_node t, t1, t2;

    // priority of operators
    int p[40] = {0};
    p[ADDITION] = p[SUBTRACTION] = 1, p[DIVISION] = p[MULTIPLICATION] = 2, p[BITWISE_XOR] = 3,
    p[RIGHT_PARENTHESIS] = p[LEFT_PARENTHESIS] = 0;

    for(int i=0;i<tokens.size();i++){
        
        // Left Bracket
        if(tokens[i].type == LEFT_PARENTHESIS){
            stT.push(tokens[i]);
        }

        // Number or Identifier
        else if(tokens[i].type == ID || tokens[i].type == NUM ){
            t = newNode(tokens[i].type, tokens[i].lexeme);
            stN.push(t);
        }
        
        
        else if(p[tokens[i].type] > 0){
            while(
                !stT.empty() && stT.top().type != LEFT_PARENTHESIS
                && ((tokens[i].type != BITWISE_XOR && p[stT.top().type] >= p[tokens[i].type])
                || ( tokens[i].type == BITWISE_XOR && p[stT.top().type] > p[tokens[i].type]))){
                
                t = newNode(stT.top().type, stT.top().lexeme);
                stT.pop();
                
                t1 = stN.top();
                stN.pop();

                t2 = stN.top();
                stN.pop();

                t->left = t2;
                t->right = t1;
                stN.push(t);
            }

            stT.push(tokens[i]);    
        }

        // Right Bracket
        else if( tokens[i].type == RIGHT_PARENTHESIS ){
            while(stT.top().type != LEFT_PARENTHESIS && !stT.empty()){
                t = newNode(stT.top().type, stT.top().lexeme);
                stT.pop();

                t1 = stN.top();
                stN.pop();

                t2 = stN.top();
                stN.pop();

                t->left = t2;
                t->right = t1;
                stN.push(t);
            }

            stT.pop();
        }
    } 
    
    t = stN.top();
    return t;
}




#endif