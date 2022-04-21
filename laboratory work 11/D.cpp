#include <vector>
#include <iostream>
#include <fstream>
#include <list>
#include <limits>
#include <algorithm>

using namespace std;

#define inf numeric_limits<long long>::max()
#define minus_inf (-5000000000000000000)

ifstream fin("path.in");
ofstream fout("path.out");

struct GraphNode {
    GraphNode(long long path, unsigned ind) : path_length(path), index(ind) {};
    long long path_length;
    unsigned index;
    bool seen = false;
    bool in_cycle = false;
};

struct GraphEdge {
    unsigned a;
    unsigned b;
    long long w;
};

int main() {
    int n, m, s;
    fin >> n >> m >> s;
    s--;
    vector<GraphNode> nodes(n, GraphNode(inf, 0));
    for (unsigned i = 0; i < n; i++)
        nodes[i].index = i;

    nodes[s].path_length = 0;

    vector<list<GraphEdge>> adj(n);

    for (unsigned i = 0; i < m; i++) {
        unsigned x, y;
        long long z;
        fin >> x >> y >> z;
        --x;
        --y;
        if (x == y && z >= 0)
            continue;
        adj[x].push_back({x, y, z});
    }

    list<GraphNode> queue;
    queue.push_back(nodes[s]);
    while (!queue.empty()) {
        GraphNode nd = queue.front();
        queue.pop_front();
        nodes[nd.index].seen = true;
        for (GraphEdge ed: adj[nd.index])
            if (!nodes[ed.b].seen) {
                queue.push_back(nodes[ed.b]);
            }
    }

    for (unsigned _ = 1; _ <= n - 1; _++) {
        bool changed = false;
        for (list<GraphEdge> &edgelist_cur: adj)
            for (GraphEdge &e: edgelist_cur)
                if (nodes[e.a].path_length != inf)
                    if (nodes[e.b].path_length > nodes[e.a].path_length + e.w) {
                        nodes[e.b].path_length = (nodes[e.a].path_length + e.w > minus_inf) ?
                                nodes[e.a].path_length +e.w : minus_inf;
                        changed = true;
                    }
        if (!changed)
            break;
    }

    for (list<GraphEdge> &edgelist_cur: adj)
        for (GraphEdge &e: edgelist_cur)
            if (nodes[e.a].path_length != inf)
                if (nodes[e.b].path_length > nodes[e.a].path_length + e.w) {
                    nodes[e.b].path_length = (nodes[e.a].path_length + e.w > minus_inf) ?
                            nodes[e.a].path_length + e.w: minus_inf;

                    queue.push_back(nodes[e.b]);
                    while (!queue.empty()) {
                        GraphNode nd = queue.front();
                        queue.pop_front();
                        nodes[nd.index].in_cycle = true;
                        for (GraphEdge ed: adj[nd.index])
                            if (!nodes[ed.b].in_cycle)
                                queue.push_back(nodes[ed.b]);
                    }
                }

    for (GraphNode &nd: nodes) {
        if (!nd.seen || nd.path_length == inf)
            fout << "*" << endl;
        else if (nd.in_cycle)
            fout << "-" << endl;
        else
            fout << nd.path_length << endl;
    }
}