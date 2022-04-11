#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>

#define INF INT_MAX
#define START_NODE 0
using namespace std;

struct Npoint {
    int x;
    int y;
    bool seen;
    int min_node_weight;

    Npoint(int abscissa = 0, int ordinate = 0) : x(abscissa), y(ordinate) {}

    int length_to(struct Npoint &other) const {
        return (x - other.x) * (x - other.x) + (y - other.y) * (y - other.y);
    }
};

ifstream fin("spantree.in");
ofstream fout("spantree.out");


int main() {
    int n;
    fin >> n;

    vector<struct Npoint> points(n);

    for (unsigned i = 0; i < n; i++) {
        int abscissa, ordinate;
        fin >> abscissa >> ordinate;
        points[i] = {abscissa, ordinate};
        points[i].seen = false;
        points[i].min_node_weight = INF;
    }

    vector<vector<int>> matrix(n, vector<int>(n));

    for (unsigned i = 0; i < n; i++)
        for (unsigned j = i; j < n; j++)
            matrix[i][j] = matrix[j][i] = points[i].length_to(points[j]);

    points[START_NODE].min_node_weight = 0;

    for (int i = 0; i < n; i++) {
        int min_v = -1;

        for (int j = 0; j < n; j++)
            if (!points[j].seen)
                min_v = (min_v == -1 || points[j].min_node_weight < points[min_v].min_node_weight) ? j : min_v;

        points[min_v].seen = true;
        for (int j = 0; j < n; j++) {
            if (!points[j].seen)
                points[j].min_node_weight = (matrix[j][min_v] < points[j].min_node_weight) ?
                                            matrix[j][min_v] : points[j].min_node_weight;
        }
    }

    double result = 0;
    for (int i = 0; i < n; i++) {
        result += sqrt(points[i].min_node_weight);
    }
    fout.precision(20);
    fout << result;
}
