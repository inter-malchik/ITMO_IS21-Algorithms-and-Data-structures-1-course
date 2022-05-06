#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin("knapsack.in");
ofstream fout("knapsack.out");

int main() {
    unsigned S, N;
    fin >> S >> N;

    vector<unsigned long long> vals(N+1, 0);
    for (unsigned i = 1; i <= N; i++) {
        fin >> vals[i];
    }

    vector<vector<bool>> bp(N + 1, vector<bool>(S + 1, false));
    bp[0][0] = true;

    for (unsigned i = 1; i <= N; i++)
        for (unsigned w = 0; w <= S; w++)
            bp[i][w] = (vals[i] <= w) ?
                       bp[i - 1][w] || bp[i - 1][w - vals[i]] :
                       bp[i - 1][w];


    unsigned answer = bp[N][0];
    for (unsigned w = 1; w <= S; w++)
        if (bp[N][w])
            answer = (w > answer) ? w : answer;

    fout << answer;
}