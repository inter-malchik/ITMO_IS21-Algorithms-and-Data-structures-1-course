#include <iostream>
#include <fstream>
#include <vector>
#include <list>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

struct GraphNode {
    bool seen;
    unsigned index;
    unsigned degree;
};

int main() {
    unsigned n, m;
    fin >> n >> m;

    // static vector<list<unsigned>> adj_list(n);
    static vector<struct GraphNode> nodes(n);

    for (unsigned i = 0; i < n; i++) {
        nodes[i] = {false, i, 0};
    }

    for (unsigned i = 0; i < m; i++) {
        unsigned x, y;
        fin >> x >> y;
        x--;
        y--;
        // adj_list[x].push_back(y);
        // adj_list[y].push_back(x);
        nodes[x].degree++;
        nodes[y].degree++;
    }

    for (auto &node: nodes)
        fout << node.degree << ' ';

    fin.close();
    fout.close();
}


