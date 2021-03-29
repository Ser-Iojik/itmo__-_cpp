#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <limits>

using namespace std;

struct point {
    int x;
    int y;
};

int distance(point a, point b) {
    return ((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

void prim(int start, int V, vector<vector<int>> &g, vector<bool> &visited, vector<double> &dist) {
    dist[start] = 0;
    for (int i = 0; i < V; i++) {
        int minID = -1;
        for (int j = 0; j < V; j++) {
            if (!visited[j] && (minID == -1 || dist[j] < dist[minID]))
                minID = j;
        }

        visited[minID] = true;

        for (int j = 0; j < V; j++) {
            if (!visited[j] && g[minID][j] < dist[j] && minID != j)
                dist[j] = g[minID][j];
        }
    }
}

int main()
{
    ifstream fin("spantree.in");
    ofstream fout("spantree.out");

    int V;
    fin >> V;

    vector<point> points(V);
    vector<bool> visited(V);
    vector<double> dist(V);
    vector< vector<int> > g;
    g.assign(V, vector<int>(V));

    for (int i = 0; i < V; i++) {
        dist[i] = numeric_limits<int>::max();
    }

    for (int i = 0; i < V; i++) {
        fin >> points[i].x >> points[i].y;
    }

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            g[i][j] = distance(points[i], points[j]);
        }
    }

    prim(0, V, g, visited, dist);

    double result = 0;

    for (int i = 0; i < V; i++) {
        result += sqrt(dist[i]);
    }

    fout << setprecision(10) << result << "\n";
    return 0;
}