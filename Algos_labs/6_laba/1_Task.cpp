#include <iostream>
#include <fstream>

#define MAXN 100000 // Максимальный размер массива

using namespace std;

 // Структура односвязаного списка
struct ListNode {
    int info; // Информация
    ListNode *next; // Адрес следующего элемента
};

// Класс множества
class Set {
private:
    ListNode *start; // Адрес начала списка
public:
    Set() { // Конструктор (вызывается при объявлении переменной)
        start = new ListNode(); // Создаём новый элемент списка
        start->info = -1; // Ставим условную (любую) информацию в него
        start->next = NULL; // Присваем адрес следующего элемента NULL (т.е. без адреса)
    }
    void Insert(int info){ // Метод для добавления элемента
        // Проверка на то, существует ли уже в списке такая информация
        if (!Exists(info)) { //Если нет, то выполняются следующие действия
            ListNode *newNode = new ListNode(); // Создаём новый элемент списка
            newNode->info = info; // Записываем в него информацию
            newNode->next = start->next; // В адрес следующего элемента записываем адрес следующий после старта
            start->next = newNode; // Обновляем следующий за стартом адрес
        }
    }

    void Delete(int value) { // Метод для удаление элемента по значению
        ListNode *curNode = start; // Счётчик/Итератор для прохождения по всем элементам списка
        // В начале присваиваем его адресу начала списка
        while (curNode->next != NULL) {// До тех пор, пока АДРЕС СЛЕДУЮЩЕГО ЭЛЕМЕНТА не станет равен NULL
            if (curNode->next->info == value) {// Если мы дошли до нужного нам элемента
                ListNode *del = curNode->next; // то запоминаем его адрес
                curNode->next = curNode->next->next; // Переводим указатель на следующий элемент после следующего

                delete del; // Удаляем элемент

                break; // Выходим из цикла
            }
            else {
                curNode = curNode->next; // Переходим к следующему элементу в списку переводя адрес текущего на следующий
            }
        }
    }

    // Метод для проверки существования элемента в списке
    bool Exists(int value) { 
        ListNode *curNode = start; // Счётчик/Итератор для прохождения по всем элементам списка
        // В начале присваиваем его адресу начала списка
        while (curNode->next != NULL) { // До тех пор, пока АДРЕС СЛЕДУЮЩЕГО ЭЛЕМЕНТА не станет равен NULL
            if (curNode->next->info == value) { // Если мы дошли до нужного нам элемента
                return true; // Возвращаем TRUE
            }
            else {
                curNode = curNode->next; // Переходим к следующему элементу в списку переводя адрес текущего на следующий
            }
        }
        return false; // Если пройдясь через цикл не нашли элемент то возвращаем FALSE
    }
};

class UpgradeSet { // Класс для оптимизации через массив и индексы
private:
    Set st[MAXN]; // Массив множеств
public:
    int findID(int element) { // Метод нахождения оптимального индекса
        int res = element % MAXN; // Значение элемента взятие по остатку максимальное кол-во элементов в массиве
                                    // Это формула/правило такое
        if (res < 0) { // Условие, если результат меньше 0
            res += MAXN; // То прибавить максимальное кол-во элементов в массиве
        }

        return res; // Вернуть результат
    }
    void Insert(int element) { // Метод добавления элемента
        if (!Exists(element)) { // Если ещё не существует в списке
            st[findID(element)].Insert(element); // То в специальную ячейку добавляем элемент
        }
    }

    bool Exists(int element) { // Метод существует ли элемент
        return st[findID(element)].Exists(element); // То вызываем для специальной ячейки метод
    }

    void Delete(int element) { // Метод удаления элемента
        st[findID(element)].Delete(element); // Вызываем метод для специальной ячейки
    }
};

int main() {
    UpgradeSet mySet; // Объявляем переменную класса
    ifstream fin("set.in");
    ofstream fout("set.out");

    string cmd; // Команда
    while (fin >> cmd) { // До тех пор пока из файла идёт ввод по слову
        // Выполняем операции с числами
        int digit;
        fin >> digit;
        if (cmd == "insert") {
            mySet.Insert(digit);
        }
        else if (cmd == "delete") {
            mySet.Delete(digit);
        }
        else {
            if (mySet.Exists(digit)) {
                fout << "true" << endl;
            }
            else {
                fout << "false" << endl;
            }
        }

    }

    return 0;
}
