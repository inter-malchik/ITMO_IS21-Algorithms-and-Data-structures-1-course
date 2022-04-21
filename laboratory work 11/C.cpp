#include <vector>
#include <iostream>
#include <fstream>
#include <limits>
#include <set>
#include <list>
using namespace std;
#define inf numeric_limits<unsigned long long>::max()

ifstream fin("pathbgep.in");
ofstream fout("pathbgep.out");

struct GraphNode {
    GraphNode(unsigned long long path, int i, bool b) : path_length(path), index(i), seen(b) {};
    unsigned long long path_length;
    unsigned index;
    bool seen;
};

struct GraphEdge {
    GraphEdge(unsigned d, unsigned w) : dest(d), weight(w) {};
    unsigned dest;
    unsigned weight;
};

struct NodeComparator {
    bool operator()(const struct GraphNode &a, const struct GraphNode &b) {
        return a.path_length <= b.path_length;
    }
};

int main() {
    unsigned N, M;
    fin >> N >> M;
    vector<struct GraphNode> nodes(N, GraphNode(inf, 0, false));
    for (unsigned i = 0; i < N; i++)
        nodes[i].index = i;

    vector<list<struct GraphEdge>> edges(N);

    for (unsigned i = 0; i < M; i++) {
        unsigned x, y, w;
        fin >> x >> y >> w;
        x--;
        y--;
        edges[x].push_back({y, w});
        edges[y].push_back({x, w});
    }

    set<struct GraphNode, NodeComparator> queue;
    nodes[0].path_length = 0;
    queue.insert(nodes[0]);

    while (!queue.empty()) {
        unsigned current = (*queue.begin()).index;
        queue.erase(queue.begin());

        if (nodes[current].seen)
            continue;

        for (auto cur_edge: edges[current]) {
            if (!nodes[cur_edge.dest].seen) {
                if (nodes[cur_edge.dest].path_length > nodes[current].path_length + cur_edge.weight) {
                    nodes[cur_edge.dest].path_length = nodes[current].path_length + cur_edge.weight;
                    queue.insert(nodes[cur_edge.dest]);
                }
            }
        }
        nodes[current].seen = true;
    }

    for (unsigned i = 0; i < N; i++)
        if (nodes[i].seen)
            fout << nodes[i].path_length << ' ';
        else
            fout << "-1 ";
}