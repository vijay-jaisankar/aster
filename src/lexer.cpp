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
#include<stdlib.h>
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
//mod oper.
ll expp(ll x, ll b){
	long long ret = 1;
	while(b > 0){
		if(b%2 == 1) ret = (ret*x)%mod;
		x = (x*x)%mod;
		b /= 2;
	}
	return ret;
}
ll add(ll x, ll y) {
	x += y;
	if (x >= mod) return x%mod;
	return x;
}
ll sub(ll x, ll y) {
	x -= y;
	if (x < 0) return (x + mod)%mod;
	return x;
}
ll mult(ll x, ll y) {
	return (x * y) % mod;
}
ll inv(ll x){
    ll ans= expp(x,mod-2);
    return ans;
}
//fast doubling for finding nth fibonacci number.
pair<ll, ll> fib (ll n) {
    if (n == 0)
        return {0, 1};
    auto p = fib(n >> 1);
    ll c = mult(p.first , (sub(mult(2 , p.second) , p.first*1LL)));
    ll d = add(mult(p.first ,p.first)*1LL , mult(p.second , p.second));
    if (n & 1)
        return {d, add(c,d)};
    else
        return {c, d};
}



int main() {_

    // file handler 
    FILE * fd;
    char path[50];
    char ch;
    char array[100];
    char * word;
    int i = 0;

    printf("Enter the path of the c file to be read: ");
    scanf("%s", path);

    fd = fopen(path, "r");

    // error handling
    if (fd == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    ch = fgetc(fd);
    while(ch!=EOF) {
        i = 0;

        if((ch>='A' && ch<='Z') || (ch>='a' && ch<='z') || ch=='_'){
            while( (ch>='A' && ch<='Z') || (ch>='a' && ch<='z') || (ch>'0' && ch<'9') || ch=='_' ){
                array[i] = ch;
                i++;
                ch = fgetc(fd);
            }
            word = new char[i+1];
            for(int j=0;j<i;j++)  word[j] = array[j];
            word[i] = '\0';
            cout<<"word: "<<word<<endl;
        }

        // macros are handled here
        else if(ch=='#'){
            while(ch!='\n' && ch!=EOF){
                array[i] = ch;
                i++;
                ch = fgetc(fd);
            }
            word = new char[i+1];
            for(int j=0;j<i;j++)  word[j] = array[j];
            word[i] = '\0';
            cout<<"macro: "<<word<<endl;
        }

        // beggining of a string
        else if(ch == '"'){
            ch = fgetc(fd);
            // until the end of the string
            while(ch!='"' && ch!=EOF){
                array[i] = ch;
                i++;
                ch = fgetc(fd);
            }
            word = new char[i+1];
            for(int j=0;j<i;j++)  word[j] = array[j];
            word[i] = '\0';
            cout<<"string: "<<word<<endl;
        }

        // check for comments
        else if( ch == '/' ){
            ch = fgetc(fd);
            if(ch == '/'){
                ch = fgetc(fd);
                while(ch!='\n' && ch!=EOF){
                    array[i] = ch;
                    i++;
                    ch = fgetc(fd);
                }
            }
            else if(ch == '*'){
                ch = fgetc(fd);
                array[i] = ch;
                i++;
                while(ch!='*' && ch!=EOF){
                    array[i] = ch;
                    i++;
                    ch = fgetc(fd);
                }
                ch = fgetc(fd);
                while(ch!='/' && ch!=EOF){
                    ch = fgetc(fd);
                }
            }
            word = new char[i+1];
            for(int j=0;j<i;j++)  word[j] = array[j];
            word[i] = '\0';
            cout<<"comment: "<<word<<endl;
        }

        ch = fgetc(fd);
    }

 
    // close the file
    fclose(fd);

}