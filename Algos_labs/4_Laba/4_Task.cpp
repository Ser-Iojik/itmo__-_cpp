#include <iostream>
#include <fstream>

using namespace std;

struct StackNode {
    int info;
    StackNode *next;
};

class Stack {
private:
    StackNode *top;
public:
    Stack() {
        top = NULL;
    }

    void push(int elem) {
        StackNode *node = new StackNode();
        node->next = top;
        node->info = elem;
        top = node;
    }

    int pop() {
        int result = top->info;
        StackNode *del = top;
        top = top->next;
        delete del;
        return result;
    }
};

int main() {
    ifstream fin("postfix.in");
    ofstream fout("postfix.out");

    Stack Stack;

    string sub;
    getline(fin, sub); // Записываем входные данные в строку
    for (int i = 0; sub[i] != '\0'; i++) {
        if (sub[i] >= '0' && sub[i] <= '9') {
            Stack.push((int)sub[i] - '0');
        }
        else if (sub[i] == '+') {
            Stack.push(Stack.pop() + Stack.pop());
        }
        else if (sub[i] == '-') {
            int y = Stack.pop();
            int x = Stack.pop();
            Stack.push(x - y);
        }
        else if (sub[i] == '*') {
            Stack.push(Stack.pop() * Stack.pop());
        }
    }
    fout << Stack.pop() << endl;

    return 0;
}