#include <iostream>
using namespace std;

int main() {
    // freopen("turtle.in", "r", stdin);
    // freopen("turtle.out", "w", stdout);

    int h, w, i, j, k, g; // кол-во строк // кол-во столбцов
    cin >> h >> w;
    int a[h][w];


    for (i = 1; i <= h; i++) {
        for (j = 1; j <= w; j++) {
            cin >> a[i][j];
        }
    }
    
    // n высота, m ширина в данный момент
    int n = h;
    int m = 1;
    int sum = a[h][1];

    for (i = 0; i < h*w; i++) {

        if (n == 1 && m == w) {
            // cout << "Sum: " << sum << endl;
            return 0;
        }

        if (a[n - 1][m] > a[n][m + 1]) { // Перейти вверх
            sum += a[n - 1][m];
            n -= 1;
        }
        if (a[n][m + 1] > a[n - 1][m]) { // Перейти вправо
            sum += a[n][m + 1];
            m += 1;
        }
        if (n == 1) {
            sum += a[n][m + 1];
            m += 1;
        }
        if (m == w) {
            sum += a[n - 1][m];
            n -= 1;
        }

        if (a[n][m + 1] == a[n - 1][m]) {

            n -= 1;

            if (a[n - 1][m] > a[n][m + 1]) { // Перейти вверх
                k += a[n - 1][m];
            }
            if (a[n][m + 1] > a[n - 1][m]) { // Перейти вправо
                k += a[n][m + 1];
            }
            if (n == 1) {
                k += a[n][m + 1];
            }
            if (m == w) {
                k += a[n][m + 1];
            }
            cout << k << endl;

            n += 1;
            m += 1;

            if (a[n - 1][m] > a[n][m + 1]) { // Перейти вверх
                g += a[n - 1][m];
            }
            if (a[n][m + 1] > a[n - 1][m]) { // Перейти вправо
                g += a[n][m + 1];
            }
            if (n == 1) {
                g += a[n][m + 1];
            }
            if (m == w) {
                g += a[n][m + 1];
            }

            if (k > g) {
                sum += a[n - 1][m];
                n -= 1;
            } else if (k < g) {
                sum += a[n][m + 1];
                m += 1;
            }

        }

    }

}