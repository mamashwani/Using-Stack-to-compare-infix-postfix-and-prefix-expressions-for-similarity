# Using-Stack-to-compare-infix-postfix-and-prefix-expressions-for-similarity
Implement a program in C++ that can evaluate a list ofarithmetic expressions for validity, and compare them for similarity. 

# Assumptions:
- The input file is a small plain text file; no need to handle binary files.
- Each input file may contain maximum 1000 expressions.In an expression, only unit digits (0-9) will be used.
- An operand will be always a single character.
- There will be no space in an expression.
- An input file may contain empty lines between expressions.
- Operators: + −.  Parentheses: (, ), {, }, [, ]. 
- Note that, input and output, all are case sensitive.
- The output should be exactly matched with the format. 

# Notes
- Each line will contain an arithmetic expression.  
- Expressions consist of numbers (0-9), lowercase alphabets (a-z), uppercase alphabets (A-Z), ‘+’, ‘-‘, ‘(‘, ‘)’,‘{‘, ‘}’, ‘[‘, and ‘]’.
- An operand (numbers, and alphabets) will not appear the second time in a single expression.
- You need to check whether the expression is valid or not. An expression will be invalid if opening and ending parenthesis dont match. - If an expression is not valid, the output will be “Error at: ”+expression number, then continue to process next expression.
- If there is no error with the expressions, you need to compare those expressions. If they are similar, then the output will be “Yes”, otherwise “No”.
- All records should be processed sequentially from beginning to end.
- The 9 "input5x.txt" files are the 9 input files that were used to test this code
- The 9 "output5x.txt" files are the files outputted by the program.
- The 9 "ans5x.txt" files are files containing the correct output that should occur from each corresponding input file, and are available for comparison to the outputs files to ensure correct output. 
- This code was tested on the University of Houston's Linux server and passed all the test cases.
- The "ArgumentManager.h" file parses arguments to sequentially open the 9 input files to automatically test the code on the server.
- The "test.sh" file is a SHELL script for automatically testing the input files on the Linux server.
- The "compile.sh" file is  SHELL script for automatically compiling the code on the Linux server before running the tests.

# Resources:

https://www.geeksforgeeks.org/convert-infix-prefix-notation/

https://www.geeksforgeeks.org/postfix-prefix-conversion/
