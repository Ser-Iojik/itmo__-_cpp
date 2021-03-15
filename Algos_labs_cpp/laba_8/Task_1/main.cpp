#include <iostream>
#include <fstream>
using namespace std;

const int VMax=100;
int arr[VMax*(VMax-1)][VMax];

int main() {
    fstream in, out;
    in.open("input.txt", ios::in);

    int n, m;
    in >> n;
    in >> m;
    // Ввод матрицы смежности
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            arr[i][j] = 0;
        }
    }

    // Ввод рёбер
    for (int i = 0; i < m; i++) {
        int x, y;
        in >> x >> y;
        arr[x][y] = 1;
    }
    
    in.close();
    out.open("output.txt", ios::out);
    // Вывод матрицы смежности
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            out << arr[i][j] << " ";
        }
        out << endl;
    }
    out.close();

    return 0;
}