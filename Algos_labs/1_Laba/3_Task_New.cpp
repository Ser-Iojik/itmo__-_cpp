#include <iostream>
using namespace std;

int main(void) {
    // const int max = 1001;
    int i, j, h, w;
    // int a[max][2] = {};
    int m = 0, n = 0;
    cin >> h >> w;
    int a[h][w];

    for (i = 1; i <= h; i++) {
        for (j = 1; j <= w; j++) {
            cin >> a[i][j];
        }

        for (j = w; j >= 1; j--) {
            n += a[i][j];
        }
    }

    for (i = 1; i <= w; i++) {
        cout << a[1][i];
    }

}