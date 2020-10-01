#include <iostream>
using namespace std;

struct CountryPeopleNum {
    string Country;
    string Name;
    int Num;
};

CountryPeopleNum a[100000], result[100000];

void mergeSort(long left, long right) {
    if (left < right) {
        long mid = (left + right) / 2;
        mergeSort(left, mid);
        mergeSort(mid + 1, right);
        long i = 0, j = 0;
        while (left + i <= mid && mid + 1 + j <= right) {
            if (a[left + i].Country > a[mid + 1 + j].Country) {
                result[i + j] = a[mid + 1 + j];
                j++;
            } else {
                result[i + j] = a[left + i];
                i++;
            }
        }
        while (left + i <= mid){
            result[i + j] = a[left + i];
            i++;
        }

        while (mid + 1 + j <= right){
            result[i + j] = a[mid + 1 + j];
            j++;
        }

        for (i = 0; i < right - left + 1; i++) {
            a[left + i] = result[i];
        }
    }
}

int main() {
    freopen("race.in", "r", stdin);
    freopen("race.out", "w", stdout);
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> a[i].Country >> a[i].Name;
        a[i].Num = i;
    }

    mergeSort(0, n - 1);
    string last;

    for (int i = 0; i < n; ++i) {

        if (last != a[i].Country) {
            cout << "=== " << a[i].Country << " ===" << endl;
            last = a[i].Country;
        }

        cout << a[i].Name << endl;
    }

    return 0;
}