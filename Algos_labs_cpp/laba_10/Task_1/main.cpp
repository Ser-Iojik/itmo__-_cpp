#include <fstream>
#include <vector>
#include <iostream>
 
using namespace std;
   
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, m;
    int v, e;
    cin >> n >> m;
    vector<int> Graph;
    Graph.resize(n);
  
    while (m != 0) { 
        cin >> v >> e;
        Graph[v - 1]++;
		Graph[e - 1]++;
        m--;
    }
    for (int i = 0; i < Graph.size(); i++) {
        cout << Graph[i] << " ";
    }
    return 0;
}
