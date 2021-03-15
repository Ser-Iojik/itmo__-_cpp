#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

class Stack {
private:
    int *ptr;
    int *initialPtr;
    int capacity_;
public:
    Stack(int capacity) {
        ptr = new int[capacity];
        initialPtr = ptr;
        capacity_ = capacity;
    }

    void push(int elem) {
        if (!isFull()) {
            *ptr++ = elem;
        } else {
            std::cout << "Stack is full!" << std::endl;
        }
    }
    int pop() {
        return *(--ptr);
    }
    bool isEmpty() {
        return (ptr - initialPtr) == 0;
    }
    bool isFull() {
        return (ptr - initialPtr) == capacity_;
    }
};

void dfs(vector<bool> &visited, vector <vector<int>> &g, Stack &topSort, int v) {
    visited[v] = true;
    for (int i = 0; i < g[v].size(); i++) {
        int to = g[v][i];
        if (!visited[to]) {
            dfs(visited, g, topSort, to);
        }
    }
    topSort.push(v);
}

void transDFS(vector<bool> &visited, vector <vector<int>> &transG, vector<int> &group, int v, int nGroup) {
    visited[v] = true;
    group[v] = nGroup;
    for (int i = 0; i < transG[v].size(); i++) {
        int to = transG[v][i];
        if (!visited[to]) {
            transDFS(visited, transG, group, to, nGroup);
        }
    }
}

int main() {
    ifstream fin("cond.in");
    ofstream fout("cond.out");

    int V, E;
    fin >> V >> E;

    vector< vector<int> > g(V);
    vector< vector<int> > transG(V);
    vector<bool> visited(V);
    vector<int> group(V);

    for (int i = 0; i < E; i++) {
        int vertex, neighbor;
        fin >> vertex >> neighbor;
        vertex--, neighbor--;
        g[vertex].push_back(neighbor);
        transG[neighbor].push_back(vertex);
    }

    Stack topSort(V);

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            dfs(visited, g, topSort, i);
        }
    }

    for (int i = 0; i < V; i++) {
        visited[i] = false;
    }
    int nGroup = 1;
    for (int i = 0; i < V; i++) {
        int v = topSort.pop();
        if (!visited[v]) {
            transDFS(visited, transG, group, v, nGroup);
            nGroup++;
        }
    }

    fout << nGroup - 1 << endl;
    for (int i = 0; i < V; i++) {
        fout << group[i] << " ";
    }

    return 0;
}

