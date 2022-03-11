#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <cstdlib>

using namespace std;

list<unsigned> history;

ifstream fin("topsort.in");
ofstream fout("topsort.out");

int time_visit = 0;

struct GraphNode {
    bool seen;
    unsigned index;
    int weight;
};

void topsort_cyclic_error() {
    fout << -1;
    exit(0);
}

void DFS(const vector<list<unsigned>> &adj_list, vector<struct GraphNode> &nodes, struct GraphNode &node) {
    time_visit += 1;
    node.seen = true;
    for (unsigned int found_node: adj_list[node.index]) {
        if (!nodes[found_node].seen)
            DFS(adj_list, nodes, nodes[found_node]);
        else if (nodes[found_node].weight == -1)
            topsort_cyclic_error();
    }
    time_visit += 1;
    node.weight = time_visit;
    history.push_front(node.index);

}


int main() {
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
        if (!node.seen)
            DFS(adj_list, nodes, node);


    for (const unsigned elem: history)
        fout << elem + 1 << ' ';


    fin.close();
    fout.close();
}


