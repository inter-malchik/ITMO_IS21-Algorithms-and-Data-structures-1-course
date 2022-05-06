#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

struct stringarg {
    stringarg(string *s) : s(s), start(0), finish(s->size()), reverse(false) {}

    stringarg(string *s, size_t st, size_t fi, bool r = false) : s(s), start(st), finish(fi), reverse(r) {}

    string *s;
    size_t start;
    size_t finish;
    bool reverse;

    char operator[](size_t i) const {
        if (!reverse)
            return s->at(start + i);
        else
            return s->at(finish - 1 - i);
    }

    size_t size() const {
        return finish - start;
    }

    bool empty() const {
        return size()==0;
    }

    bool consists(char a) const {
        if (!reverse) {
            for (size_t i = start; i < finish; i++)
                if (s->at(i) == a)
                    return true;
            return false;
        }
        else {
            for (size_t i = finish-1; i >= start; i--) {
                if (s->at(i) == a)
                    return true;
                if (!i)
                    break;
            }
            return false;
        }

    }
};

class CommonSubsequence {
public:
    CommonSubsequence() : ans("") {
        cin >> x >> y;
        stringarg starg1(&x);
        stringarg starg2(&y);

        if (x.size() >= y.size())
            hirschberg(starg1, starg2);
        else
            hirschberg(starg2, starg1);

        for (char an: ans)
            cout << an;

        cout << endl;
    }

private:
    vector<unsigned> LCS(stringarg s1, stringarg s2) {
        unsigned m = s1.size(), n = s2.size();
        vector<unsigned> prevline (n+1, 0);;
        for (unsigned i = 0; i <= m; i++) {
            vector<unsigned> newline (n+1, 0);
            for (unsigned j = 0; j <= n; j++)
                newline[j] = (!i || !j) ? 0 :
                             (s1[i - 1] == s2[j - 1]) ? prevline[j - 1] + 1 :
                             (s1[i - 1] != s2[j - 1]) ? max(newline[j - 1], prevline[j]) : 0;

            prevline = newline;
        }
        return prevline;
    }

    void hirschberg(stringarg s1, stringarg s2) {
        if (s1.empty() || s2.empty())
            return;
        if (s1.size() == 1) {
            if (s2.consists(s1[0]))
                ans += s1[0];
            return;
        }

        size_t mid = s1.size() / 2;


        vector<unsigned> f = LCS(stringarg(s1.s, s1.start, s1.start + mid), s2);

        vector<unsigned> s = LCS(stringarg(s1.s, s1.start + mid, s1.finish, true), stringarg(s2.s, s2.start, s2.finish,true));


        unsigned max = s[0];
        unsigned maxj = 0;

        for (unsigned j = 0; j < s2.size(); j++) {
            unsigned ass = f[j] + s[s2.size() - (j)];
            if (ass > max) {
                max = f[j] + s[s2.size() - (j)];
                maxj = j;
            }
        }

        maxj = (f[s2.size()] > max) ? s2.size() : maxj;

        hirschberg(stringarg(s1.s, s1.start, s1.start + mid), stringarg(s2.s, s2.start, s2.start + maxj));
        hirschberg(stringarg(s1.s, s1.start + mid, s1.finish), stringarg(s2.s, s2.start + maxj, s2.finish));
    }

    string ans;
    string x, y;
};

int main() {
    CommonSubsequence alg{};
}