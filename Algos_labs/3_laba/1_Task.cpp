#include <iostream>
using namespace std;

int main() {
    freopen("isheap.in", "r", stdin);
    freopen("isheap.out", "w", stdout);
    int n;
    cin >> n;
    int arr[n];

    for(int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    int x = 0;
    
    for(int i = 1; i <= n; i++) {
        if(1 <= i && i <= n) {
            if(2*i <= n) {
                if(arr[i] <= arr[2*i]) {
                    x += 1;
                }
            }
            if(2*i+1 <= n) {
                if(arr[i] <= arr[2*i+1]) {
                    x += 1;
                }
            }
        }
    }

    if(x == n-1) {
        cout << "YES";
    } else cout << "NO";
}