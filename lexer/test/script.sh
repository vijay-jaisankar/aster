# Going to the appropriate directory
cd ../
pwd 

# Compiling the code
g++ -o lexer Helpers.cpp Keywords.cpp Operators.cpp Token.cpp main.cpp Structs.h

# Executing the code
k=1

for i in ../src/*.c;
do 
    ./lexer $i > test/$k.txt 
    ((k=k+1))
done

# Deleting the Executable
rm -f ./lexer

