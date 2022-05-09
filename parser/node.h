#include <string>
#include <bits/stdc++.h>
#include "token.h"

using namespace std;

// Structure to store AST Nodes
typedef struct node {
    int type;
    string lexeme;
    struct node *left, *right;
}*ast_node;

// Post order traversal of the AST
void postOrder(ast_node root){
    if(root){
        postOrder(root->left);
        postOrder(root->right);
        cout<< "lexeme: "<<root->lexeme << ", type: "<< root->type << endl;
    }
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
    
    // stack to hold tokens
    stack<ast_node> stN;
    stack<token> stT;
    ast_node t, t1, t2;

    // priority of operators
    int p[123] = {0};
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