#include <iostream>
#include <fstream>
using namespace std;

struct StackNode {
    int elem; // Элемент в списке
    StackNode *next; // Указатель на следующий элемент списка
};

class Stack {
    private: 
        StackNode *top; // Конкретно в этом классе берём указатель на верхний элемент
    public:
        Stack() {
            top = NULL; // Говорим что верхний элемент является Null
        }

        void push(int Num) {
            StackNode *node = new StackNode(); // Создали новую переменную node нашего типа StackNode
            node->next = top; // И указатель равен указателю на следующий элемент            
            node->elem = Num; // Говорим что элемент теперь равен нашему числу
            top = node; // Записываем всё в верхний элемент(обновляем его)
        }

        int pop() {
            int result = top->elem; // В result сохраняем текущий элемент сверху списка с его числом и адресом
            // В первом случае это будет 10 и его адрес, во втором 1234 с адресом соответственно
            StackNode *del = top; // Объявляем новую переменную del, в которую записываем адрес для дальнейшего удаления
            top = top->next; // Перевели указатель на следующий элемент
            delete del; // Удалили адрес
            return result; // Вернули результат
        }
};

int main() {
    ifstream fin("stack.in");
    ofstream fout("stack.out");

    Stack Stack;

    int M;
    fin >> M;

    for (int i = 0; i < M; i++) {
        string command;
        fin >> command;
        if (command == "+") {
            int Num;
            fin >> Num;
            Stack.push(Num);
        } else {
            fout << Stack.pop() << endl;
        }
    }


    return 0;
}
