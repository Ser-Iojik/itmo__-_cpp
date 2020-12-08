#include <fstream>
#include <iostream>

#define MAXN 1000 // Максимальное условное количество элементов в массиве

using namespace std;

// Структура односвязаного списка для словаря
struct ListNode {
	string key; // Ключ
	string value; // Значение
	ListNode *next; // Адрес следующего элемента
};

// Класс описывающий множество
class Map {
private:
    ListNode *start; // Адрес начального элемента
public:
	Map() { // Конструктор (вызывается при объявлении переменной)
        start = new ListNode(); // Объявляем новую переменную
        start->value = ""; // Присваиваем пустую строку значению
        start->key = ""; // Присваиваем пустую строку ключу
        start->next = NULL; // Адрес следующего элемента NULL
    }

    void Insert(string key, string value) { // Метод добавления элемента
        ListNode *newNode = Search(key); // Присваиваем адресу новой переменной адрес элемента по ключу
        if (Search(key) == NULL) { // Если функция вернула NULL
            ListNode *newNode = new ListNode; // То создаём новую переменную
            newNode->key = key; // Заносим ключ
            newNode->value = value; // Заночим значение
            newNode->next = start->next; // Переводим адрес
            start->next = newNode; // Обновляем адрес старта
        }
        else { // Если элемент с таким ключом уже есть то мы ПЕРЕЗАПИСЫВАЕМ значение
            ListNode *exNode = Search(key); // Находим адрес нужного элемента
            exNode->value = value; // Обновляем значение
        }
    }

    void Delete(string key) { // Метод удаление элемента по ключу
        ListNode *curNode = start; // Начинаем с начального адреса списка

        while (curNode->next != NULL) { // Перебираем до тех пор пока адрес не станет равен NULL
            if (curNode->next->key == key) { // Если нашли нужный элемент
                ListNode *del = curNode->next; // Запоминаем адрес для удаления
                curNode->next = curNode->next->next; // Переводим указатель на следующий адрес

                delete del; // Удаление элемента

                break; // Выход из цикла
            }
            else {
                curNode = curNode->next; // Переводим адрес на следующий
            }
        }
    }

    ListNode* Search(string key) { // Функция нахождения адреса элемента по ключу
        ListNode *curNode = start; // Итератор встаёт в начало списка

        while (curNode->next != NULL) { // До тех пор пока адрес не равен NULL (т.е. концу списка)
            if (curNode->next->key == key) { // Если нашли нужный элемент
                return curNode->next; // Возвращаем его адрес
            }
            else {
                curNode = curNode->next; // Переходим к адресу следующего элемента
            }
        }

        return NULL; // Если элемент не найден то возвращаем NULL
    }
};

class UpgradeMap { // Класс для оптимизации работы со множеством черех массив
private:
    Map mp[MAXN]; // Массив множество
public:
    int findID(string key) { // Метод нахождения индекса
        unsigned int res = 0; // Результат
        unsigned int pow = 1; // Степень
        unsigned int p = 31; // Константа

        for(int i = 0; i < key.length(); i++) {
            res += (key[i] - 'A') * pow; // Арифметические операциии
            pow *= p; // Арифметические операции
        }

        return res % MAXN; // Возвращаем остаток от деления результата НА максимальное кол-во элементов
    }

    void Put(string key, string value) { // Метод добавления элемента в словарь
        mp[findID(key)].Insert(key, value);
    }

    string Get(string key) { // Метод получения элемента из словаря по ключу
        ListNode *result = mp[findID(key)].Search(key);

        if (result == NULL) { // Если такого элемента нет
            return "none"; // то возвощаем none
        }
        else {
            return result->value; // Иначе значение элемента
        }
    }

    void Delete(string key) { // Метод удаления элемента из словаря по ключу
        mp[findID(key)].Delete(key);
    }
};

int main() {
	ifstream fin("map.in");
	ofstream fout("map.out");

	UpgradeMap mp; // Переменная словаря

	string cmd;
	while (fin >> cmd) {
		string key;
		fin >> key;

		if (cmd == "put") {
			string value;
			fin >> value;

			mp.Put(key, value);
		}
        else if (cmd == "delete") {
            mp.Delete(key);
        }
		else {
			fout << mp.Get(key) << endl;
		}
	}

	return 0;
}
