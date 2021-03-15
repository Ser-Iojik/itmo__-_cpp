#include <iostream>
using namespace std;

int main() {
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);

    int n, m;
    cin >> n;
    cin >> m;
    int arr[n][n];
    // Ввод матрицы смежности
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            arr[i][j] = 0;
        }
    }
    int x, y;
    // Ввод рёбер
    for (int i = 0; i < m; i++) { 
        cin >> x >> y;
        x--;
        y--;
        arr[x][y]++;
    }

    // Проверка на параллельные рёбра
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (arr[i][j] + arr[j][i] > 1) {
                cout << "YES";
                return 0;
            }
        }
    }
    cout << "NO";

    return 0;
}