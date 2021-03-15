#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
 
void dfs(vector<bool> &visited, vector <vector<int> > &g, int v, vector<int> &group, int ngroup) {
    visited[v] = true; // Отмечаем, что данную вершину уже прошли
    group[v] = ngroup; // Записываем число >1, Означающее принадлежность к компоненте связности
    for (int i = 0; i < g[v].size(); i++) { // Обходим каждую из вершин
        int to = g[v][i]; 
        if (!visited[to]) {
            dfs(visited, g, to, group, ngroup); // Рекурсивно проходим по каждой смежной вершине
        }                                       // и записываем её компоненту и отмечаем пройденной
    }
}

int main() {
    fstream in, out;
    in.open("components.in", ios::in);
 
    int n, m, x, y;
    in >> n >> m;
 
    vector<vector<int>> g; // Массив рёбер
    vector<bool> visited; // Посещённые вершины
    vector<int> group; // Отношение вершины к компоненте связности
 
    g.resize(n);
    visited.resize(n);
    group.resize(n);
 
    for (int i = 0; i < m; i++) {
        in >> x >> y;
        x--;
        y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    in.close();
 
    // Обходим каждую вершину графа и записываем её принадлежность к компоненте связности
    int count = 0;
    int nGroup = 1;
    for (int i = 0; i < g.size(); i++) {
        if (!visited[i]) {
            dfs(visited, g, i, group, nGroup);
            nGroup++;
            count++;
        }
    }
 
    out.open("components.out", ios::out);
 
    out << count << endl;
    for (int i = 0; i < group.size(); i++) {
        out << group[i] << " ";
    }
    out.close();
 
    return 0;
}