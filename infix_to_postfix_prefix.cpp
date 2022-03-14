/*INPUT can contain SPACES*/

#include<bits/stdc++.h>
using namespace std;

int precedence(char op) {
    if (op == '+' | op == '-')
        return 1;
    else if (op == '*' | op == '/')
        return 2;
    else if (op == '^')
        return 3;
    return 0;
}

string infix_to_postfix(string infix) {
    string postfix;
    stack <char> i2p_helper;
    int n = infix.size();

    for (int i=0; i<n; i++) {
        if (isalnum(infix[i])) 
            postfix += infix[i];
        else if (infix[i] == '(')
            i2p_helper.push(infix[i]);
        else if (infix[i] == ')') {
            while (i2p_helper.top() != '(') {
                postfix += i2p_helper.top();
                i2p_helper.pop();
            }
            i2p_helper.pop();
        }
        else {
            while (!i2p_helper.empty() &&
            precedence(infix[i]) <= precedence(i2p_helper.top())) {
                postfix += i2p_helper.top();
                i2p_helper.pop();
            }
            i2p_helper.push(infix[i]);
        }
    }
    while (!i2p_helper.empty()) {
        postfix += i2p_helper.top();
        i2p_helper.pop();
    }

    return postfix;
}

string postfix_to_prefix(string postfix) {
    string prefix;
    stack <string> p2p_helper;
    int n = postfix.size();

    for (int i=0; i<n; i++) {
        if (isalnum(postfix[i])) {
            p2p_helper.push(string(1, postfix[i]));
        }
        else if (postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/' || postfix[i] == '^') {
            string s1 = p2p_helper.top();
            p2p_helper.pop();
            string s2 = p2p_helper.top();
            p2p_helper.pop();
            string s = postfix[i] + s2 + s1;
            p2p_helper.push(s);
        }
    }
    while (!p2p_helper.empty()) {
        prefix += p2p_helper.top();
        p2p_helper.pop();
    }

    return prefix;
}

int main() {
    string infix_notation;
    getline(cin, infix_notation);
    int l = infix_notation.length();
    int c = count(infix_notation.begin(), infix_notation.end(), ' ');
    remove(infix_notation.begin(), infix_notation.end(), ' ');
    infix_notation.resize(l-c);
    string postfix_notation = infix_to_postfix(infix_notation);
    string prefix_notation = postfix_to_prefix(postfix_notation);
    cout << "Infix Notation\t"<<"\t:\t"<<infix_notation<<endl;
    cout << "Postfix Notation\t"<<":\t"<<postfix_notation<<endl;
    cout << "Prefix Notation\t"<<"\t:\t"<<prefix_notation<<endl;
    return 0;
}