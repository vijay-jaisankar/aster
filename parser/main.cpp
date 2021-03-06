#include <bits/stdc++.h>
#include <vector>
#include <string>

#include "node.h"
#include "token.h"
#include "Listtok.h"




// Read list of tokens
const char* fileName = "output.txt";

int main(int argc, char const *argv[]){


    // List of tokens
    Listtok* tokensObj = new Listtok();

    FILE *fp = fopen(fileName, "r");

    // Read the file line-by-line
    char line[100];

    while(fgets(line, 100, fp)){

        // Split the line by space
        char *t = strtok(line, " ");

        // Create new token
        token tok;
        tok.lexeme = t;
        t = strtok(NULL, " ");
        tok.type = atoi(t);

        // Add the token to the list of vectors
        tokensObj->addToken(tok);
    }

    // Close the file
    fclose(fp);

    // Print all tokens
    tokensObj->printTokens();

    // Create AST
    vector<token> t = tokensObj->getListTokens();
    ast_node root = createAST(t);

    // Print the AST in post-order fashion
    postOrder(root);

    // Pretty print the ast
    printBT(root);

    return 0;
}
