#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

struct GraphNode {
    unordered_set<unsigned> kids = {};
};

void DP_DFS(unsigned cur_ind, vector<GraphNode> &nodes, vector<vector<unsigned>> &dp) {
     dp[cur_ind][0]=0;
     dp[cur_ind][1]=1;
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
    cin >> N;
    vector<GraphNode> nodes(N, GraphNode());
    vector<vector<unsigned>> dp(N, vector<unsigned>(2,0));

    unsigned root;

    for (unsigned i = 0; i < N; i++) {
        unsigned parent;
        cin >> parent;
        if (!parent) {
            root = i;
            continue;
        }
        nodes[parent - 1].kids.insert(i);
    }

    DP_DFS(root, nodes, dp);
    cout << max(dp[root][0], dp[root][1]);
    return 0;
}