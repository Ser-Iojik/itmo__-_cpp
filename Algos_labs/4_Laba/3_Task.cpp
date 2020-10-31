#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct StackNode {
    char info;
    StackNode *next;
};

class Stack {
public:
    StackNode *top;
    Stack() {
        top = NULL;
    }

    void push(char elem) {
        StackNode *node = new StackNode();
        node->next = top;
        node->info = elem;
        top = node;
    }

    void pop() {
        if (!isEmpty() == true) {
            StackNode *del = top;
            top = top->next;
            delete del;
        }
    }

    char getTop() {
        return top->info;
    }

    bool isEmpty() {
        if (top == NULL) {
            return true;
        }
        return false;
    }
};

int main() {
    ifstream fin("brackets.in");
    ofstream fout("brackets.out");
    Stack Stack;

    string sub;

    while (fin >> sub) {
        string flag = "YES";

        for (int i = 0; sub[i] != '\0'; i++) { // В цикле проходим до конца строки
            if (sub[i] == '(' || sub[i] == '[') {
                Stack.push(sub[i]);
            } else { // Если стек не пустой, то делаем проерку на соответствие скобок и вытаскиваем последнюю скобку из стека
                if (Stack.isEmpty() == false && ((Stack.getTop() == '[' && sub[i] == ']') || (Stack.getTop() == '(' && sub[i] == ')'))) {
                    Stack.pop();
                } else { // Если стек пустой и первая скобка закрывающая
                    flag = "NO";
                }
            }
        } // Если стек пуст, то всё ОК
        if (Stack.isEmpty() == true) {
            if (flag == "NO") {
                flag = "NO";
            } else {
                flag = "YES";
            }
        } else {
            flag = "NO";
        }
        fout << flag << endl;

        for(int j = 0; j <= 10000; j++) {
            if(Stack.isEmpty() == false) {
                Stack.pop();
            }
            if(Stack.isEmpty() == true) {
                break;
            }
        }
    }
    return 0;
}
