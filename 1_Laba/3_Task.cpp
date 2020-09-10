#include <iostream>
using namespace std;

int main() {
    int h; // кол-во строк
    int w; // кол-во столбцов

    // freopen("turtle.in", "r", stdin);
    // freopen("turtle.out", "w", stdout);

    cin >> h >> w;
    // int a[h][w];
    // cout << a;
    int i, j;
    for(i = h; i > 0; i--) {
        for(j = w; j > 0; j--) {
            cin >> w;
        }
    }

    return 0;
}