#include <vector>
#include <iostream>
#include <fstream>
#include <limits>
#include <set>

using namespace std;
#define inf numeric_limits<unsigned long long>::max()

ifstream fin("pathmgep.in");
ofstream fout("pathmgep.out");

struct GraphNode {
    GraphNode(unsigned long long path, int i, bool b) : path_length(path), index(i), seen(b) {};
    unsigned long long path_length;
    unsigned index;
    bool seen;
};

struct NodeComparator {
    bool operator()(const struct GraphNode &a, const struct GraphNode &b) {
        return a.path_length <= b.path_length;
    }
};

int main() {
    unsigned N, S, F;
    fin >> N >> S >> F;
    vector<vector<int>> matrix(N, vector<int>(N, -1));
    vector<struct GraphNode> nodes(N, GraphNode(inf, 0, false));
    for (unsigned i = 0; i < N; i++) {
        nodes[i].index = i;
        for (unsigned j = 0; j < N; j++)
            fin >> matrix[i][j];
    }
    S--;
    F--;

    set<struct GraphNode, NodeComparator> queue;
    nodes[S].path_length = 0;
    queue.insert(nodes[S]);

    while (!queue.empty()) {
        unsigned current = (*queue.begin()).index;
        queue.erase(queue.begin());

        if (nodes[current].seen)
            continue;

        for (unsigned j = 0; j < N; j++) {
            if (!nodes[j].seen && matrix[current][j] != -1) {
                if (nodes[j].path_length > nodes[current].path_length + matrix[current][j]) {
                    nodes[j].path_length = nodes[current].path_length + matrix[current][j];
                    queue.insert(nodes[j]);
                }
            }
        }

        if (current == F) {
            fout << nodes[current].path_length;
            exit(0);
        }

        nodes[current].seen = true;
    }

    if (nodes[F].seen)
        fout << nodes[F].path_length;
    else
        fout << "-1";
}