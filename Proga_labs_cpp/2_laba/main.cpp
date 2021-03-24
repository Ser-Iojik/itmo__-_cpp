#include <iostream>
#include <utility>
#include <vector>
#include <cmath>
#include <exception>
#include <stdexcept>
#include <string>
using namespace std;

// Документация к ф-циям print()
// print() для операций +=, -=, -, =, вывод полинома
// printDuo() для операций +, -
// printMultiplication() для операций *=, /=
// printMultiplicationDivision() для операций *, /

class Polynom {
private:
public:
    vector<float> k;
    vector<vector<float>> k2;
    int size1;
    int size2;

    explicit Polynom () {}

    explicit Polynom (vector<float> coef) : k(std::move(coef)) {}

    explicit Polynom (vector<float> coef1, vector<float> coef2) {
        size1 = coef1.size();
        size2 = coef2.size();
        k2.resize(2);

        for (int i = 0; i < size1; i++) {
            k2[0].emplace_back(coef1[i]);
        }
        for (int i = 0; i < size2; i++) {
            k2[1].emplace_back(coef2[i]);
        }
    }

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

    void printDuo() {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < k2[i].size(); j++) {
                if (k2[i][j] == 0) {
                    continue;
                }
                if (k2[i][j] == 1 && j == 0) {
                    cout << 1 << " "; 
                    if (j != k2[i].size()-1) {
                        cout << "+ ";
                    }
                    continue;
                }
                if (k2[i][j] == 1) {
                    cout << "x" << "^" << j << " ";
                    if (j != k2[i].size()-1) {
                        cout << "+ ";
                    }
                    continue;
                }
                if (j == 0) {
                    cout << k2[i][j] << " ";
                    if (j != k2[i].size()-1) {
                        cout << "+ ";
                    }
                    continue;
                }
                if (j == 1) {
                    cout << k2[i][j] << "x" << " ";
                    if (j != k2[i].size()-1) {
                        cout << "+ ";
                    }
                    continue;
                }
                cout << k2[i][j] << "x" << "^" << j << " ";
                if (j != k2[i].size()-1) {
                    cout << "+ ";
                }
            }
            if (i < k2.size()-1) {
                cout << "+ ";
            }
        }
    }

    void printMultiplication() {
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
                cout << "x" << "^" << i*2 << " "; 
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
                cout << k[i] << "x" << "^" << i*2 << " ";
                if (i != n-1) {
                    cout << "+ ";
                }
                continue;
            }
            cout << k[i] << "x" << "^" << i*2 << " ";
            if (i != n-1) {
                cout << "+ ";
            }
        }
    }
    
    void printDuoMultiplicationDivision(string str) {
        for (int i = 0; i < 2; i++) {
            cout << "(";
            for (int j = 0; j < k2[i].size(); j++) {
                if (k2[i][j] == 0) {
                    continue;
                }
                if (k2[i][j] == 1 && j == 0) {
                    cout << 1 << " "; 
                    if (j != k2[i].size()-1) {
                        cout << "+ ";
                    }
                    continue;
                }
                if (k2[i][j] == 1) {
                    cout << "x" << "^" << j << " ";
                    if (j != k2[i].size()-1) {
                        cout << "+ ";
                    }
                    continue;
                }
                if (j == 0) {
                    cout << k2[i][j] << " ";
                    if (j != k2[i].size()-1) {
                        cout << "+ ";
                    }
                    continue;
                }
                if (j == 1) {
                    cout << k2[i][j] << "x" << " ";
                    if (j != k2[i].size()-1) {
                        cout << "+ ";
                    }
                    continue;
                }
                cout << k2[i][j] << "x" << "^" << j;
                if (j != k2[i].size()-1) {
                    cout << "+ ";
                }
                if (j == k2[i].size()-1) {
                    cout << ") ";
                }
            }
            if (i < k2.size()-1 && str == "*") {
                cout << "* ";
            }
            if (i < k2.size()-1 && str == "/") {
                cout << "/ ";
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

Polynom operator + (Polynom Poly1, Polynom Poly2) {
    Polynom Plus(Poly1.k, Poly2.k);
    Plus.printDuo();
}

Polynom operator - (Polynom Poly1, const Polynom& Poly2) {
    int size = Poly2.k.size();

    vector<float> res(size);
    for (int i = 0; i < res.size(); i++) {
        res[i] == 0;
    }
    for (int i = 0; i < size; i++) {
        res[i] -= Poly2.k[i];
    }

    Polynom Minus(Poly1.k, res);
    Minus.printDuo();
}

Polynom operator += (const Polynom& Poly1, const Polynom& Poly2) {
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
    Polynom(res).print();
    return Polynom(res);
}

Polynom operator -= (const Polynom& Poly1, const Polynom& Poly2) {
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
    Polynom(res).print();
    return Polynom(res);
}

Polynom operator - (const Polynom& Poly) {
    int size = Poly.k.size();

    vector<float> res(size);
    for (int i = 0; i < res.size(); i++) {
        res[i] == 0;
    }
    for (int i = 0; i < size; i++) {
        res[i] -= Poly.k[i];
    }

    Polynom(res).print();
    return Polynom(res);
}

Polynom operator *= (const Polynom& Poly1, const Polynom& Poly2) {
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
        res[i] *= Poly2.k[i];
    }
    Polynom(res).printMultiplication();
    return Polynom(res);
}

Polynom operator /= (const Polynom& Poly, float g) {
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
    Polynom(res).print();
    return Polynom(res);
}

Polynom operator * (Polynom Poly1, Polynom Poly2) {
    Polynom Multiplication(Poly1.k, Poly2.k);
    Multiplication.printDuoMultiplicationDivision("*");
}

Polynom operator / (Polynom Poly1, Polynom Poly2) {
    Polynom Multiplication(Poly1.k, Poly2.k);
    Multiplication.printDuoMultiplicationDivision("/");
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


    // Задание 3
    cout << endl << "Op_+" << endl;
    Polynom Poly3 = Poly1 + Poly2;

    cout << endl << "Op_-" << endl;
    Polynom Poly4 = Poly1 - Poly2;

    cout << endl << "Op_+=" << endl;
    Polynom Poly5 = Poly1 += Poly2;

    cout << endl << "Op_-=" << endl;
    Polynom Poly6 = Poly1 -= Poly2;

    cout << endl << "Op_Un-" << endl;
    Polynom UnMinus = -Poly1;


    // Задание 4
    cout << endl;
    cout << endl << "Op_*=" << endl;
    Polynom Poly7 = Poly1 *= Poly2;

    cout << endl << "Op_/=" << endl;
    Polynom Poly8 = Poly1 /= 2;

    cout << endl << "Op_*" << endl;
    Polynom Poly9 = Poly1 * Poly2;

    cout << endl << "Op_/" << endl;
    Polynom Poly10 = Poly1 / Poly2;


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
    cout << Poly11[index] << "x" << "^" << index;

    return 0;
}
