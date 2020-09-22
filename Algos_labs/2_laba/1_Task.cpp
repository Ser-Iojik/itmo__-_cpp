#include <iostream>
using namespace std;

int main() {
    freopen("sort.in", "r", stdin);
    freopen("sort.out", "w", stdout);
    long n, a_min;
    int i, j, k;
    cin >> n;
    long a[n];

    for (i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (i = 0; i < n; i++) {
        a_min = a[i];
        for (j = i + 1; j < n; j++) {
            if (a[j] < a_min) {
                k = a[j];
                a[j] = a_min;
                a_min = k;
            }
        }
        a[i] = a_min;
    }
    for (i = 0; i < n; i++) {
        cout << a[i] << " ";
    }

    return 0;
}