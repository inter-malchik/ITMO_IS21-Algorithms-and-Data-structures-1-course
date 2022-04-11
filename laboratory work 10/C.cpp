#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <unordered_set>
#include <algorithm>

using namespace std;

ifstream fin("spantree3.in");
ofstream fout("spantree3.out");

struct GraphNode {
    unsigned index;
    unsigned color;
};

struct GraphEdge {
    unsigned index_a;
    unsigned index_b;
    unsigned weight;
};

bool compare_edges(struct GraphEdge &e1, struct GraphEdge &e2) {
    return e1.weight < e2.weight;
}

int main() {
    unsigned n, m;
    fin >> n >> m;

    vector<struct GraphNode> nodes(n);
    vector<struct GraphEdge> edges(m);
    vector<unordered_set<unsigned>> colors_sets(n);

    for (unsigned i = 0; i < n; i++) {
        nodes[i] = {i, i};
        colors_sets[i].insert(i);
    }

    for (unsigned j = 0; j < m; j++) {
        unsigned x, y, w;
        fin >> x >> y >> w;
        edges[j] = {--x, --y, w};
    }

    unsigned long long mst_sum = 0;
    sort(edges.begin(), edges.end(), compare_edges);

    for (const struct GraphEdge &edge: edges) {
        unsigned color1 = nodes[edge.index_a].color, color2 = nodes[edge.index_b].color;
        if (color1 != color2) {
            mst_sum += edge.weight;

            if (colors_sets[color1].size() > colors_sets[color2].size()) {
                for (unsigned colored_node: colors_sets[color2]) {
                    nodes[colored_node].color = color1;
                    colors_sets[color1].insert(colored_node);
                }
                colors_sets[color2] = {};
            }
            else {
                for (unsigned colored_node: colors_sets[color1]) {
                    nodes[colored_node].color = color2;
                    colors_sets[color2].insert(colored_node);
                }
                colors_sets[color1] = {};
            }
        }
    }
    fout << mst_sum;
    fin.close();
    fout.close();
}


