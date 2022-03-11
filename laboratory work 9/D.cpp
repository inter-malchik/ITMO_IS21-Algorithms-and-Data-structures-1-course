#include <iostream>
#include <fstream>
#include <vector>
#include <list>

using namespace std;

ifstream fin("cond.in");
ofstream fout("cond.out");

struct GraphNode {
    bool seen;
    unsigned index;
    int comp_color;
};

list<unsigned> ts_result;

void DFS_TS(const vector<list<unsigned>> &adj_list, vector<struct GraphNode> &nodes, struct GraphNode &node) {
    node.seen = true;
    for (unsigned int found_node: adj_list[node.index])
        if (!nodes[found_node].seen)
            DFS_TS(adj_list, nodes, nodes[found_node]);
    ts_result.push_front(node.index);
}

void DFS_COND(const vector<list<unsigned>> &adj_list, vector<struct GraphNode> &nodes, struct GraphNode &node, int comp_n) {
    node.comp_color = comp_n;
    for (unsigned int found_node: adj_list[node.index])
        if (nodes[found_node].comp_color == -1)
            DFS_COND(adj_list, nodes, nodes[found_node], comp_n);
}


int main() {
    unsigned n, m;
    fin >> n >> m;

    static vector<list<unsigned>> adj_list(n);
    static vector<list<unsigned>> adj_list_reversed(n);
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
        adj_list_reversed[y].push_back(x);
    }

    for (struct GraphNode &node: nodes)
        if (!node.seen)
            DFS_TS(adj_list, nodes, node);

    int comp = 0;
    for (const unsigned &i: ts_result)
        if (nodes[i].comp_color == -1)
            DFS_COND(adj_list_reversed, nodes, nodes[i], ++comp);


    fout << comp << endl;
    for (struct GraphNode &node: nodes)
        fout << node.comp_color << ' ';

    fin.close();
    fout.close();
}


