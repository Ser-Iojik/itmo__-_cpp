#include <fstream>
#include <vector>
#include <set>

using namespace std;

void deikstra(vector<vector<pair<int, int>>> &g, set<pair<int, int>> &sEdges, vector<int> &dist) {
    dist[0] = 0;
    sEdges.emplace(dist[0], 0);
    while (!sEdges.empty()) {
        int from = sEdges.begin()->second;
        sEdges.erase(sEdges.begin());
        for (auto& edge : g[from]) {
            int to = edge.first;
            int weight = edge.second;
            if (dist[from] + weight < dist[to]) {
                sEdges.erase({dist[to], to});
                dist[to] = dist[from] + weight;
                sEdges.emplace(dist[to], to);
            }
        }
    }
}

int main() {
    ifstream fin("pathbgep.in");
    ofstream fout("pathbgep.out");

    int V, E;
    fin >> V >> E;

    vector<vector<pair<int, int>>> g(V);
    vector<int> dist(V);
    set<pair<int, int>> sEdges;

    const int INF = 321321321;

    for (int i = 0; i < V; i++) {
        dist[i] = INF;
    }

    for (int i = 0; i < E; i++) {
        int from, to, weight;
        fin >> from >> to >> weight;
        g[from - 1].emplace_back(to - 1, weight);
        g[to - 1].emplace_back(from - 1, weight);
    }

    deikstra(g, sEdges, dist);

    for (int weight : dist) {
        fout << weight << " ";
    }

    return 0;
}