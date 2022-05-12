#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <list>

using namespace std;

ifstream fin("search2.in");
ofstream fout("search2.out");

#define X_COEFF 67;

class RabinKarp {
public:
    RabinKarp(string &s1): p(s1), pows(p.length(), 1) {
        for (unsigned i = 1; i < pows.size(); i++)
            pows[i] = pows[i - 1] * X_COEFF;

        for (unsigned i = 0; i < p.size(); i++)
            pattern_hash += p[i] * pows[i];
    }

    list<size_t> search(string &t) {
        pows.resize(max(t.size(), p.size()));
        for (unsigned i = p.size(); i < t.size(); i++)
            pows[i] = pows[i - 1] * X_COEFF;

        vector<unsigned long long> string_hash(t.length());
        for (unsigned i = 0; i < t.length(); ++i)
            string_hash[i] = (!i) ? t[i] * pows[i] : t[i] * pows[i] + string_hash[i - 1];

        list<size_t> subs;
        
        for (unsigned i = 0; i < t.length(); i++) {
            if (i + p.length() > t.length())
                break;

            unsigned long long currentHash = (!i) ? string_hash[i + p.length() - 1] : string_hash[i + p.length() - 1] - string_hash[i - 1];

            if (currentHash == pattern_hash * pows[i])
                subs.push_back(i + 1);
        }
        return subs;
    }


private:
    string p;
    vector<unsigned long long> pows;
    unsigned long long pattern_hash = 0;
};

int main() {
    string p, t;
    fin >> p >> t;

    list<size_t> subs = RabinKarp(p).search(t);
    fout << subs.size() << endl;
    for (size_t sub: subs)
        fout << sub << ' ';
}