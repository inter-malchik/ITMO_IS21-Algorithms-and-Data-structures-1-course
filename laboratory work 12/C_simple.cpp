#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

void printLCS(int i, int j, vector<vector<pair<int, int >>> const &prev, string &s) {
    if (i == 0 or j == 0)
        return;
    if (prev[i][j] == pair(i - 1, j - 1)) {
        printLCS(i - 1, j - 1, prev, s);
        cout << s[i - 1];
    } else if (prev[i][j] == pair(i - 1, j))
        printLCS(i - 1, j, prev, s);
    else
        printLCS(i, j - 1, prev, s);
}

int main() {
    string s1;
    string s2;
    cin >> s1 >> s2;
    
    unsigned m = s1.size(), n = s2.size();
    vector<vector<unsigned>> lcs(m + 1, vector<unsigned>(n + 1, 0));
    vector<vector<pair<int, int>>> prev(m + 1, vector<pair<int, int >>(n + 1, {0, 0}));
    for (unsigned i = 0; i <= m; i++) {
        for (unsigned j = 0; j <= n; j++) {
            lcs[i][j] = (!i || !j) ? 0 :
                        (s1[i - 1] == s2[j - 1]) ? lcs[i - 1][j - 1] + 1 :
                        (s1[i - 1] != s2[j - 1]) ? max(lcs[i][j - 1], lcs[i - 1][j]) : 0;

            prev[i][j] = (!i || !j) ? pair<int, int>(0, 0) :
                         (s1[i - 1] == s2[j - 1]) ? (pair<int, int>(i - 1, j - 1)) :
                         (s1[i - 1] != s2[j - 1]) ?
                         ((lcs[i - 1][j] >= lcs[i][j - 1]) ?
                          pair<int, int>(i - 1, j) : pair<int, int>(i, j - 1))
                                                  : pair<int, int>(0, 0);
        }
        if (i<2)
            continue;
        else
            lcs[i-2].clear();
    }

    printLCS(m, n, prev, s1);
}