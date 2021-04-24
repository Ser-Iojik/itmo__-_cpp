#include <fstream>
#include <vector>
#include <queue>

using namespace std;

struct Edge {
    long long neighbor;
    long long weight;
};

class Compare {
public:
    bool operator() (Edge e1, Edge e2) {
        return e1.weight > e2.weight;
    }
};

long long prim(vector<vector<Edge>> &g, vector<bool> &visited) {
    long long result = 0;
    priority_queue<Edge, vector<Edge>, Compare> queue;
    queue.push(Edge{0, 0});
    while (!queue.empty()) {
        Edge edge = queue.top();
        queue.pop();
        long long fromNeighbor = edge.neighbor;
        long long fromWeight = edge.weight;
        if (!visited[fromNeighbor]) {
            visited[fromNeighbor] = true;
            result += fromWeight;
            for (long long i = 0; i < g[fromNeighbor].size(); i++) {
                long long toNeighbor = g[fromNeighbor][i].neighbor;
                long long toWeight = g[fromNeighbor][i].weight;
                if (!visited[toNeighbor]) {
                    queue.push(Edge{toNeighbor, toWeight});
                }
            }
        }
    }
    return result;
}

int main() {
    ifstream fin("spantree3.in");
    ofstream fout("spantree3.out");

    long long V, E;
    fin >> V >> E;

    vector<bool> visited(V);
    vector<vector<Edge>> g(V);

    for (long long i = 0; i < E; i++) {
        long long from, to, weight;
        fin >> from >> to >> weight;
        g[from - 1].push_back(Edge{to - 1, weight});
        g[to - 1].push_back(Edge{from - 1, weight});
    }

    fout << prim(g, visited) << endl;

    return 0;
}