#include <algorithm>
#include <fstream>
#include <vector>
using namespace std;

// Данный алгоритм находит кратайшие расстояния между всеми парами вершин за O(V^3).
// Описание алгоритма: фиксируем вершину k, затем перебираем всевозможные пары вершин (i, j)
// и если a_ij > a_ik + a_kj, то делаем a_ij = a_ik + a_kj.

// Алгоритм Флойда-Уоршелла за O(V^3)
void floydWarshall(vector<vector<int>> &g, int V) {
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
            }
        }
    }
}

int main() {
    ifstream fin("pathsg.in");
    ofstream fout("pathsg.out");

    int V, E;
    fin >> V >> E;

    vector <vector<int>> g;
    g.assign(V, vector <int>(V, 321321321));

    for (int i = 0; i < E; i++) {
        int from, to, weight;
        fin >> from >> to >> weight;
        g[from - 1][to - 1] = weight;
    }

    floydWarshall(g, V);

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i == j) {
                g[i][j] = 0;
            }
            fout << g[i][j] << " ";
        }
        fout << "\n";
    }
    return 0;
}