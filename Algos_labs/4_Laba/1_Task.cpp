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
    int Stack[100000];

    for(int i = 0; i < M; i++) {
        cin >> Command; // Вводим команду + или -

        if(Command == '+') {
            cin >> Num; // Вводим число
            Stack[i] = Num; // в самый верх пихаем новое число
        } else {
            Del = Stack[i-1]; // записываем в Del самый верхний элемент
            i -= 2;
            M -= 2;
            cout << Del << '\n'; // Выводим самый верхний элемент
        }
    }

    return 0;
}