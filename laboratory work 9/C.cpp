#include <iostream>
#include <fstream>
#include <vector>
#include <list>

using namespace std;

enum BiColor {
    NOT_MARKED = 0,
    COLOR_ONE,
    COLOR_TWO
};

ifstream fin("bipartite.in");
ofstream fout("bipartite.out");

struct GraphNode {
    enum BiColor mark;
    unsigned index;
};

void bipartite_invalid() {
    fout << "NO";
    exit(0);
}

void DFS(vector<list<unsigned>> &adj, vector<struct GraphNode> &nodelist, struct GraphNode &node, enum BiColor color) {
    node.mark = color;
    for (unsigned i: adj[node.index])
        if (!nodelist[i].mark)
            DFS(adj, nodelist, nodelist[i], (color == COLOR_ONE) ? COLOR_TWO : COLOR_ONE);
        else if (nodelist[i].mark == color)
            bipartite_invalid();
}


int main() {
    unsigned n, m;
    fin >> n >> m;

    static vector<list<unsigned>> adj_list(n);
    static vector<struct GraphNode> nodes(n);

    for (unsigned i = 0; i < n; i++) {
        nodes[i] = {NOT_MARKED, i};
    }

    for (unsigned i = 0; i < m; i++) {
        unsigned x, y;
        fin >> x >> y;
        x--;
        y--;

        if (x == y)
            bipartite_invalid();

        adj_list[x].push_back(y);
        adj_list[y].push_back(x);
    }

    for (struct GraphNode &node: nodes)
        if (!node.mark)
            DFS(adj_list, nodes, node, COLOR_ONE);

    fout << "YES";
    
    return 0;
}