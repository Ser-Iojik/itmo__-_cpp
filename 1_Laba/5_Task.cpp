#include <iostream>
using namespace std;

int main() {

    freopen("sortland.in", "r", stdin);
    freopen("sortland.out", "w", stdout);

    /* Ввод данных */

    int n, i, j;
    cin >> n;
    float a[n];
    float b[n];

    for (i = 0; i < n; i++) {
        cin >> a[i];
        b[i] = a[i];
    }

    /* Сортировка данных */

    for (i = 0; i < n; i++) {

        int b_min = i;

        for (j = i + 1; j < n; j++) {
            if (b[j] < b[b_min]) {
                b_min = j;
            }
        }

        swap(b[i], b[b_min]);
    }

    float one;
    float two;
    float three;

    one = b[0];
    two = b[n/2];
    three = b[n-1];

    for (i = 0; i < n; i++) {
        if (one == a[i]) {
            cout << i+1 << " ";
        }
    }

    for (i = 0; i < n; i++) {
        if (two == a[i]) {
            cout << i+1 << " ";
        }
    }

    for (i = 0; i < n; i++) {
        if (three == a[i]) {
            cout << i+1 << " ";
        }
    }

    return 0;
}