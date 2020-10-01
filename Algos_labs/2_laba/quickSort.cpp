#include <iostream>
using namespace std;

// Функция перемены местами 2-х элементов
void swap(int* a, int* b) { 
    int t = *a;
    *a = *b;
    *b = t;
} 
   

int partition (int arr[], int low, int high) {
    int pivot = arr[high];// pivot 
    int i = (low - 1);   
   
    for (int j = low; j <= high- 1; j++) { 
        // Если текущий элемент меньше опорного, то выполняем i++ и меняем местами i и j
        if (arr[j] <= pivot) { 
            i++;
            swap(&arr[i], &arr[j]); 
        } 
    } 
    swap(&arr[i + 1], &arr[high]); 
    return (i + 1); 
} 
   
void quickSort(int arr[], int low, int high) { 
    if (low < high) { 
        int pivot = partition(arr, low, high); 
   
        quickSort(arr, low, pivot - 1); 
        quickSort(arr, pivot + 1, high); 
    } 
} 
   
int main() {
    // freopen("sort.in", "r", stdin);
    // freopen("sort.out", "w", stdout);
    int n;
    cin >> n;
    int arr[n];

    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    quickSort(arr, 0, n-1); 
    for(int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    return 0;
}