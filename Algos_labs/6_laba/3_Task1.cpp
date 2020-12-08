#include <fstream>
#include <iostream>

#define MAXN 1000 // Максимальное количество элементов

using namespace std;

struct ListNode { // Структура ячейки элемента списка
	string key; // Ключ
	string value; // Значение
	ListNode *nextInChain; // Адрес следующего элемента в цепочке
	ListNode *next; // Адрес следующего элемента
	ListNode *prev; // Адрес предыдущего элемента
};

class LinkedMap { // Класс связанного словаря
private:
    ListNode *start; // Начальный адрес элемента
public:
	LinkedMap() { // Конструктор (вызывается при объявлении переменной)
        start = new ListNode(); // Объявляем новую переменную
        start->key = ""; // Записываем в ключ пустую строку
        start->value = ""; // Записываем в значение пустую строку
        start->nextInChain = NULL; // Адресу следующего элемента в цепочке ставим NULL
    }

    void Insert(string key, string value, ListNode *Head) { // Метод добавления элемента
        ListNode *newNode = Search(key); // Находим адрес элемента по ключу

        if (Search(key) == NULL) { // Если такого элемента не существует то создаём новый
            newNode = new ListNode; // Объявляем новую переменную для вызова конструктора
            newNode->key = key; // Заносим ключ
            newNode->value = value; // Заносим значение
            newNode->nextInChain = start->nextInChain; // Переводим адрес следующего в цепочке
            start->nextInChain = newNode; // Обвноляем адрес следующего в цепочке
            ListNode *Tail = Head->prev; // Объявляем переменную конца списка и присвиваем адрес прыдыдущего перед началом
            Tail->next = newNode; // Обновляем адрес следующего элемента
            Head->prev = newNode; // Обновляем адрес предыдущего элемента
            newNode->next = Head; // Ставим адрес следующего элемента
            newNode->prev = Tail; // Ставим адрес предыдущего элемента
        }
        else { // Если элемент не найден
            newNode->value = value; // То перезаписываем значение
        }
    }

    void Delete(string key, ListNode *Head) { // Метод удаления элемента
        ListNode *curNode = start; // Ставим адрес на начало списка

        while (curNode->nextInChain != NULL) { // Перебираем все адреса списка
            if (curNode->nextInChain->key == key) { // Если нашли нужный элемент
                ListNode *del = curNode->nextInChain; // Запоминаем адрес
                curNode->nextInChain = curNode->nextInChain->nextInChain; // Переводим адрес на следующий
                ListNode *PrevListNode = del->prev, *NextListNode = del->next; // Запоминаем адреса предыдущего/следующего
                del->prev->next = NextListNode; // Заносим адрес следующего
                del->next->prev = PrevListNode; // Заносим адрес предыдущего
                delete del; // Удаляем элемент

                break; // Выходим из цикла
            }
            else { // Если не найден
                curNode = curNode->nextInChain; // То переходим к следующему адресу (элементу списка)
            }
        }
    }

    ListNode* Search(string key) { // Метод поиска адреса элемента по ключу

        ListNode *curNode = start; // Начинаем с начального адреса списка

        while (curNode->nextInChain != NULL) { // До тех пор пока адрес следующего элемента не NULL
            if (curNode->nextInChain->key == key) { // Если нашли нужный элемент
                return curNode->nextInChain; // Возвращаем его адрес
            }
            else { // Если нет
                curNode = curNode->nextInChain; // Переходим к следующему элементу
            }
        }

        return NULL; // Если прошли цикл и не нашли нужного элемента то возвращаем NULL
    }
};

class UpgradeLinkedMap { // Класс для оптимизации работы со ссылочным словарём через массив
private:
    LinkedMap mp[MAXN]; // Массив словарей
	ListNode *Head; // Адрес начального/конечно элемента ("головы" списка)
public:
	UpgradeLinkedMap() { // Конструктор
        Head = new ListNode; // Объявляем переменную
        Head->next = Head->prev = Head; // Присваиваем предыдещму и следующему элементу один адрес
        Head->value = Head->key = "HEAD"; // Присваиваем ключу и значению строку "HEAD"
    }

    int findID(string key) { // Нахождение индекса
        unsigned int result = 0; // Результат
        unsigned int power = 1; // Степень
        unsigned int p = 31; // Константа

        for(int i = 0; i < key.length(); i++) {
            result += (key[i] - 'A') * power;
            power *= p;
        }

        return result % MAXN; // Возвращаем остаток от деления результата на макс. кол-во элементов в массиве
    }

    void Put(string key, string value) { // Метод добавления элемента
        mp[findID(key)].Insert(key, value, Head);
    }

    string Get(string key) { // Метод получения значения в элементе

        ListNode *result = mp[findID(key)].Search(key); // Находим элемент по ключу

        if (result == NULL) { // Если такого элемента нет
            return "none"; // То возвращаем "none"
        }
        else {
            return result->value; // иначе возвращаем значение которое хранится по этому адресу
        }
    }

    void Delete(string key) { // Метод удаления элемента
        mp[findID(key)].Delete(key, Head);
    }

    string Next(string key) { // Метод получения значения следующего элемента

        ListNode *result = mp[findID(key)].Search(key); // Находим адрес элемента

        if (result == NULL || result->next == Head) {
            // Если адрес текущего элемента равен NULL или адрес следующего элемента равен адресу Head
            return "none"; // то  возвращаем "none"
        }
        else { // иначе
            return result->next->value; // Возвращаем значение следующего элемента
        }
    }

    string Prev(string key) { // Метод получения значения предыдущего элемента

        ListNode *result = mp[findID(key)].Search(key); // Находим адрес элемента по ключу

        if (result == NULL || result->prev == Head) {
            // Если адрес текущего элемента равен NULLL или адрес предыдущего равен адресу Head
            return "none"; // то возвращаем "none"
        }
        else { // иначе
            return result->prev->value; // возвращаем значение предыдущего элемента
        }
    }
};

int main() {
	ifstream fin("linkedmap.in");
	ofstream fout("linkedmap.out");

	UpgradeLinkedMap lm; // Объявляем переменную

	string cmd;
	while (fin >> cmd) { // Вводим команды
		string key;
		fin >> key;

		if (cmd == "put") {
			string value;
			fin >> value;

			lm.Put(key, value);
		}
		else if (cmd == "delete") {
			lm.Delete(key);
		}
		else if (cmd == "get") {
			fout << lm.Get(key) << endl;
		}
		else if (cmd == "next") {
			fout << lm.Next(key) << endl;
		}
		else {
			fout << lm.Prev(key) << endl;
		}
	}
	return 0;
}
