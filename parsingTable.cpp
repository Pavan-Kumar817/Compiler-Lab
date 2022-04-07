#include<iostream>
#include<iomanip>
#include<vector>
#include<map>
#include<set>
using namespace std;

vector<string> productions;
map<char, set<char>> first;
map<char, set<char>> follow;
map<string, set<char>> firstOfBody;
map<char, map<char, vector<string>>> parser;
set<char> term;
set<char> nonterm;

void printFirst() {
    cout << "-----FIRST-----"<<endl;
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

void printFollow() {
    cout<<"-----FOLLOW-----"<<endl;
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

void printppTable() {
    cout<<"-----PARSING TABLE-----"<<endl;
    map<char, map<char, vector<string>>>::iterator itr;
    map<char, vector<string>>::iterator ptr;
    for (itr = parser.begin(); itr != parser.end(); itr++) {
        for (ptr = itr->second.begin(); ptr != itr->second.end(); ptr++) {
            cout << "M[ " << itr->first << "," << ptr->first<< " ] = { ";
            for (int i=0; i<ptr->second.size(); i++) {
                cout << ptr->second[i] << " ";
            }
            cout << "}" << endl;
        }

    }
    cout<<setw(10)<<" ";
    for(char ch:term){
        cout<<setw(20)<<left<<ch;
    }
    cout<<endl;

    for(char ch:nonterm){
        cout<<setw(10)<<ch;
        for(char cc:term){
            if (parser[ch][cc].size() == 0) cout << setw(20)<<left<<" ";
            else {
                string temp; 
                for (int i=0; i<parser[ch][cc].size(); i++) {
                    temp += parser[ch][cc][i];
                }
                cout << setw(20)<<left<<temp;
            }    
        }
        cout<<endl;
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
            int flag = (first[productions[i][0]].find('^') != first[productions[i][0]].end())?1:0;
            for (int j=3; j<k; j++) {
                
                if (j==3) {
                    first[productions[i][0]].insert(first[productions[i][j]].begin(), first[productions[i][j]].end());
                    if (j<k-1 && flag == 0) first[productions[i][0]].erase('^');
                }
                else if (j>3 && isupper(productions[i][j-1]) && first[productions[i][j-1]].find('^') != first[productions[i][j-1]].end()) {
                    if (isupper(productions[i][j])) {
                        first[productions[i][0]].insert(first[productions[i][j]].begin(), first[productions[i][j]].end());
                        if (j<k-1 && flag == 0) first[productions[i][0]].erase('^');
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

bool containsEpsilon(int m, int n) {
    for (int i=n; i<productions[m].size(); i++) {
        if (!isupper(productions[m][i])) {
            follow[productions[m][n-1]].insert(productions[m][i]);
            return false;
        }
        else if (first[productions[m][i]].find('^') == first[productions[m][i]].end())
            return false;
        else if (i != productions[m].size()-1 && (first[productions[m][i]].find('^') != first[productions[m][i]].end()))
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
                    follow[productions[i][j]].erase('^');
                    
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

void firstofBody(int n) {
    for (int i=0; i<n; i++) {
        string body = productions[i].substr(3);
        if (body == "^") {
            firstOfBody[body].insert('^');
            continue;
        }
        int idx = 3;
        while (idx != productions[i].size()) {
            if (!isupper(productions[i][idx])) {
                firstOfBody[body].insert(productions[i][idx]);
                break;
            }
            else {
                firstOfBody[body].insert(first[productions[i][idx]].begin(), first[productions[i][idx]].end());
                if (first[productions[i][idx]].find('^') == first[productions[i][idx]].end()) break;
            }
            idx++;
        }
        if (idx != productions[i].size())
            firstOfBody[body].erase('^');
    }
}

void ppTable(int n) {
    firstofBody(n);
    for (int i=0; i<n; i++) {
        string body = productions[i].substr(3);
        set<char> :: iterator itr;
        for (itr = firstOfBody[body].begin(); itr != firstOfBody[body].end(); itr++) {
            if (*itr != '^') {
                parser[productions[i][0]][*itr].push_back(productions[i]);
            }
            else {
                set<char> :: iterator itr1;
                for (itr1 = follow[productions[i][0]].begin(); itr1 != follow[productions[i][0]].end(); itr1++) {
                    parser[productions[i][0]][*itr1].push_back(productions[i]);
                }
            }
        }
    }
    printppTable();
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
    for (int i=0; i<k; i++) {
        nonterm.insert(productions[i][0]);
        for (int j=3; j<productions[i].size(); j++) {
            if (!isupper(productions[i][j]) && productions[i][j] != '^') {
                term.insert(productions[i][j]);
            }
        }
    }
    // copy(term.begin(), term.end(), t.begin());
    // copy(nonterm.begin(), nonterm.end(), nont.begin());
    term.insert('$');
    ppTable(k);
    return 0;
}