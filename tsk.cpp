#include <iostream>
using namespace std;
 
int main() {
    freopen("graphedges162.txt", "r", stdin);
    // freopen("aplusb.out", "w", stdout);

    int a, b, x;
    int numberOfVertices = 0;
    int numberOfIsolat = 0;
    int arrVersh[1000] = {0};
    int arrIsol[1000];

    x = 0;
    for(int i = 0; i < 1000; i++) {
        arrIsol[i] = x;
        x++;
    }

    while(cin >> a >> b) {

        if (a != b) {
            numberOfVertices++;
        }

        for(int i = 0; i < 1000; i++) {
            if (a == arrIsol[i]) {
                arrIsol[i] = 0;
            }
            if (b == arrIsol[i]) {
                arrIsol[i] = 0;
            }
        }
    }
    cout << "\nNumber of vertices: " << numberOfVertices << "\n\n";

    cout << "Isolat: ";
    for(int i = 0; i < 1000; i++) {
        if (arrIsol[i] > 0) {
            numberOfIsolat++;
            cout << arrIsol[i] << " ";
        }
    }

    cout << "\n\nNumber of isolat: " << numberOfIsolat << "\n\n";

    return 0;
}