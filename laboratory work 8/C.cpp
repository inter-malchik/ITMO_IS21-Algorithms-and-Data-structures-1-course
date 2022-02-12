#include <iostream>
#include <fstream>
#include <vector>
#include <list>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);


    ifstream fin("input.txt");
    ofstream fout("output.txt");

    unsigned n, m;
    fin >> n >> m;
    vector<list<unsigned>> adj_list(n);
    bool answer = false;

    for (unsigned i = 0; i < m; i++) {
        unsigned x, y;
        fin >> x >> y;
        for (const unsigned &elem: adj_list[x - 1]) {
            if (elem == y - 1) {
                answer = true;
                break;
            }
        }
        if (answer)
            break;
        adj_list[x - 1].push_back(y - 1);
        if (x != y)
            adj_list[y - 1].push_back(x - 1);
    }

    fout << ((answer) ? "YES" : "NO");

    fin.close();
    fout.close();
}
