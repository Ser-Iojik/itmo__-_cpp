#include <iostream>
#include <vector>

using namespace std;


void siftDown(vector<int> &array, int i, int n){
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	int ind = i;
	if (l < n && array[i] < array[l])
		ind = l;
	if (r < n && array[ind] < array[r])
		ind = r;
	if (ind != i) {
		swap(array[i], array[ind]);
		siftDown(array, ind, n);
	}
}

void buildHeap(vector<int> &array, int n){
	for (int i = n / 2; i >= 0; i--) {
		siftDown(array, i, n);
	}
}

void heapSort(vector<int> &array, int n){
	buildHeap(array, n);
	int heapSize = n;
	for (int i = 0; i < n - 1; i++) {
		swap(array[0], array[n - 1 - i]);
		heapSize--;
		siftDown(array, 0, heapSize);
	}
}

int main(){
	freopen("sort.in", "r", stdin);
    freopen("sort.out", "w", stdout);

    int n;
    cin >> n;
    vector<int> array(n, 0); 

    for (int i = 0; i < n; i++)
        cin >> array[i];

    heapSort(array, n);
    
    for (int i = 0; i < n; i++)
        cout << array[i] << " ";

    return 0;
}


