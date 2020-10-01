#include <iostream>
#include <vector>
 
using namespace std;

int main() {
    freopen("antiqs.in", "r", stdin);
    freopen("antiqs.out", "w", stdout);
    int n;
    vector<int> arr;
    cin >> n;

    // Оставляем в векторе первые n элементов
    arr.resize(n);
    // Заполняем массив arr элементами от 1 до n
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }
    
    for (int i = 2; i < n; i++) {
        swap(arr[i], arr[i/2]);
    }
    // Выводим массив arr элементами от 1 до n
    for (int i = 0; i < n; i++) {
        cout << (arr[i]) << " ";
    }

    return 0;
}