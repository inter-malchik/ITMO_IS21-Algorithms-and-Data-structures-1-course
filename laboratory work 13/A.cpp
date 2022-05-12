#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin("search1.in");
ofstream fout("search1.out");

int main() {
    string p;
    string t;
    fin >> p >> t;
    vector<size_t> subs;
    for (size_t i = 0; i < t.size(); i++) {
        bool ok = true;
        for (size_t j = 0; j < p.size(); j++) {
            if (p[j] != t[i + j]) {
                ok = false;
                break;
            }
        }
        if (ok)
            subs.push_back(i + 1);
    }
    fout << subs.size() << endl;
    for (size_t sub: subs)
        fout << sub << ' ';
    return 0;
}