#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

ifstream fin("selectw.in");
ofstream fout("selectw.out");

struct GraphNode {
    long long weight{};
    unordered_set<unsigned> kids = {};
};

void DP_DFS(unsigned cur_ind, vector<GraphNode> &nodes, vector<vector<long long>> &dp) {
    dp[cur_ind][0] = 0;
    dp[cur_ind][1] = nodes[cur_ind].weight;
    for (unsigned kid: nodes[cur_ind].kids) {
        DP_DFS(kid, nodes, dp);
    }
    for (unsigned kid: nodes[cur_ind].kids) {
        dp[cur_ind][1] += dp[kid][0];
        dp[cur_ind][0] += max(dp[kid][0], dp[kid][1]);
    }
}

int main() {
    unsigned N;
    fin >> N;
    vector<GraphNode> nodes(N, GraphNode());
    vector<vector<long long>> dp(N, vector<long long>(2, 0));

    unsigned root;

    for (unsigned i = 0; i < N; i++) {
        unsigned parent;
        long long weight;
        fin >> parent >> weight;
        nodes[i].weight = weight;
        if (!parent) {
            root = i;
            continue;
        }
        nodes[parent - 1].kids.insert(i);
    }

    DP_DFS(root, nodes, dp);
    fout << max(dp[root][0], dp[root][1]);
    return 0;
}