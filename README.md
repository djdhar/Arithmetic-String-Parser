# Parsing-Random-Length-Arithmetic-Expression

## BCSE III- Compiler Design Lab 
### Assignment 5
### *Project 10*
Write a program that will parse an arithmetic expression of any length involvng operators { + , - , * , / } and generate an annotated parse tree displaying the value of the expression.

Extend the program to generate a three three address code of the expression.

#### How to run the code 

1. lex calc.l
2. yacc -d calc.y
3. g++ lex.yy.c y.yab.c -w
4. ./a.out
