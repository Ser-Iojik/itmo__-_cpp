#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

enum color {
    BLACK,
    WHITE
};

color reverseColor(color color) {
    if (color == BLACK) {
        return WHITE;
    }
    return BLACK;
}

void dfs(vector<color> &colors, vector <vector<int> > &g, int v, color color, bool &flag) {
    colors[v] = color;
    for (int i = 0; i < g[v].size(); i++) {
        int to = g[v][i];
        if (colors[to] == WHITE) {
            dfs(colors, g, to, reverseColor(color), flag);
        } else if (colors[to] == color) {
            flag = false;
            return;
        }
    }
}

int main() {
    ifstream fin("bipartite.in");
    ofstream fout("bipartite.out");
    // ifstream fin("bipartitein.txt");
    // ofstream fout("bipartiteout.txt");

    int V, E;
    fin >> V >> E;

    vector<vector<int>> g(V);
    vector<color> colors(V, WHITE);
    bool flag = true;

    for (int i = 0; i < E; i++) {
        int vertex, neighbor;
        fin >> vertex >> neighbor;
        vertex--, neighbor--;
        g[vertex].push_back(neighbor);
        g[neighbor].push_back(vertex);
    }
    for (int i = 0; i < V; i++) {
        if (colors[i] == WHITE) {
            dfs(colors, g, i, WHITE, flag);
            if (!flag) {
                fout << "NO" << endl;
                return 0;
            }
        }
    }
    fout << "YES" << endl;
    return 0;
}
