#include <iostream>
#include <fstream>
using namespace std;

const int VMax = 100;
int arr[VMax][VMax];

int main() {
    fstream in, out;
    in.open("input.txt", ios::in);


    int n;
    in >> n;
    // Ввод матрицы смежности
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int k;
            in >> k;
            arr[i][j] = k;
        }
    }
    in.close();

    out.open("output.txt", ios::out);
    // Проверка на неориентированность
    int h, g = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (arr[i][j] == arr[j][i]) {
                h = 1;
            } else {
                out << "NO";
                return 0;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j && (arr[i][j] == 1)) {
                out << "NO";
                return 0;
            }
        }
    }

    if (h == 1) {
        out << "YES";
    } else {
        out << "NO";
    }
    
    out.close();

    return 0;
}