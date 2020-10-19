#include <iostream>
#include <vector>
#include <string>

using namespace std;


void radixsort(vector<string>& array, int m, int k) {

    for (int i = m - 1; i >= m - k; i--) {

        vector<int> alph(26, 0);
        int x = array.size();
        for (int j = 0; j < x; j++) {
            alph[array[j][i] - 'a']++;
        }

        int temp, count = 0;
        x = alph.size();
        for (int j = 0; j < x; j++) {
            temp = alph[j];
            alph[j] = count;
            count += temp;
        }

        vector<string> result(array.size(), "");
        x = array.size();
        for (int j = 0; j < x; j++) {
            result[ alph[array[j][i] - 'a'] ] = array[j];
            alph[array[j][i] - 'a']++;
        }
        array = result;
        alph.clear();
        result.clear();
    }
}

int main(){
    // freopen("radixsort.in", "r", stdin);
    // freopen("radixsort.out", "w", stdout);

    int n, m, k;
    cin >> n >> m >> k;
    vector<string> array(n, "");
    for (int i = 0; i < n; i++) {
        cin >> array[i];
    }

    radixsort(array, m, k);

    for (int i = 0; i < n; i++) {
        cout << array[i] << endl;
    }
    
    return 0;
}
