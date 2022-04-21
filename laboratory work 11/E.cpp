#include <vector>
#include <iostream>
#include <fstream>
#include <list>

using namespace std;
#define inf 1000000000

ifstream fin("negcycle.in");
ofstream fout("negcycle.out");

struct GraphNode {
    GraphNode(int path, int ind) : path_length(path), index(ind) {};
    int path_length;
    unsigned index;
    int parent = -1;
};

struct GraphEdge {
    unsigned i;
    unsigned j;
    int w;
};

int main() {
    int n;
    fin >> n;

    vector<GraphEdge> edges;
    for (unsigned i = 0; i < n; i++)
        for (unsigned j = 0; j < n; j++) {
            int w;
            fin >> w;
            if (w < inf)
                edges.push_back({i, j, w});
        }

    vector<GraphNode> nodes(n, GraphNode(inf, 0));
    for (unsigned i = 0; i < n; i++) {
        nodes[i].index = i;
    }

    for (unsigned s = 0; s < n; s++) {
        for (unsigned i = 0; i < n; i++) {
            nodes[i].path_length = inf;
        }

        nodes[s].path_length = 0;

        for (unsigned _ = 1; _ <= n - 1; _++) {
            bool changed = false;
            for (GraphEdge e: edges)
                if (nodes[e.i].path_length < inf)
                    if (nodes[e.j].path_length > nodes[e.i].path_length + e.w) {
                        nodes[e.j].path_length = nodes[e.i].path_length + e.w;
                        nodes[e.j].parent = (int) e.i;
                        changed = true;
                    }
            if (!changed)
                break;
        }
        int x = -1;
        for (GraphEdge e: edges)
            if (nodes[e.i].path_length < inf)
                if (nodes[e.j].path_length > nodes[e.i].path_length + e.w) {
                    nodes[e.j].path_length = nodes[e.i].path_length + e.w;
                    x = e.j;
                }

        if (x != -1) {
            fout << "YES" << endl;
            int init = x;
            int cur = x;

            if (nodes[cur].parent == -1) {
                fout << 2 << endl;
                fout << cur + 1 << ' ' << cur + 1 << endl;
                exit(0);
            }

            for (int i = 0; i < n; ++i)
                cur = init = nodes[cur].parent;

            list<int> cycle;

            cycle.push_back(cur);
            cur = nodes[cur].parent;

            while (cur != init) {
                cycle.push_back(cur);
                cur = nodes[cur].parent;
            }
            cycle.push_back(init);
            fout << cycle.size() << endl;
            cycle.reverse();
            for (auto nd: cycle)
                fout << nd + 1 << ' ';
            exit(0);
        }
    }
    fout << "NO";
}