#include <iostream>
#include <vector>

using namespace std;
# define base ((long long) 1000000000)

long long pal(unsigned i, unsigned j, vector<unsigned> &sequence, vector<vector<long long>> &matrix,
              vector<vector<bool>> &seen) {
    if (i < 0 || j < 0 || i > j || i > sequence.size() || j > sequence.size())
        return 0;
    if (i == j)
        return 1;
    if (!seen[i][j]) {
        if (sequence[i] != sequence[j])
            matrix[i][j] = base + (pal(i, j - 1, sequence, matrix, seen) +
                                   pal(i + 1, j, sequence, matrix, seen) -
                                   pal(i + 1, j - 1, sequence, matrix, seen)) % base;
        else
            matrix[i][j] = pal(i, j - 1, sequence, matrix, seen) + pal(i + 1, j, sequence, matrix, seen) + 1;
        seen[i][j] = true;
    }
    return matrix[i][j] = matrix[i][j] % base;

}

int main() {
    unsigned N;
    cin >> N;
    vector<unsigned> colors(N);
    for (unsigned i = 0; i < N; i++) {
        cin >> colors[i];
    }
    vector<vector<long long>> amts(N, vector<long long>(N, 0));
    vector<vector<bool>> seen(N, vector<bool>(N, false));

    pal(0, N - 1, colors, amts, seen) % base;

    cout << amts[0][amts.size() - 1];
    return 0;
}