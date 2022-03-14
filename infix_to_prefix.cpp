#include<bits/stdc++.h>
using namespace std;

int priority(char op) {
    if (op == '+' || op == '-')
        return 1;
    else if (op == '*' || op == '/')
        return 2;
    return 0;
} 

string infix_to_prefix(string infix) {
    string prefix;
    stack<char> operators;
    int n = infix.size();
    reverse(infix.begin(), infix.end());
    
    for (int i=0; i<n; i++) {
        if (isalpha(infix[i]))
            prefix += infix[i];
        else if (infix[i] == ')')
            operators.push(infix[i]);
        else if (infix[i] == '(') {
            while(operators.top() != ')') {
                prefix += operators.top();
                operators.pop();
            }
            operators.pop();
        }
        else if (infix[i] == '+' || infix[i] == '*' || infix[i] == '/' || infix[i] == '-') {
            if (operators.empty())
                operators.push(infix[i]);
            else {
                while (priority(infix[i]) <= priority(operators.top())) {
                    prefix += operators.top();
                    operators.pop();
                }
                operators.push(infix[i]);
            }
        }
    }
    reverse(prefix.begin(), prefix.end());

    return prefix;
}

int main() {
    string infix_notation = "(a*b+c)";
    string prefix_notation = infix_to_prefix(infix_notation);
    cout << prefix_notation << endl;
    return 0;
}