#include <algorithm>
#include <fstream>
#include <vector>
using namespace std;

const long long INF = 321321321321;

void deikstra(vector<vector<long long>> &g, vector<bool> &visited,
              vector<long long> &dist, long long V, long long start) {
    dist[start - 1] = 0;
    for (long long i = 0; i < V; i++) {
        long long minID = -1;
        for (long long j = 0; j < V; j++) {
            if (!visited[j] && (minID == -1 || dist[j] < dist[minID])) {
                minID = j;
            }
        }
        if (dist[minID] == INF) {
            break;
        }
        visited[minID] = true;

        for (long long j = 0; j < V; j++)
            dist[j] = min(dist[j], dist[minID] + g[minID][j]);
    }
}

int main() {
    ifstream fin("pathmgep.in");
    ofstream fout("pathmgep.out");

    long long V, start, finish;
    fin >> V >> start >> finish;

    vector <long long> dist(V);
    vector <bool> visited(V);
    vector <vector<long long>> g;
    g.assign(V, vector<long long>(V));

    for (long long i = 0; i < V; i++) {
        dist[i] = INF;
    }

    for (long long i = 0; i < V; i++) {
        for (long long j = 0; j < V; j++) {
            fin >> g[i][j];
            if (g[i][j] < 0) {
                g[i][j] = INF;
            }
        }
    }

    deikstra(g, visited, dist, V, start);

    if (dist[finish - 1] >= INF) {
        fout << -1;
    } else {
        fout << dist[finish - 1];
    }

    return 0;
}