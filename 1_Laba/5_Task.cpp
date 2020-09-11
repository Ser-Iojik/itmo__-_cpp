#include <iostream>
using namespace std;

int main() {

    freopen("smallsort.in", "r", stdin);
    freopen("smallsort.out", "w", stdout);

    /* Ввод данных */
    int n, i, j;
    cin >> n;
    int a[n];
    

    for (i = 0; i < n; i++) {
        cin >> a[i];
    }

    /* Сортировка данных */
    for (i = 0; i < n; i++) {

        int a_min = i;

        for (j = i + 1; j < n; j++) {

            if (a[j] < a[a_min]) {
                a_min = j;
            }

        }

        swap(a[i], a[a_min]);

    }

    /* Вывод данных */
    for (i = 0; i < n; i++) {
        cout << a[i] << " ";
    }


    return 0;
}