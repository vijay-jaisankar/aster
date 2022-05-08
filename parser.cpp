#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<map>
#include<set>
#include<queue>
#include<list>
#include<deque>
#include<stack>
#include<bitset>
#include<vector>
#include<utility>
#include<sstream>
#include<iterator>
#include<functional>
#include<numeric>
#include<iomanip>
#include<ctime>
#include<climits>
#include<cctype>
#include<cassert>
#include<complex>
#include "prettyprint.hpp"
#include<stdlib.h>
#include<fstream>
// #include"parser.h"
using namespace std;
typedef long long ll;
typedef vector <int> vi;
typedef vector <vi> vvi;
typedef vector <string> vs;
typedef pair< int ,int > pii;
typedef pair< ll , ll > pll;
typedef vector <ll> vll;
typedef istringstream iss;
typedef ostringstream oss;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define sz size()
#define ln length()
#define rep(i,n) for(int i=0;i<n;i++)
#define rep1(i,n) for(int i=1;i<=n;i++)
#define ESP (1e-9)
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define __ freopen("input.txt","r",stdin);freopen("output.txt","w",stdout);
//operator overloading for printing pair
template<typename S, typename T> 
ostream& operator<<(ostream& out,pair<S,T> const& p){out<<'('<<p.fi<<", "<<p.se<<')';return out;}
//operator overloading for printing vector.
template<typename T>
ostream& operator<<(ostream& out,vector<T> const& v){
int l=v.size();for(int i=0;i<l-1;i++)out<<v[i]<<' ';if(l>0)out<<v[l-1];return out;}
const ll mod=1e9+7;

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

typedef struct {
    int type;
    string lexeme;
} token;

vector<token> tokens;


// define struct for ast node
typedef struct node {
    int type;
    string lexeme;
    struct node *left, *right;
} * ast_node;

void postorder(ast_node root)
{
    if (root)
    {
        postorder(root->left);
        postorder(root->right);
        cout<< "lexeme: "<<root->lexeme << ", type: "<< root->type << endl;
    }
}

ast_node newNode(int type, string lexeme)
{
    ast_node n = new node;
    n->type = type;
    n->lexeme = lexeme;
    n->left = n->right = nullptr;
    return n;
}

 
ast_node create_ast(vector<token> tokens)
{
    stack<ast_node> stN;

    // stack to hold tokens
    stack<token> stT;
    ast_node t, t1, t2;

    // priority of operators
    int p[123] = {0};
    p[ADDITION] = p[SUBTRACTION] = 1, p[DIVISION] = p[MULTIPLICATION] = 2, p[BITWISE_XOR] = 3,
    p[RIGHT_PARENTHESIS] = p[LEFT_PARENTHESIS] = 0;

    for(int i=0;i<tokens.size();i++)
    {
        if(tokens[i].type == LEFT_PARENTHESIS ) 
        {
            stT.push(tokens[i]);
        }
        else if(tokens[i].type == ID || tokens[i].type == NUM ) 
        {
            t = newNode(tokens[i].type, tokens[i].lexeme);
            stN.push(t);
        }
        else if(p[ tokens[i].type ] > 0){

            while(
                !stT.empty() && stT.top().type != LEFT_PARENTHESIS
                && ((tokens[i].type != BITWISE_XOR && p[stT.top().type] >= p[tokens[i].type])
                || ( tokens[i].type == BITWISE_XOR && p[stT.top().type] > p[tokens[i].type])))
            {
                
                t = newNode(stT.top().type, stT.top().lexeme);
                stT.pop();
                
                cout<<"stT top1: "<<stT.top().lexeme<<endl;

                t1 = stN.top();
                stN.pop();

                cout<<"stN top1: "<<stN.top()->lexeme<<endl;

                t2 = stN.top();
                stN.pop();

                cout<<"stN top2: "<<stN.top()->lexeme<<endl;

                t->right = t1;
                t->left = t2;

                stN.push(t);
            }
            stT.push(tokens[i]);    
        }
        else if( tokens[i].type == RIGHT_PARENTHESIS )
        {
            while(stT.top().type != LEFT_PARENTHESIS && !stT.empty())
            {
                t = newNode(stT.top().type, stT.top().lexeme);
                stT.pop();

                // cout<<"stT top2: "<<stT.top().lexeme<<endl;

                t1 = stN.top();
                stN.pop();

                // cout<<"stN top3: "<<stN.top()->lexeme<<endl;

                t2 = stN.top();
                stN.pop();

                // cout<<"stN top4: "<<stN.top()->lexeme<<endl;

                t->right = t1;
                t->left = t2;
                stN.push(t);
            }
            stT.pop();

            // cout<<"stT top3: "<<stT.top().lexeme<<endl;
        }
    } 
    t = stN.top();
    return t;
}



int main(void){
    // take the tokens from the file output.txt and store it in the vector
    FILE *fp = fopen("output.txt", "r");
    //read line by line
    char line[100];
    while(fgets(line, 100, fp)){
        // split the line by space
        char *t = strtok(line, " ");
        token tk;
        // store first part of the line in tk.lexeme and the second part in tk.type
        tk.lexeme = t;
        t = strtok(NULL, " ");
        tk.type = atoi(t);
        // store the token in the vector
        tokens.pb(tk);
    }
    fclose(fp);

    // print tokens array
    rep(i, tokens.size()){
        cout << tokens[i].lexeme << " " << tokens[i].type << endl;
    }

    // create the ast
    ast_node root = create_ast(tokens);

    // print the ast
    postorder(root);


}