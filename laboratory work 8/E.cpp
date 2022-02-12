#include <iostream>
#include <fstream>
#include <vector>
#include <list>

using namespace std;

struct GraphNode {
    bool seen;
    unsigned index;
    int weight;
};

void BFS(const vector<list<unsigned>> &matrix, vector<struct GraphNode> &nodes,
         struct GraphNode &node, int depth) {
    node.seen = true;
    node.weight = depth;
    list<struct GraphNode> list_queue;
    list_queue.push_back(node);

    while (!list_queue.empty()) {
        struct GraphNode current = list_queue.front();
        for (const unsigned newind: matrix[current.index]){
            if (!nodes[newind].seen) {
                nodes[newind].seen = true;
                nodes[newind].weight = current.weight + 1;
                list_queue.push_back(nodes[newind]);
            }
        }
        list_queue.pop_front();
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ifstream fin("pathbge1.in");
    ofstream fout("pathbge1.out");

    unsigned n, m;
    fin >> n >> m;
    static vector<list<unsigned>> matrix(n);
    static vector<struct GraphNode> nodes(n);
    for (unsigned i = 0; i < n; i++) {
        nodes[i] = {false, i, -1};
    }

    for (unsigned i = 0; i < m; i++) {
        unsigned x, y;
        fin >> x >> y;
        x--;
        y--;
        matrix[x].push_back(y);
        matrix[y].push_back(x);
    }

    BFS(matrix, nodes, nodes[0], 0);

    for (struct GraphNode &node: nodes)
        fout << node.weight << ' ';

    fin.close();
    fout.close();
}
