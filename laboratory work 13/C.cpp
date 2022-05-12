#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <list>

using namespace std;

ifstream fin("prefix.in");
ofstream fout("prefix.out");

int main() {
    string s;
    fin >> s;
    vector<size_t> pref(s.length()+1, 0);
    size_t i = 1, j = 0, n = s.length();

    while (i < n)
        if (s[i] == s[j])
            pref[i++ + 1] = j++ + 1;
        else if (j)
            j = pref[j];
        else
            pref[i++ + 1] = 0;

    for (size_t ind = 1; ind < pref.size(); ind++)
        fout << pref[ind] << ' ';

    return 0;
}
