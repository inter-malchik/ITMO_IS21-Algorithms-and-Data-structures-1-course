#include <iostream>
#include <fstream>

using namespace std;
ifstream fin("knight2.in");
ofstream fout("knight2.out");

static int n, m;

int knight2(int x, int y) {
    if (x == 0 && y == 0)
        return 1;
    else if (x < 0 || y < 0 || x>=n || y >= m)
        return 0;
    else
        return knight2(x + 1, y - 2) + knight2(x - 1, y - 2) + knight2(x - 2, y - 1) + knight2(x - 2, y + 1);
}

int main() {
    fin >> n >> m;
    fout << knight2(n - 1, m - 1);
}