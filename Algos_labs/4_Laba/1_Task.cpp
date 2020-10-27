#include <iostream>
using namespace std;
 
int main() {
    freopen("stack.in", "r", stdin);
    freopen("stack.out", "w", stdout);

    int M;
    cin >> M;
    char Command;
    int Num;
    int Del;
    int Stack[M];

    for(int i = 0; i < M; i++) {
        cin >> Command; // Вводим команду + или -

        if(Command == '+') {
            cin >> Num; // Вводим число
            for(int l = M-1; l >= 0; l--) {
                Stack[l] = Stack[l-1]; // Перестраиваем стек, чтоб освободить место
            }
            Stack[0] = Num; // в самый низ пихаем новое число
        }
        if(Command == '-') {
            Del = Stack[0]; // записываем в Del самый нижний элемент
            for(int j = 0; j < M; j++) {
                Stack[j] = Stack[j+1]; // Перестраиваем стек
            }
            cout << Del << "\n"; // Выводим самый нижний элемент
        }
    }

    return 0;
}