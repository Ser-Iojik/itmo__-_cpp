#include <iostream>
using namespace std;

int main() {
    // freopen("turtle.in", "r", stdin);
    // freopen("turtle.out", "w", stdout);

    // Задание переменных и ввод данных
	const int max = 1001;
	int h, w, i, j;
	int a[max][2] = {};
	int p = 0, k = 0;

	cin >> h >> w;

	for (i = 0; i < h; i++) {
		p = i % 2;
        // Ввод значений верхней строки таблицы
		for (j = w ; j > 0; j--) {
		    cin >> a[j][p];
		}

		if (i == 0) {
			for (k = 1; k <= w; k++) {
				a[k][0] += a[k - 1][0];
            }
		}

		else {
			for (k = 1; k <= w; k++) {
				if (a[k][1 - p] > a[k - 1][p]) {
					a[k][p] += a[k][1 - p];
                }
				else {
					a[k][p] += a[k - 1][p];
                }
            }
        }
		
	}

	cout << a[w][p];

	return 0;
}