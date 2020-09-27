#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <stack>
using namespace std;

map<double, char> double2char;
map<char, double> char2double;

#define INORDER_FILE "inorder"
#define PREORDER_FILE "preorder"

bool isOperator(char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/')
        return true;
    return false;
}

string tokenizer(string exp)
{
    string ret = "";
    char symbol = 'a';
    bool neg = false;
    for (int i = 0; i < exp.size(); i++)
    {
        char c = exp[i];

        if (c == '-')
        {
            if (i == 0)
            {
                neg = true;
            }
            else if (i > 0 && (isOperator(exp[i - 1]) || (exp[i - 1] == '(')))
            {
                neg = true;
            }
            else
            {

                ret += c;
            }
            continue;
        }

        if (isOperator(c))
        {
            ret += c;
            continue;
        }
        if (c == '(' || c == ')')
        {
            ret += c;
            continue;
        }
        string num = "";
        while (i < exp.size() && !isOperator(exp[i]) && exp[i] != '(' && exp[i] != ')')
        {
            num += exp[i];
            i++;
        }
        i--;
        ret += symbol;
        double res = stod(num);
        if (neg)
            res = -res;

        char2double[symbol] = res;
        double2char[res] = symbol;
        symbol++;
        neg = false;
    }
    return ret;
}

int prec(char c)
{
    if (c == '^')
        return 3;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '+' || c == '-')
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
    for (int i = 0; i < l; i++)
    {
        if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
            ns += s[i];

        else if (s[i] == '(')

            st.push('(');

        else if (s[i] == ')')
        {
            while (st.top() != 'N' && st.top() != '(')
            {
                char c = st.top();
                st.pop();
                ns += c;
            }
            if (st.top() == '(')
            {
                char c = st.top();
                st.pop();
            }
        }
        else
        {
            while (st.top() != 'N' && prec(s[i]) <= prec(st.top()))
            {
                char c = st.top();
                st.pop();
                ns += c;
            }
            st.push(s[i]);
        }
    }
    while (st.top() != 'N')
    {
        char c = st.top();
        st.pop();
        ns += c;
    }
    return ns;
}

class Node
{
public:
    string name;
    char oprator;
    Node *left;
    Node *right;

    Node(string str)
    {
        name = str;
        left = NULL;
        right = NULL;
        oprator = 'N';
    }
    Node(int num)
    {
        name = to_string(num);
        left = NULL;
        right = NULL;
        oprator = 'N';
    }
    Node(int num, char op)
    {
        name = to_string(num);
        left = NULL;
        right = NULL;
        oprator = op;
    }
    Node(float num)
    {
        name = to_string(num);
        left = NULL;
        right = NULL;
        oprator = 'N';
    }
    Node(float num, char op)
    {
        name = to_string(num);
        left = NULL;
        right = NULL;
        oprator = op;
    }
};

Node *parent = new Node("root");
Node *root = parent;
stack<Node *> stk;

void Inorder(Node *root)
{

    if (root)
    {
        Inorder(root->left);
        fstream f;
        f.open(INORDER_FILE, ios::app);
        f << root->name << " " << root->oprator << ",";
        f.close();
        Inorder(root->right);
    }
}

void Preorder(Node *root)
{
    if (root)
    {
        fstream f;
        f.open(PREORDER_FILE, ios::app);
        f << root->name << " " << root->oprator << ",";
        f.close();
        Preorder(root->left);
        Preorder(root->right);
    }
}

void makefree()
{
    fstream f;
    f.open(PREORDER_FILE, ios::out);
    f.close();
    fstream f2;
    f2.open(INORDER_FILE, ios::out);
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

// Recursive function to print binary tree using inorder traversal
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
    cout << "[" << root->name << " , " << root->oprator << "]" << endl;

    if (prev)
        prev->str = prev_str;
    trunk->str = "   |";

    printTree(root->right, trunk, false);
}

//3 address code Form util function
int threeAddressCodeUtil(Node *nodde, int current_count)
{
    if (nodde->oprator == 'N')
    {
        printf("\tt%d\t=\t%g\n",current_count, stod(nodde->name));
        return current_count + 1;
    }
    int left = threeAddressCodeUtil(nodde->left, current_count);
    int right = threeAddressCodeUtil(nodde->right, left);
    int center = right;
    cout << "\tt" << center << "\t="
         << "\tt" << left - 1 << "\t" << nodde->oprator << "\tt" << right - 1 << endl;
    return center + 1;
}

//3 address code Form function
void threeAddressCodeGenerator(Node *root)
{
    cout << endl
         << "Three address code of the expression is given below:" << endl;
    int count = threeAddressCodeUtil(root, 0);
    cout << "Verification: \n\tNo. of nodes in the tree = " << count << endl;
}

double Calculate(Node *l, Node *r, char op)
{
    double res = 0;
    if (op == '+')
    {
        res = stod(l->name) + stod(r->name);
    }
    if (op == '-')
    {
        res = stod(l->name) - stod(r->name);
    }
    if (op == '*')
    {
        res = stod(l->name) * stod(r->name);
    }
    if (op == '/')
    {
        res = stod(l->name) / stod(r->name);
    }
    return res;
}

Node *postfixToTree(string s)
{
    for (int i = 0; i < s.size(); i++)
    {
        char c = s[i];
        if (!isOperator(c))
        {
            Node *leaf = new Node((float)char2double[c]);
            stk.push(leaf);
        }
        else
        {
            Node *r = stk.top();
            stk.pop();
            Node *l = stk.top();
            stk.pop();
            double res = Calculate(l, r, c);
            Node *nd = new Node((float)res, c);
            nd->left = l;
            nd->right = r;
            stk.push(nd);
        }
    }
    return stk.top();
}

int main()
{
    string expression;
    cin >> expression;
    makefree();
    
    string mappedstring = tokenizer(expression);
    cout << "Tokens : " << mappedstring <<endl;

    string postfixstring = infixToPostfix(mappedstring);

    Node *parsetree = postfixToTree(postfixstring);
    printf("Result: %g\n\n", stod(parsetree->name));

    Preorder(parsetree);
    Inorder(parsetree);

    threeAddressCodeGenerator(parsetree);
}
