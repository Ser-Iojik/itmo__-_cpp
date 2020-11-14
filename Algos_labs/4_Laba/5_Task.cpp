#include <iostream>
#include <fstream>
using namespace std;

int arr[100000];

int left_search(int x, int N) {
	int left = -1; // Right = 1 left = 0, Условие не срабатывает, Нулевой элемент массива
	int right = N;
	int mid;
	while (right - left > 1) { 
		mid = (right + left) / 2;
		if (arr[mid] >= x) { // Если средний элемент больше искомого значит искомый находится слева от среднего
			right = mid;
		}
		else if (arr[mid] < x) {
			left = mid;
		}
	}
	if (arr[right] == x) return right + 1;
		return -1;
}

int right_search(int x, int N) {
	int left = -1;
	int right = N;
	int mid;
	while (right - left > 1) {
		mid = (right + left) / 2;
		if (arr[mid] > x) {
			right = mid;
			continue;
		}
		else if (arr[mid] <= x) {
			left = mid;
			continue;
		}
	}
	if (arr[left] == x) return left + 1;
		return -1;
}

int main() {
    ifstream fin("binsearch.in");
    ofstream fout("binsearch.out");

	int N, M;
	fin >> N;
	for (int i = 0; i < N; i++) fin >> arr[i];// Вводим массив
	fin >> M;
	int x;
	for (int i = 0; i < M; i++) {
		fin >> x;
		fout << left_search(x, N) << ' ' << right_search(x, N) << '\n';
	}
    return 0;
}