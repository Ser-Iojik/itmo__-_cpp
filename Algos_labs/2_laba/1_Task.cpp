#include <iostream>
using namespace std;

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int num_l = m - l + 1;
    int num_r = r - m;

    int l_arr[num_l], r_arr[num_r];

    for (i = 0; i < num_l; i++)
        l_arr[i] = arr[l + i];
    for (j = 0; j < num_r; j++)
        r_arr[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < num_l && j < num_r) {
        if (l_arr[i] <= r_arr[j]) {
            arr[k] = l_arr[i];
            i++;
        }
        else {
            arr[k] = r_arr[j];
            j++;
        }
        k++;
    }

    while (i < num_l) {
        arr[k] = l_arr[i];
        i++;
        k++;
    }

    while (j < num_r) {
        arr[k] = r_arr[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

int main() {
    freopen("sort.in", "r", stdin);
    freopen("sort.out", "w", stdout);

    int n;
    cin >> n;
    int arr[n];

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    mergeSort(arr, 0, n - 1);

    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }

    return 0;
}