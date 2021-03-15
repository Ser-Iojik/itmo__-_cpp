#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
using namespace std;
 
void bfs(vector< vector<int> > &g, vector<int> &dist, vector<bool> &visited, int start) {
    // Создаём очередь q и пушим туда начальную вершину 0, сразу помечаем её пройденной и что её расстояние 0
    queue<int> q;
    q.push(start);
    dist[start] = 0;
    visited[start] = true;

    // До тех пор пока очередь не опустеет проходим по каждой вершине, отмечаем её посещённой и прибавляем единицу расстояния
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int i = 0; i < g[v].size(); i++) {
            if (!visited[g[v][i]]) {
                dist[g[v][i]] = dist[v] + 1;
                visited[g[v][i]] = true;
                q.push(g[v][i]);
            }
        }
    }
}

int main() {
    fstream in, out;
    in.open("pathbge1.in", ios::in);

    int n, m, x, y;
    in >> n >> m;

    vector<vector<int>> g(n);
    vector<int> dist(n);
    vector<bool> visited(n);
 
    for (int i = 0; i < m; i++) {
        in >> x >> y;
        x--;
        y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    bfs(g, dist, visited, 0);

    out.open("pathbge1.out", ios::out);

    for (int i = 0; i < dist.size(); i++) {
        out << dist[i] << " ";
    }
    out.close();

    return 0;
}