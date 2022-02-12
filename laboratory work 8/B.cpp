#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

bool check_diagonal(const vector<vector<unsigned>> &matrix) {
    for (unsigned i = 0; i < matrix.size(); i++)
        if (matrix[i][i])
            return false;
    return true;
}

bool check_symmetry(const vector<vector<unsigned>> &matrix) {
    for (unsigned i = 0; i < matrix.size(); i++)
        for (unsigned j = i + 1; j < matrix[i].size(); j++)
            if (matrix[i][j] != matrix[j][i])
                return false;
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ifstream fin("input.txt");
    ofstream fout("output.txt");

    unsigned n;
    fin >> n;
    vector<vector<unsigned>> matrix(n);
    for (unsigned i = 0; i < n; i++) {
        matrix[i].resize(n);
        for (unsigned j = 0; j < n; j++)
            fin >> matrix[i][j];
    }

    if (check_symmetry(matrix) && check_diagonal(matrix))
        fout << "YES";
    else
        fout << "NO";

    fin.close();
    fout.close();
}
