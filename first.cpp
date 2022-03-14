// INPUT FORMAT:
//  1. Epsilon is represented by @
// 2. All uppercase letters are Non terminals and others are terminals.
// 3. Terminals have only one character. i.e., terminals like 'id' are not allowed but 'a' is allowed.
// 4. No spaces should be present.

// The first line of input is the no.of production rules n. The next n lines are followed by the production rules.
/*
**Example input-1:**
4
S->ACB|CbB|Ba
A->da|BC
B->g|@
C->h|@
**Example Output-1:**
FIRST(A) = { @, d, g, h }
FIRST(B) = { @, g }
FIRST(C) = { @, h }
FIRST(S) = { @, a, b, d, g, h }
*/

/*
**Example input-2:**
5
E->TA
A->+TA|@
T->FB
B->*FB|@
F->(E)|a
**Example Output-2:**
FIRST(A) = { +, @ }
FIRST(B) = { *, @ }
FIRST(E) = { (, a }
FIRST(F) = { (, a }
FIRST(T) = { (, a }
*/


#include<bits/stdc++.h>
using namespace std;

vector<string> productions;
map<char, set<char>> first;

void printFirst() {
    map<char, set<char>>:: iterator itr;
    for (itr = first.begin(); itr != first.end(); itr++) {
        cout << "FIRST(" << itr->first << ") = ";
        set<char>::iterator itr1;
        cout << "{ ";
        for (itr1 = itr->second.begin(); itr1 != itr->second.end(); itr1++) {
            cout << *itr1;
            if (++itr1 != itr->second.end()) cout<<", ";
            itr1--;
        }
        cout << " }" << endl;
    }
}

void findFirst(int n) {
    bool completed = false;
    for (int i=0; i<n; i++) {
        first[productions[i][0]] = {};
    }
    for (int i=0; i<n; i++) {
        if (!isupper(productions[i][3])) {
            first[productions[i][0]].insert(productions[i][3]);
        }
    }
    while (!completed) {
        completed = true;
        // printFirst();
        // cout << "----"<<endl;
        for (int i=0; i<n; i++) {
            if (!isupper(productions[i][3])) continue;
            int temp1 = first[productions[i][0]].size();
            int k = productions[i].size();
            int flag = (first[productions[i][0]].find('@') != first[productions[i][0]].end())?1:0;
            for (int j=3; j<k; j++) {
                
                if (j==3) {
                    first[productions[i][0]].insert(first[productions[i][j]].begin(), first[productions[i][j]].end());
                    if (j<k-1 && flag == 0) first[productions[i][0]].erase('@');
                }
                else if (j>3 && isupper(productions[i][j-1]) && first[productions[i][j-1]].find('@') != first[productions[i][j-1]].end()) {
                    if (isupper(productions[i][j])) {
                        first[productions[i][0]].insert(first[productions[i][j]].begin(), first[productions[i][j]].end());
                        if (j<k-1 && flag == 0) first[productions[i][0]].erase('@');
                    }
                    else
                        first[productions[i][0]].insert(productions[i][j]);
                }
                else break;
                // cout<<productions[i][0]<<endl;
                // printFirst();
                // cout << "----"<<endl;
            }
            int temp2 = first[productions[i][0]].size();
            if (temp1 != temp2) completed = false;
            
        }
    }
    for (int i=0; i<n; i++) {
        if (!isupper(productions[i][3])) {
            first[productions[i][0]].insert(productions[i][3]);
        }
    }
    printFirst();
}

int main() {
    int n;
    cin >> n;
    for (int i=0; i<n; i++) {
        string temp;
        cin >> temp;
        string nt = temp.substr(0, 3);
        temp.erase(0, 3);
        for (int j=0; j<temp.size(); j++) {
            if (temp[j] == '|') {
                productions.push_back(nt + temp.substr(0, j));
                temp.erase(0, j+1);
                j=0;
            }
        }
        productions.push_back(nt+temp);
    }
    int k = productions.size();
    // for (int i=0; i<k; i++) {
    //     cout << productions[i] << endl;
    // }
    findFirst(k);
    return 0;
}