#include <iostream>
#include <utility>
#include <vector>
#include <cmath>
#include <exception>
#include <stdexcept>
#include <string>
using namespace std;

class Polynom {
protected:
public:
    vector<float> k;

    explicit Polynom () {}

    explicit Polynom (vector<float> coef) : k(std::move(coef)) {}

    // Перегрузка оператора =
    Polynom& operator = (const Polynom& Poly) {
        k = Poly.k;
        return *this;
    }

    // Перегрузка оператора <<
    Polynom& operator << (float g) {
        k.emplace_back(g);
        return *this;
    }

    // Перегрузка оператора >>
    Polynom& operator >> (float g) {
        k.at(g);
        cout << k.at(g) << "x" << "^" << g << endl;;
        return *this;
    }

    float& operator[] (const int index);

    void print() {
        int n = k.size();
        for (int i = 0; i < n; i++) {
            if (k[i] == 0) {
                continue;
            }
            if (k[i] == 1 && i == 0) {
                cout << 1 << " ";
                if (i != n-1) {
                    cout << "+ ";
                }
                continue;
            }
            if (k[i] == 1) {
                cout << "x" << "^" << i << " "; 
                if (i != n-1) {
                    cout << "+ ";
                }
                continue;
            }
            if (i == 0) {
                cout << k[i] << " ";
                if (i != n-1) {
                    cout << "+ ";
                }
                continue;
            }
            if (i == 1) {
                cout << k[i] << "x" << " ";
                if (i != n-1) {
                    cout << "+ ";
                }
                continue;
            }
            cout << k[i] << "x" << "^" << i << " ";
            if (i != n-1) {
                cout << "+ ";
            }
        }
    }

    ~Polynom() = default;
};

bool operator == (Polynom Poly1, Polynom Poly2) {
    return Poly1.k == Poly2.k;
}
bool operator != (Polynom Poly1, Polynom Poly2) {
    return Poly1.k != Poly2.k;
}

Polynom operator + (const Polynom& Poly1, const Polynom& Poly2) {
    int max_size = max(Poly1.k.size(), Poly2.k.size());
    int size1 = Poly1.k.size();
    int size2 = Poly2.k.size();

    vector<float> res(max_size);
    for (int i = 0; i < res.size(); i++) {
        res[i] == 0;
    }
    for (int i = 0; i < size1; i++) {
        res[i] += Poly1.k[i];
    }
    for (int i = 0; i < size2; i++) {
        res[i] += Poly2.k[i];
    }
    return Polynom(res);
}

Polynom operator - (const Polynom& Poly1, const Polynom& Poly2) {
    int max_size = max(Poly1.k.size(), Poly2.k.size());
    int size1 = Poly1.k.size();
    int size2 = Poly2.k.size();

    vector<float> res(max_size);
    for (int i = 0; i < res.size(); i++) {
        res[i] == 0;
    }
    for (int i = 0; i < size1; i++) {
        res[i] += Poly1.k[i];
    }
    for (int i = 0; i < size2; i++) {
        res[i] -= Poly2.k[i];
    }
    return Polynom(res);
}

Polynom operator += (Polynom& Poly1, const Polynom& Poly2) {
    int max_size = max(Poly1.k.size(), Poly2.k.size());
    int size1 = Poly1.k.size();
    int size2 = Poly2.k.size();

    vector<float> res(max_size);
    for (int i = 0; i < res.size(); i++) {
        res[i] == 0;
    }
    for (int i = 0; i < size1; i++) {
        res[i] += Poly1.k[i];
    }
    for (int i = 0; i < size2; i++) {
        res[i] += Poly2.k[i];
    }
    return Poly1 = Polynom(res);
}

Polynom operator -= (Polynom& Poly1, const Polynom& Poly2) {
    int max_size = max(Poly1.k.size(), Poly2.k.size());
    int size1 = Poly1.k.size();
    int size2 = Poly2.k.size();

    vector<float> res(max_size);
    for (int i = 0; i < res.size(); i++) {
        res[i] == 0;
    }
    for (int i = 0; i < size1; i++) {
        res[i] += Poly1.k[i];
    }
    for (int i = 0; i < size2; i++) {
        res[i] -= Poly2.k[i];
    }
    return Poly1 = Polynom(res);
}

Polynom operator - (Polynom& Poly) {
    int size = Poly.k.size();

    vector<float> res(size);
    for (int i = 0; i < res.size(); i++) {
        res[i] == 0;
    }
    for (int i = 0; i < size; i++) {
        res[i] -= Poly.k[i];
    }
    return Poly = Polynom(res);
}

Polynom operator *= (Polynom& Poly1, const Polynom& Poly2) {
    int max_size = max(Poly1.k.size(), Poly2.k.size());
    int size1 = Poly1.k.size();
    int size2 = Poly2.k.size();

    vector<float> res(size1*size2);
    for (int i = 0; i < res.size(); i++) {
        res[i] == 0;
    }
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            for (int k = 0; k < 1; k++) {
                k += i + j;
                res[k] += Poly1.k[i] * Poly2.k[j];
                k -= i - j;
            }
        }
    }
    return Poly1 = Polynom(res);
}

Polynom operator /= (Polynom& Poly, float g) {
    int size = Poly.k.size();

    vector<float> res(size);
    for (int i = 0; i < res.size(); i++) {
        res[i] == 0;
    }
    for (int i = 0; i < size; i++) {
        res[i] += Poly.k[i];
    }
    for (int i = 0; i < size; i++) {
        res[i] /= g;
    }
    return Poly = Polynom(res);
}

Polynom operator * (const Polynom& Poly1, const Polynom& Poly2) {
    int max_size = max(Poly1.k.size(), Poly2.k.size());
    int size1 = Poly1.k.size();
    int size2 = Poly2.k.size();

    vector<float> res(size1+size2-1);
    for (int i = 0; i < res.size(); i++) {
        res[i] == 0;
    }
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            int k = i + j;
            res[k] += Poly1.k[i] * Poly2.k[j];
            k -= i - j;
        }
    }
    return Polynom(res);
}

Polynom operator / (const Polynom& Poly, float g) {
    int size = Poly.k.size();
    vector<float> res(size);
    for (int i = 0; i < res.size(); i++) {
        res[i] == 0;
    }
    for (int i = 0; i < size; i++) {
        res[i] += Poly.k[i];
    }
    for (int i = 0; i < size; i++) {
        res[i] /= g;
    }
    return Polynom(res);
}

float& Polynom::operator[] (const int index) {
    return k[index];
}

int main() {
    // Индексы вектора - степени x
    vector<float> k1;
    k1.emplace_back(4);
    k1.emplace_back(5);
    k1.emplace_back(3);
    Polynom Poly1(k1);

    vector<float> k2;
    k2.emplace_back(1);
    k2.emplace_back(2);
    k2.emplace_back(10);
    Polynom Poly2(k2);

    Poly1.print();
    cout << endl;
    Poly2.print();
    cout << endl;

    // Задание 1
    // Перегрузка оператора = и возвращаем всё на место как и было
    cout << endl << "Op=" << endl;
    Polynom Poly0;
    Poly0 = Poly1; // Запомнили Poly1
    Poly1 = Poly2; // Показали что всё работает

    Poly1.print();
    cout << endl;
    Poly1 = Poly0; // Вернули Poly1 на место

    
    // Задание 2
    // Классика. 0 - выражение не верно, 1 - выражение верно :)
    bool b1 = Poly1 == Poly2;
    cout << endl << "Op_==" << endl << b1;

    bool b2 = Poly1 != Poly2;
    cout << endl << "Op_!=" << endl << b2 << endl;


    // Задание 3 fixed
    cout << endl << "Op_+" << endl;
    Polynom Poly3 = Poly1 + Poly2;
    Poly3.print();

    cout << endl << "Op_-" << endl;
    Polynom Poly4 = Poly1 - Poly2;
    Poly4.print();

    cout << endl << "Op_+=" << endl;
    Poly1 += Poly2;
    Poly1.print();
    Poly1 -= Poly2; // Вернули на место

    cout << endl << "Op_-=" << endl;
    Poly1 -= Poly2;
    Poly1.print();
    Poly1 += Poly2; // Вернули на место

    cout << endl << "Op_Un-" << endl;
    -Poly1;
    Poly1.print();


    // Задание 4
    cout << endl;

    Polynom Poly5(k1);
    Polynom Poly6(k2);

    cout << endl << "Op_*=" << endl;
    Poly5 *= Poly6;
    Poly5.print();

    cout << endl << "Op_/=" << endl;
    Poly6 /= 2;
    Poly6.print();

    Polynom Poly7(k1);
    Polynom Poly8(k2);

    cout << endl << "Op_*" << endl;
    Polynom Poly9 = Poly7 * Poly8;
    Poly9.print();

    cout << endl << "Op_/" << endl;
    Polynom Poly10 = Poly7 / 2;
    Poly10.print();

    // Задание 5
    cout << endl;
    cout << endl << "Op_<<" << endl;
    Polynom Poly11;
    Poly11 << 5 << 0 << 87 << 1 << 32 << 0 << 0 << 0 << 3;
    Poly11.print();
    cout << endl << "Op_>>" << endl;
    Poly11 >> 3;

    // Задание 6
    cout << endl << "Op_[]" << endl;
    int index = 2;
    cout << Poly11[index];

    return 0;
}