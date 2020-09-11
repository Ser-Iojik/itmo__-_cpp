#include <iostream>
using namespace std;

int main() {

    // freopen("smallsort.in", "r", stdin);
    // freopen("smallsort.out", "w", stdout);

    /* Ввод данных */
    int n, i, j;
    cin >> n;
    float a[n];
    float k;
    float min_k = 1000001;
    float max_k = 0;

    for (i = 0; i < n; i++) {
        cin >> a[i];
    }

    /* Сортировка данных */
    /* Поиск минимума */
    for (i = 0; i < n; i++) {
        if (a[i] < min_k) {
            min_k = a[i];
        }
    }

    /* Поиск среднего */
    for (i = 0; i < n; i++) {
        k += a[i];
    }
    k / n;

    /* Поиск максимума */
    for (i = 0; i < n; i++) {
        if (a[i] > max_k) {
            max_k = a[i];
        }
    }

    /* Вывод данных */
    // for (i = 0; i < n; i++) {
    //     cout << a[i] << " ";
    // }

    cout << min_k << " " << max_k << endl;

    return 0;
}