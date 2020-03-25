##  Parsing-Random-Length-Arithmetic-Expression
**BCSE III- Compiler Design Lab Assignment 5** 

*Project 10*  
Write a program that will parse an arithmetic expression of any length involvng operators `{ + , - , * , / }` and generate an annotated parse tree displaying the value of the expression.  
Extend the program to generate a three address code of the expression.

#### How to run the code
```
cd processor
lex calc.l
yacc -d calc.y
g++ lex.yy.c y.tab.c -w
./a.out
```
#### Group Details
|Roll Number| Name|
|--|--|
|0017105010**67**|[Dibyajyoti Dhar](https://github.com/djdhar) |
|0017105010**71**| [Devesh Jalan](https://github.com/djalan) |
|0017105010**73**|[Rohit Chattopadhyay](https://github.com/RohitChattopadhyay) |
|0017105010**76**| [Priti Shaw](https://github.com/PritiShaw) |