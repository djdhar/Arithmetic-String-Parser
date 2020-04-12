#include<bits/stdc++.h>
using namespace std;
map<int, char> int2char;
map<char,int> char2int;


#define INORDER_FILE "inorder"
#define PREORDER_FILE "preorder"



bool isOperator(char c){
    if(c=='+'|| c=='-' || c=='*' || c=='/' || c=='^')
        return true;
    return false;
}
string extractIntegerWords(string exp) 
{
    char idx='a';
    string newexp="";
    string num="";
    for(int i=0;i<exp.size();i++){
        char c = exp[i];
        if(exp[i]>='0' && exp[i]<='9')
            num+=exp[i];
        else
            {
                newexp+=idx;
                newexp+=c;
                int val = stoi(num);
                int2char[val] = idx;
                char2int[idx] = val;
                idx++;
                num="";
            }
    }
                newexp+=idx;
                int val = stoi(num);
                int2char[val] = idx;
                char2int[idx] = val;
                idx++;
                num="";
    return newexp;
}

int prec(char c) 
{ 
    if(c == '^') 
    return 3; 
    else if(c == '*' || c == '/') 
    return 2; 
    else if(c == '+' || c == '-') 
    return 1; 
    else
    return -1; 
} 
 
string infixToPostfix(string s) 
{ 
    std::stack<char> st; 
    st.push('N'); 
    int l = s.length(); 
    string ns; 
    for(int i = 0; i < l; i++) 
    { 
        if((s[i] >= 'a' && s[i] <= 'z')||(s[i] >= 'A' && s[i] <= 'Z')) 
        ns+=s[i]; 

        else if(s[i] == '(') 
          
        st.push('('); 
          
        else if(s[i] == ')') 
        { 
            while(st.top() != 'N' && st.top() != '(') 
            { 
                char c = st.top(); 
                st.pop(); 
               ns += c; 
            } 
            if(st.top() == '(') 
            { 
                char c = st.top(); 
                st.pop(); 
            } 
        } 
        else{ 
            while(st.top() != 'N' && prec(s[i]) <= prec(st.top())) 
            { 
                char c = st.top(); 
                st.pop(); 
                ns += c; 
            } 
            st.push(s[i]); 
        } 
  
    } 
    while(st.top() != 'N') 
    { 
        char c = st.top(); 
        st.pop(); 
        ns += c; 
    } 
    return ns;
  
}



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
			f.open(INORDER_FILE,ios::app);
			f<<root->name<<" "<<root->oprator<<",";
			f.close();
		Inorder(root->right);
	}

}

void Preorder(Node* root){
	if(root){
		fstream f;
		f.open(PREORDER_FILE,ios::app);
		f<<root->name<<" "<<root->oprator<<",";
		f.close();
		Preorder(root->left);
		Preorder(root->right);
	}
}

void makefree(){
	fstream f;
	f.open(PREORDER_FILE,ios::out);
	f.close();
	fstream f2;
	f2.open(INORDER_FILE,ios::out);
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

double Calculate( Node *l, Node *r, char op){
    double res=0;
    if(op=='+'){
        res= stod(l->name)+stod(r->name);
    }
    if(op=='-'){
        res= stod(l->name)-stod(r->name);
    }
    if(op=='*'){
        res= stod(l->name)*stod(r->name);
    }
    if(op=='/'){
        res= stod(l->name)/stod(r->name);
    }
    return res;
}

Node* postfixToTree(string s){
    for(int i=0;i<s.size();i++){
        char c = s[i];
        if(!isOperator(c)){
            Node *leaf = new Node(char2int[c]); stk.push(leaf);
            
        }
        else{
            Node *r=stk.top();
            stk.pop();
            Node *l = stk.top();
            stk.pop();
            double res = Calculate(l,r,c);
            //cout<<res<<endl;
            Node *nd = new Node((float)res,c);
            nd->left=l;
            nd->right=r;
            stk.push(nd);
        }
    }
    return stk.top();
}



int main(){
    //Developed by DJ
    cout<< "Enter the expression :"<<endl<<endl;
    string expression;
    // take arithmetic expression
    cin>> expression;
    cout<<endl<<endl;
    // arithmetic to algebric infix expression
    cout<<"The algebric form of this infix expression : "<<endl<<endl;
    string mappedstring = extractIntegerWords(expression);
    cout<<mappedstring<<endl<<endl;
    //algebric infix to postfix expression
    cout<<"After conversion of the infix to postfix : "<<endl<<endl;
    string postfixstring = infixToPostfix(mappedstring);
    cout<<postfixstring<<endl<<endl;

    cout<<"Development of the parse tree from the post-fix expression"<<endl<<endl;
    //Make parse tree from postfix
    Node *parsetree = postfixToTree(postfixstring);
    cout<<"res = "<<parsetree->name<<endl<<endl;
    //Print the parse tree
    printTree(parsetree,nullptr,false);
    //Print the three address code
    threeaddresscodefunction(parsetree);

}