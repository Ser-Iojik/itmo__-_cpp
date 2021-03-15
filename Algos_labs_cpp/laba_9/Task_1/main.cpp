#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
using namespace std;

enum colors {
    WHITE,
    GRAY,
    BLACK
};

void dfs(vector<colors> &colors, vector <vector<int> > &g, vector<int> &Stack, bool &flag, int v) {
    colors[v] = GRAY;
    for (int i = 0; i < g[v].size(); i++) {
        int to = g[v][i];
        if (colors[to] == WHITE) {
            dfs(colors, g, Stack, flag, to);
        } else if (colors[to] == GRAY) {
            flag = false;
            return;
        }
    }
    colors[v] = BLACK;
    Stack.push_back(v);
}

int main() {
    ifstream fin("topsort.in");
    ofstream fout("topsort.out");

    int V, E;
    fin >> V >> E; // V - Vertex, E - Edges

    vector<colors> colors(V);
    vector<vector<int>> g(V);
    vector<int> Stack(V);

    for (int i = 0; i < E; i++) {
        int vertex, neighbor;
        fin >> vertex >> neighbor;
        vertex--, neighbor--;
        g[vertex].push_back(neighbor);
    }

    bool flag = true;

    for (int i = 0; i < V; i++) {
        if (!colors[i]) {
            dfs(colors, g, Stack, flag, i);
        }
    }

    int h = Stack.size();
    int j = h/2;

    if (flag) {
        while (h > j) {
            fout << Stack[h-1] + 1 << " ";
            h-=1;
        }
    } else {
        fout << -1;
    }
    return 0;
}
