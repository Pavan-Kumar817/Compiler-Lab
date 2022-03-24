// INPUT FORMAT:
//  1. Epsilon is represented by #
// 2. All uppercase letters are Non terminals and others are terminals.
// 3. Terminals have only one character. i.e., terminals like 'id' are not allowed but 'a' is allowed.
// 4. No spaces should be present.

// The first line of input is the no.of production rules n. The next n lines are followed by the production rules.

/*
**Example input-1:**
4
S->ACB|CbB|Ba
A->da|BC
B->g|#
C->h|#
**Example Output-1:**
FOLLOW(A) = { $, g, h }
FOLLOW(B) = { $, a, g, h }
FOLLOW(C) = { $, b, g, h }
FOLLOW(S) = { $ }
*/


#include<iostream>
#include<vector>
#include<map>
#include<set>
using namespace std;

vector<string> productions;
map<char, set<char>> first;
map<char, set<char>> follow;

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
            int flag = (first[productions[i][0]].find('#') != first[productions[i][0]].end())?1:0;
            for (int j=3; j<k; j++) {
                
                if (j==3) {
                    first[productions[i][0]].insert(first[productions[i][j]].begin(), first[productions[i][j]].end());
                    if (j<k-1 && flag == 0) first[productions[i][0]].erase('#');
                }
                else if (j>3 && isupper(productions[i][j-1]) && first[productions[i][j-1]].find('#') != first[productions[i][j-1]].end()) {
                    if (isupper(productions[i][j])) {
                        first[productions[i][0]].insert(first[productions[i][j]].begin(), first[productions[i][j]].end());
                        if (j<k-1 && flag == 0) first[productions[i][0]].erase('#');
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
    // printFirst();
}

void printFollow() {
    map<char, set<char>>:: iterator itr;
    for (itr = follow.begin(); itr != follow.end(); itr++) {
        cout << "FOLLOW(" << itr->first << ") = ";
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

bool containsEpsilon(int m, int n) {
    for (int i=n; i<productions[m].size(); i++) {
        if (!isupper(productions[m][i])) {
            follow[productions[m][n-1]].insert(productions[m][i]);
            return false;
        }
        else if (first[productions[m][i]].find('#') == first[productions[m][i]].end())
            return false;
        else if (i != productions[m].size()-1 && (first[productions[m][i]].find('#') != first[productions[m][i]].end()))
            follow[productions[m][n-1]].insert(first[productions[m][i+1]].begin(), first[productions[m][i+1]].end());
    }
    return true;
}

void findFollow(int n) {
    findFirst(n);
    follow[productions[0][0]].insert('$');
    bool completed = false;
    while (!completed) {
        completed = true;
        for (int i=0; i<n; i++) {
            for (int j=3; j<productions[i].size(); j++) {
                // int temp1 = follow[productions[i][j]].size();
                if (isupper(productions[i][j]) && j != productions[i].size()-1) {
                    int temp1 = follow[productions[i][j]].size();
                    if (!isupper(productions[i][j+1]))
                        follow[productions[i][j]].insert(productions[i][j+1]);
                    else {
                        follow[productions[i][j]].insert(first[productions[i][j+1]].begin(), first[productions[i][j+1]].end());
                        if (containsEpsilon(i, j+1)) {
                            follow[productions[i][j]].insert(follow[productions[i][0]].begin(), follow[productions[i][0]].end());
                        }
                    }
                    follow[productions[i][j]].erase('#');
                    
                    int temp2 = follow[productions[i][j]].size();
                    if (temp1 != temp2) completed = false;
                }
                else if (isupper(productions[i][j]) && j == productions[i].size()-1) {
                    int temp1 = follow[productions[i][j]].size();
                    follow[productions[i][j]].insert(follow[productions[i][0]].begin(), follow[productions[i][0]].end());
                    int temp2 = follow[productions[i][j]].size();
                    if (temp1 != temp2) completed = false;
                }
            }
        }
    }
    printFollow();
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
    findFollow(k);
    return 0;
}