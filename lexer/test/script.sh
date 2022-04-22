# Going to the appropriate directory
cd ../
pwd 

# Compiling the code
g++ -o lexer Helpers.cpp Keywords.cpp Operators.cpp Token.cpp main.cpp 

# Executing the code
./lexer ../src/test1.c > test/output1.txt
./lexer ../src/test2.c > test/output2.txt
./lexer ../src/test3.c > test/output3.txt
./lexer ../src/test4.c > test/output4.txt

# Deleting the Executable
rm -f ./lexer

