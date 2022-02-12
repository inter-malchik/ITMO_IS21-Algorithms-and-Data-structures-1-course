#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>

using namespace std;

struct GraphNode {
    char signature;
    bool seen;
    unsigned a;
    unsigned b;
    int weight;
    string path;
};

struct GraphNodeCoords {
    unsigned x;
    unsigned y;
};

string BFS(const vector<vector<list<struct GraphNodeCoords>>> &matrix, vector<vector<struct GraphNode>> &nodes,
           struct GraphNode &node, int depth) {

    node.seen = true;
    node.weight = depth;
    list<struct GraphNode> list_queue;
    list_queue.push_back(node);

    while (!list_queue.empty()) {
        struct GraphNode current = list_queue.front();
        for (const struct GraphNodeCoords new_coord: matrix[current.a][current.b]) {
            if (!nodes[new_coord.x][new_coord.y].seen) {
                nodes[new_coord.x][new_coord.y].seen = true;
                nodes[new_coord.x][new_coord.y].weight = current.weight + 1;
                list_queue.push_back(nodes[new_coord.x][new_coord.y]);

                char symbol('\0');
                if (new_coord.x - current.a == 1)
                    symbol = 'D';
                else if (new_coord.x - current.a == -1)
                    symbol = 'U';
                else if (new_coord.y - current.b == 1)
                    symbol = 'R';
                else if (new_coord.y - current.b == -1)
                    symbol = 'L';

                if (symbol != '\0')
                    nodes[new_coord.x][new_coord.y].path = nodes[current.a][current.b].path + symbol;

                if (nodes[new_coord.x][new_coord.y].signature == 'T') {
                    return nodes[new_coord.x][new_coord.y].path;
                }
            }
        }
        list_queue.pop_front();
    }
    return "";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ifstream fin("input.txt");
    ofstream fout("output.txt");

    unsigned n, m;
    fin >> n >> m;

    static vector<vector<list<struct GraphNodeCoords>>> matrix(n, vector<list<struct GraphNodeCoords>>(m));
    static vector<vector<struct GraphNode>> nodes_maze(n, vector<struct GraphNode>(m));

    struct GraphNodeCoords start_node{};

    for (unsigned i = 0; i < n; i++)
        for (unsigned j = 0; j < m; j++) {
            char symbol;
            fin >> symbol;
            if (symbol == 'S')
                start_node = {i, j};
            nodes_maze[i][j] = {symbol, false, i, j, 0, {}};
        }

    for (unsigned i = 0; i < n; i++)
        for (unsigned j = 0; j < m; j++) {
            list<struct GraphNode> neighbours;
            if (i > 0 && j > 0 && i < n - 1 && j < m - 1)
                neighbours =
                        {nodes_maze[i - 1][j], nodes_maze[i][j - 1], nodes_maze[i + 1][j], nodes_maze[i][j + 1]};
            else {
                struct GraphNodeCoords
                        up = {i + 1, j}, down = {i - 1, j}, left = {i, j - 1}, right = {i, j + 1};
                list<struct GraphNodeCoords> possible_neighbours = {up, down, left, right};
                for (const struct GraphNodeCoords &pn: possible_neighbours) {
                    if (pn.x >= 0 && pn.y >= 0 && pn.x <= n - 1 && pn.y <= m - 1)
                        neighbours.push_back(nodes_maze[pn.x][pn.y]);
                }

            }

            if (nodes_maze[i][j].signature != '#')
                for (struct GraphNode &neighbour: neighbours) {
                    if (neighbour.signature != '#') {
                        matrix[i][j].push_back({neighbour.a, neighbour.b});
                        matrix[neighbour.a][neighbour.b].push_back({i, j});
                    }
                }
        }

    string result_path = BFS(matrix, nodes_maze, nodes_maze[start_node.x][start_node.y], 0);
    if (!result_path.empty()) {
        fout << result_path.length() << endl;
        fout << result_path << endl;
    }
    else
        fout << "-1";

    fin.close();
    fout.close();
}
