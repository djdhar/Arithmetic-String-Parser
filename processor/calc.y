%{

#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h>
#include<string>
using namespace std;

extern int yylex();
extern int yyparse();
extern FILE* yyin;

class Node{
	public:
	string name;
	char oprator;
	Node *left;
	Node *right;

	Node(string str){
		name=str;
		left=NULL;
		right=NULL;
		oprator='N';
	}
	Node(int num){
		name = to_string(num);
		left=NULL;
		right=NULL;
		oprator='N';
	}
	Node(int num, char op){
		name = to_string(num);
		left=NULL;
		right=NULL;
		oprator=op;
	}
	Node(float num){
		name = to_string(num);
		left=NULL;
		right=NULL;
		oprator='N';
	}
	Node(float num, char op){
		name = to_string(num);
		left=NULL;
		right=NULL;
		oprator=op;
	}
};

Node *parent = new Node("root");
Node *root= parent;
stack<Node*> stk;

void Inorder(Node* root){

	if(root){
		Inorder(root->left);
			fstream f;
			f.open("inorder.csv",ios::app);
			f<<root->name<<" "<<root->oprator<<",";
			f.close();
			cout<<" *** "<<root->name<<" *** "<<root->oprator<<endl;
		Inorder(root->right);
	}

}

void Preorder(Node* root){
	if(root){
		fstream f;
		f.open("preorder.csv",ios::app);
		f<<root->name<<" "<<root->oprator<<",";
		cout<<" *** "<<root->name<<" *** "<<root->oprator<<endl;
		f.close();
		Preorder(root->left);
		Preorder(root->right);
	}
}

void makefree(){
	fstream f;
	f.open("preorder.csv",ios::out);
	f.close();
	fstream f2;
	f2.open("inorder.csv",ios::out);
	f2.close();
}

struct Trunk
{
    Trunk *prev;
    string str;

    Trunk(Trunk *prev, string str)
    {
        this->prev = prev;
        this->str = str;
    }
};

// Helper function to print branches of the binary tree
void showTrunks(Trunk *p)
{
    if (p == nullptr)
        return;

    showTrunks(p->prev);

    cout << p->str;
}

// Recursive function to print binary tree
// It uses inorder traversal
void printTree(Node *root, Trunk *prev, bool isLeft)
{
    if (root == nullptr)
        return;
    
    string prev_str = "    ";
    Trunk *trunk = new Trunk(prev, prev_str);

    printTree(root->left, trunk, true);

    if (!prev)
        trunk->str = "---";
    else if (isLeft)
    {
        trunk->str = ".---";
        prev_str = "   |";
    }
    else
    {
        trunk->str = "`---";
        prev->str = prev_str;
    }

    showTrunks(trunk);
    cout<<"["<<root->name<<" , "<<root->oprator<<"]"<<endl;

    if (prev)
        prev->str = prev_str;
    trunk->str = "   |";

    printTree(root->right, trunk, false);
}

//util function 
int threeaddresscodeutil(Node* nodde, int current_count)
{
	if(nodde->oprator=='N')
	{
		cout<<"\tt"<<current_count<<"\t=\t"<<nodde->name<<endl;
		return current_count+1;
	}
	int left=threeaddresscodeutil(nodde->left,current_count);
	int right=threeaddresscodeutil(nodde->right,left);
	int center=right;
	cout<<"\tt"<<center<<"\t="<<"\tt"<<left-1<<"\t"<<nodde->oprator<<"\tt"<<right-1<<endl;
	return center+1;
}


//3 address code Form function
void threeaddresscodefunction(Node* root)
{
	cout<<endl<<"Three address code of the expression is given below:"<<endl;
	int count=threeaddresscodeutil(root,0);
	cout<<"Verification: \n\tNo. of nodes in the tree = "<<count<<endl;
}


void yyerror(const char* s);
%}

%union {
	int ival;
	float fval;
}

%token<ival> T_INT
%token<fval> T_FLOAT
%token T_PLUS T_MINUS T_MULTIPLY T_DIVIDE T_LEFT T_RIGHT
%token T_NEWLINE T_QUIT
%left T_PLUS T_MINUS
%left T_MULTIPLY T_DIVIDE

%type<ival> expression
%type<fval> mixed_expression

%start calculation

%%

calculation:
	   | calculation line
;

line: T_NEWLINE
    | mixed_expression T_NEWLINE { printf("\n\tResult: %f\n\n", $1); makefree(); cout<<"Inorder Traversal"<<endl; Inorder(stk.top()); cout<<endl; cout<<"Preorder Traversal"<<endl; Preorder(stk.top()); cout<<endl<<"Parse Tree"<<endl; printTree(stk.top(),nullptr,false);threeaddresscodefunction(stk.top());cout<<"\nEnter next expression or 'exit' to end session"<<endl<<"=>";}
    | expression T_NEWLINE { printf("\nResult: %i\n\n", $1);cout<<"Inorder Traversal"<<endl; Inorder(stk.top()); cout<<endl<<"Parse Tree"<<endl; printTree(stk.top(),nullptr,false);threeaddresscodefunction(stk.top());cout<<"\nEnter next expression or 'exit' to end session"<<endl<<"=>"; }
    | T_QUIT T_NEWLINE {   cout<<"\n\t-----Session Terminated-----\n"<<endl;exit(0);}
;
//cout<<to_string($$)<<endl ; Node *node = new Node($1,'+'); node->right=stk.top(); stk.pop(); node->left=stk.top(); stk.pop(); stk.push(node);
mixed_expression: T_FLOAT                 		 { $$ = $1; /*cout<<to_string($$)<<endl*/ ;Node *leaf = new Node($1); stk.push(leaf); }
	  | mixed_expression T_PLUS mixed_expression	 { $$ = $1 + $3; /*cout<<to_string($$)<<endl*/ ; Node *node = new Node($$,'+'); node->right=stk.top(); stk.pop(); node->left=stk.top(); stk.pop(); stk.push(node);} 
	  | mixed_expression T_MINUS mixed_expression	 { $$ = $1 - $3; /*cout<<to_string($$)<<endl*/ ; Node *node = new Node($$,'-'); node->right=stk.top(); stk.pop(); node->left=stk.top(); stk.pop(); stk.push(node);}
	  | mixed_expression T_MULTIPLY mixed_expression { $$ = $1 * $3; /*cout<<to_string($$)<<endl*/ ; Node *node = new Node($$,'*'); node->right=stk.top(); stk.pop(); node->left=stk.top(); stk.pop(); stk.push(node);}
	  | mixed_expression T_DIVIDE mixed_expression	 { $$ = $1 / $3; /*cout<<to_string($$)<<endl*/ ; Node *node = new Node($$,'/'); node->right=stk.top(); stk.pop(); node->left=stk.top(); stk.pop(); stk.push(node);}
	  | T_LEFT mixed_expression T_RIGHT		 { $$ = $2; }
	  | expression T_PLUS mixed_expression	 	 { $$ = $1 + $3; /*cout<<to_string($$)<<endl*/ ; Node *node = new Node($$,'+'); node->right=stk.top(); stk.pop(); node->left=stk.top(); stk.pop(); stk.push(node);}
	  | expression T_MINUS mixed_expression	 	 { $$ = $1 - $3; /*cout<<to_string($$)<<endl*/ ; Node *node = new Node($$,'-'); node->right=stk.top(); stk.pop(); node->left=stk.top(); stk.pop(); stk.push(node);} 
	  | expression T_MULTIPLY mixed_expression 	 { $$ = $1 * $3; /*cout<<to_string($$)<<endl*/ ; Node *node = new Node($1,'*'); node->right=stk.top(); stk.pop(); node->left=stk.top(); stk.pop(); stk.push(node);}
	  | expression T_DIVIDE mixed_expression	 { $$ = $1 / $3; /*cout<<to_string($$)<<endl*/ ; Node *node = new Node($$,'/'); node->right=stk.top(); stk.pop(); node->left=stk.top(); stk.pop(); stk.push(node);} 
	  | mixed_expression T_PLUS expression	 	 { $$ = $1 + $3; /*cout<<to_string($$)<<endl*/ ; Node *node = new Node($$,'+'); node->right=stk.top(); stk.pop(); node->left=stk.top(); stk.pop(); stk.push(node);} 
	  | mixed_expression T_MINUS expression	 	 { $$ = $1 - $3; /*cout<<to_string($$)<<endl*/ ; Node *node = new Node($$,'-'); node->right=stk.top(); stk.pop(); node->left=stk.top(); stk.pop(); stk.push(node);} 
	  | mixed_expression T_MULTIPLY expression 	 { $$ = $1 * $3; /*cout<<to_string($$)<<endl*/ ; Node *node = new Node($$,'*'); node->right=stk.top(); stk.pop(); node->left=stk.top(); stk.pop(); stk.push(node);} 
	  | mixed_expression T_DIVIDE expression	 { $$ = $1 / $3; /*cout<<to_string($$)<<endl*/ ; Node *node = new Node($$,'/'); node->right=stk.top(); stk.pop(); node->left=stk.top(); stk.pop(); stk.push(node);} 
	  | expression T_DIVIDE expression	{   $$ = $1 / (float)$3; /*cout<<to_string($$)<<endl*/ ; Node *node = new Node($$,'/'); node->right=stk.top(); stk.pop(); node->left=stk.top(); stk.pop(); stk.push(node);} 
;

expression: T_INT						{ $$ = $1; /*cout<<to_string($$)<<endl*/ ;Node *leaf = new Node(to_string($1)); stk.push(leaf); }
	  | expression T_PLUS expression	{ $$ = $1 + $3; /*cout<<to_string($$)<<endl*/ ; Node *node = new Node($$,'+'); node->right=stk.top(); stk.pop(); node->left=stk.top(); stk.pop(); stk.push(node);} 
	  | expression T_MINUS expression	{ $$ = $1 - $3; /*cout<<to_string($$)<<endl*/ ; Node *node = new Node($$,'-'); node->right=stk.top(); stk.pop(); node->left=stk.top(); stk.pop(); stk.push(node);} 
	  | expression T_MULTIPLY expression	{ $$ = $1 * $3; /*cout<<to_string($$)<<endl*/ ; Node *node = new Node($$,'*'); node->right=stk.top(); stk.pop(); node->left=stk.top(); stk.pop(); stk.push(node);} 
	  | T_LEFT expression T_RIGHT		{ $$ = $2; }
;

%%

int main() {
	cout<<"Enter an expression using numbers and operators : +,-,*,/ only"<<endl<<"=>";
	yyin = stdin;

	do {
		yyparse();
	} while(!feof(yyin));

	return 0;
}

void yyerror(const char* s) {
	cout<<"Error"<<endl;
	fprintf(stderr, "Parse error: %s\n", s);
	exit(1);
}
