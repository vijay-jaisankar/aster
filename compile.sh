cd lexer/
g++ -o lexer Helpers.cpp Keywords.cpp Operators.cpp Token.cpp main.cpp Structs.h
echo "Lexer compiled"
cd ../parser/
g++ -o parser main.cpp node.h token.h Listtok.cpp
echo "Parser compiled"


cd ../lexer/
./lexer $1 

cd ../parser
touch output.txt

cp ../lexer/output.txt output.txt 

pwd
./parser

