#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <unordered_set>

using namespace std;

ifstream fin("hamiltonian.in");
ofstream fout("hamiltonian.out");

struct GraphNode {
    bool seen;
    unsigned index;
};

void DFS_TS(const vector<unordered_set<unsigned>> &adj_list, vector<struct GraphNode> &nodes, struct GraphNode &node, list<unsigned> &ts_result) {
    node.seen = true;
    for (unsigned int found_node: adj_list[node.index])
        if (!nodes[found_node].seen)
            DFS_TS(adj_list, nodes, nodes[found_node], ts_result);
    ts_result.push_front(node.index);
}

int main() {
    unsigned n, m;
    fin >> n >> m;

    if (n == 1) {
        fout << "YES";
        return 0;
    }

    static vector<unordered_set<unsigned>> adj_list(n);
    static vector<struct GraphNode> nodes(n);

    for (unsigned i = 0; i < n; i++) {
        nodes[i] = {false, i};
    }

    for (unsigned i = 0; i < m; i++) {
        unsigned x, y;
        fin >> x >> y;
        x--;
        y--;
        adj_list[x].insert(y);
    }

    list<unsigned> ts_result;

    for (struct GraphNode &node: nodes)
        if (!node.seen)
            DFS_TS(adj_list, nodes, node, ts_result);

    auto it = ts_result.begin();

    for (unsigned i = 1; i<n; i++)
        if (!adj_list[*it].count(*(++it))) {
            fout << "NO";
            return 0;
        }

    fout << "YES";
    fin.close();
    fout.close();
}


