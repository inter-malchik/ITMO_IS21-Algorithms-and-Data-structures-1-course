#include <iostream>
#include <fstream>
#include <vector>
#include <list>

using namespace std;

struct GraphNode {
    bool seen;
    unsigned index;
    int color;
};

void DFS(const vector<list<unsigned>> &matrix, vector<struct GraphNode> &nodes,
         struct GraphNode &node, int class_num) {
    node.seen = true;
    node.color = class_num;
    for (unsigned int found_node: matrix[node.index]) {
        if (!nodes[found_node].seen)
            DFS(matrix, nodes, nodes[found_node], class_num);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ifstream fin("components.in");
    ofstream fout("components.out");

    unsigned n, m;
    fin >> n >> m;
    static vector<list<unsigned>> matrix(n);
    static vector<struct GraphNode> nodes(n);
    for (unsigned i = 0; i < n; i++) {
        nodes[i] = {false, i, 0};
    }

    for (unsigned i = 0; i < m; i++) {
        unsigned x, y;
        fin >> x >> y;
        x--;
        y--;
        matrix[x].push_back(y);
        matrix[y].push_back(x);
    }

    int classes = 0;
    for (struct GraphNode &node: nodes)
        if (!node.seen)
            DFS(matrix, nodes, node, ++classes);

    fout << classes << endl;
    for (struct GraphNode &node: nodes)
        fout << node.color << ' ';

    fin.close();
    fout.close();
}
