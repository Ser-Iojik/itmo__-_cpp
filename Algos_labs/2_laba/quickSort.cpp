#include <iostream>
using namespace std;

// Функция перемены местами 2-х элементов
void swap(int* a, int* b) { 
    int t = *a;
    *a = *b;
    *b = t;
} 
   
// Используем разбиение массива и опорный элемент на самом правом месте
// Таким образом мы поставим опорный элемент в такое место, 
// где слева будут все числа меньше него, а справа больше
// int partition (int arr[], int low, int high) {
//     int pivot = arr[high];
//     int i = (low - 1);
   
//     for (int j = low; j <= high- 1; j++) { 
//         // Если текущий элемент меньше опорного, то выполняем i++ и меняем местами i и j
//         if (arr[j] <= pivot) { 
//             i++;
//             swap(&arr[i], &arr[j]); 
//         } 
//     } 
//     swap(&arr[i + 1], &arr[high]); 
//     return (i + 1); 
// } 
   
// void quickSort(int arr[], int low, int high) { 
//     if (low < high) { 
//         // Устанавливаем опорный элемент
//         // int pivot = partition(arr, low, high);
//         int pivot = arr[1]; 
//         cout << arr[0];
//         // Сортируем
//         quickSort(arr, low, pivot - 1); 
//         quickSort(arr, pivot + 1, high); 
//     } 
// } 



void qsort (int *arr, int b, int e)
{
    int l = b, r = e;
    int piv = arr[1];
    while (l <= r)
        {
            while (arr[l] < piv)
                l++;
            while (arr[r] > piv)
                r--;
            if (l <= r)
                swap (arr[l++], arr[r--]);
  }
    if (b < r) {
        qsort (arr, b, r);
    }
    if (e > l) {
        qsort (arr, l, e);
    }
    return(int arr);
}

int main() {
    // freopen("sort.in", "r", stdin);
    // freopen("sort.out", "w", stdout);
    int arr[5] = {1, 2, 3, 4, 5};
    cout << arr[1];
    qsort(arr, 0, 4);
    cout << arr[1];
    for(int i = 0; i < 5; i++) {
        cout << arr[i] << " ";
    }
    return 0;
}