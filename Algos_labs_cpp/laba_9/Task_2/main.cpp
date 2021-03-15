#include <iostream>
#include <vector>
#include <fstream>
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

enum colors {
    WHITE,
    GRAY,
    BLACK
};

bool dfs(vector<colors> &colors, vector <vector<int> > &g, vector<int> &parent, int v, int &cycle_st, int &cycle_end) {
    colors[v] = GRAY;
    for (int i = 0; i < g[v].size(); i++) {
        int to = g[v][i];
        if (colors[to] == WHITE) {
            parent[to] = v;
            if (dfs(colors, g, parent, to, cycle_st, cycle_end)) {
                return true;
            }
        } else if (colors[to] == GRAY) {
            cycle_st = to;
            cycle_end = v;
        }
    }
    colors[v] = BLACK;
    return false;
}

int main() {
    ifstream fin("cycle.in");
    ofstream fout("cycle.out");
    // ifstream fin("cyclein.txt");
    // ofstream fout("cycleout.txt");
    int V, E;
    fin >> V >> E; // V - Vertex, E - Edges

    vector<colors> colors(V);
    vector< vector<int> > g(V);
    vector<int> parent(V);

    for (int i = 0; i < E; i++) {
        int vertex, neighbor;
        fin >> vertex >> neighbor;
        vertex--, neighbor--;
        g[vertex].push_back(neighbor);
    }

    int cycle_st = -1, cycle_end = -1;

    for (int i = 0; i < V; i++) {
        if (dfs(colors, g, parent, i, cycle_st, cycle_end)) {
            break;
        }
    }
    if (cycle_st == -1) {
        fout << "NO" << endl;
    } else {
        fout << "YES" << endl;
        Stack stack(V);
        for (int i = cycle_end; i != cycle_st; i = parent[i]) {
            stack.push(i);
        }
        stack.push(cycle_st);
        while (!stack.isEmpty()) {
            fout << stack.pop() + 1 << " ";
        }
    }

    return 0;
}
