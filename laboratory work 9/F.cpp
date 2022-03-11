#include <iostream>
#include <fstream>
#include <vector>
#include <list>

using namespace std;

ifstream fin("game.in");
ofstream fout("game.out");

struct GraphNode {
    bool seen;
    unsigned index;
    bool winning;
};

void DFS(const vector<list<unsigned>> &adj_list, vector<struct GraphNode> &nodes, struct GraphNode &node) {
    node.seen = true;
    for (unsigned int found_node: adj_list[node.index])
        if (!nodes[found_node].seen)
            DFS(adj_list, nodes, nodes[found_node]);

    for (unsigned int found_node: adj_list[node.index])
        if (!nodes[found_node].winning) {
            node.winning = true;
            break;
        }
}

int main() {
    unsigned n, m, k;
    fin >> n >> m >> k;

    static vector<list<unsigned>> adj_list(n);
    static vector<struct GraphNode> nodes(n);

    for (unsigned i = 0; i < n; i++) {
        nodes[i] = {false, i, false};
    }

    for (unsigned i = 0; i < m; i++) {
        unsigned x, y;
        fin >> x >> y;
        x--;
        y--;
        adj_list[x].push_back(y);
    }

    DFS(adj_list, nodes, nodes[k - 1]);

    if (nodes[k - 1].winning)
        fout << "First player wins";
    else
        fout << "Second player wins";

    fin.close();
    fout.close();
}


