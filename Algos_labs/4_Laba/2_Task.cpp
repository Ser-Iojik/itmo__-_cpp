#include <iostream>
#include <fstream>
using namespace std;

struct Elem { // Структура элемента очереди
    int Num; // Хранение инф об элементе очереди
    Elem *prev; // Указатель на предыдущий элемент
    Elem *next; // Указатель на следующий элемент

};

class Queue {// Класс реализации очереди (двусвязный список)
private:
    Elem *start; // Первый элемент в очереди
    Elem *finish; // Последний элемент в очереди
public:
    Queue() {
        start = NULL; // Говорим что верхний элемент является Null
        finish = NULL; // и финиш
    }

    void enqueue(int item) { // enqueue - объявляем метод для добавления элемента в очередь
        Elem *point = new Elem(); // Создание нового элемента

        if (start != NULL) { // Проверка условия
            start->next = point; // Указать следующий элемент после первого
        }
        else { // Если первый покупатель
            finish = point; // Указать финиш
        }

        point->Num = item; // Заносим информацию
        point->prev = start; // Указатель на предыдущий элемент теперь является нынешним стартом
        point->next = NULL; // Указатель на следующий элемент NULL (т.е. его нет, т.к. нет элемента)

        start = point; // Обновляем старт
    }
    int dequeue() { // dequeue - метод для удаления элемента из очереди
        int result = finish->Num; // Запоминаем результат
        Elem *del = finish; // Объявляем указатель для удаления адреса
        finish = finish->next; // Переводим указатель на следующий элемент
        if (finish == NULL) { // Проверка условия
            start = NULL;
        }
        delete del; // Удаляем адрес
        return result; // Возвращаем результат
    }
};

int main() {
    ifstream fin("queue.in");
    ofstream fout("queue.out");

    Queue q; /// Тут вызывается конструктор
    
    int M;
    fin >> M;

    for (int i = 0; i < M; i++) {
        char Command;
        fin >> Command;
        if (Command == '+') {
            int Num;
            fin >> Num;
            q.enqueue(Num);
        } else {
            fout << q.dequeue() << "\n";
        }
    }

    return 0;
}
