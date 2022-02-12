#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ifstream fin("input.txt");
    ofstream fout("output.txt");

    unsigned n, m;
    fin >> n >> m;
    vector<vector<unsigned>> matrix(n);
    for (unsigned i = 0; i < n; i++) {
        matrix[i].resize(n);
        for (unsigned j = 0; j < n; j++)
            matrix[i][j] = 0;
    }

    for (unsigned i = 0; i < m; i++) {
        unsigned x, y;
        fin >> x >> y;
        matrix[x - 1][y - 1] = 1;
    }

    for (unsigned i = 0; i < n; i++) {
        for (unsigned j = 0; j < n; j++)
            fout << matrix[i][j] << ' ';
        fout << endl;
    }

    fin.close();
    fout.close();
}
