#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <unordered_set>

using namespace std;

bool cycled = false;
unsigned repeated = 0;
unordered_set<unsigned> seen;
list<unsigned> history;

struct GraphNode {
    bool seen;
    unsigned index;
    int weight;
};

void DFS(const vector<list<unsigned>> &adj_list, vector<struct GraphNode> &nodes, struct GraphNode &node) {
    node.seen = true;

    if (seen.find(node.index) == seen.end())
        seen.insert(node.index);
    else {
        cycled = true;
        repeated = node.index;
    }
    history.push_back(node.index);

    for (unsigned int found_node: adj_list[node.index]) {
        if (not cycled)
            DFS(adj_list, nodes, nodes[found_node]);
        else
            break;
    }
    if (cycled)
        return;

    history.pop_back();
    seen.erase(node.index);
}

int main() {
    ifstream fin("cycle.in");
    ofstream fout("cycle.out");

    unsigned n, m;
    fin >> n >> m;

    static vector<list<unsigned>> adj_list(n);
    static vector<struct GraphNode> nodes(n);

    for (unsigned i = 0; i < n; i++) {
        nodes[i] = {false, i, -1};
    }

    for (unsigned i = 0; i < m; i++) {
        unsigned x, y;
        fin >> x >> y;
        x--;
        y--;
        adj_list[x].push_back(y);
    }

    for (struct GraphNode &node: nodes)
        if (!node.seen && not cycled)
            DFS(adj_list, nodes, node);

    if (!history.empty())
        history.pop_back();

    fout << ((!history.empty()) ? "YES" : "NO") << endl;
    bool seen_key = false;
    if (!history.empty())
        for (const unsigned elem: history) {
            if (!seen_key && elem == repeated)
                seen_key = true;
            if (seen_key)
                fout << elem + 1 << ' ';
        }

    fin.close();
    fout.close();
}
