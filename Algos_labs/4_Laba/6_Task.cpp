#include <vector>
#include <fstream>
#include <iostream>
using namespace std;
/*
короче
мы при помощи бинпоиска подбираем значение a[1]
сначала берём максимально возможное и от него начинаем строить вниз гирлянду,
если зашла в минус - понимаем, что всё говно,
выбираем новое значение для райт, а если не заходит в минус - понимаем,
что можем подобрать лучше и начинаем тыкать палкой лефт,
и так подбираем крутанское значение
*/
double buildLights(vector <double> a, int n) {

    double left = a[0], right = 0;

    while (left - right > 0.00001) {
        a[1] = (left + right) / 2;
        bool down = true;
        for (int i = 2; i < n; i++) {
            a[i] = 2 * a[i - 1] - a[i - 2] + 2;
            if (a[i] < 0) {
                down = false;
                break;
            }
        }
        if (down) // Если не заходит в минус, то подбираем значение точнее
            left = a[1];
        else // Если зашли ниже пола, то выбираем новое значение для right
            right = a[1];
    }
    return a[n - 1]; // Выводим высоту последней лампочки
}

int main(){
    ifstream fin("garland.in");
    ofstream fout("garland.out");
    
    int n;
    fin >> n;
    vector <double> a(n,0);
    fin >> a[0];
    fout << fixed;
    fout.precision(2); // вывод в 2 знака после ,
    fout << buildLights(a, n);

}
