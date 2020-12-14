#include <fstream>
#include <cstdlib>
#include <queue>
    
using namespace std;

// ifstream fin("rotation.in");
// ofstream fout("rotation.out");
ifstream fin("rotationin.txt");
ofstream fout("rotationout.txt");

typedef int T;
typedef int L;
typedef int R;
typedef int ID;
typedef int H;

#define RT(a, b) ((a) > (b))
#define LT(a, b) ((a) < (b))
   
// Структура дерева
struct Node {
    T data;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
    H height;
    L leftkey;
    R rightkey;
    ID id;
};

int n = 1;
// Функция создания нового узла
Node* getFreeNode(T value, Node *parent, L leftkey, R rightkey) {
    Node* tmp = (Node*) malloc(sizeof(Node));
    tmp->left = tmp->right = NULL;
    tmp->data = value;
    tmp->parent = parent;
    tmp->leftkey = leftkey;
    tmp->rightkey = rightkey;
    tmp->height;
    tmp->id = n;
    n++;
    return tmp;
}
    
void insert(Node **head, int key, int left, int right) {
            
    Node *tmp = NULL;
    int j = 1;
    // Проверяем, если дерево пустое, то вставляем корень
    if (*head == NULL) {
        *head = getFreeNode(key, NULL, left, right);
        return;
    }
  
    // Проходим по дереву и ищем место для вставки
    tmp = *head;
    // Пока не дошли до пустого узла
    while (tmp) {
        // Если значение больше, чем значение текущего узла
        if (RT(key, tmp->data)) {
            // Если при этом правый узел не пустой, то за корень теперь считаем правую ветвь и начинаем цикл сначала
            if (tmp->right) {
                tmp = tmp->right;
                continue;
            // Если правой ветви нет, то вставляем узел справа
            } else {
                tmp->right = getFreeNode(key, tmp, left, right);
                return;
            }
        // Также обрабатываем левую ветвь
        } else if (LT(key, tmp->data)) {
            if (tmp->left) {
                tmp = tmp->left;
                continue;
            } else {
                tmp->left = getFreeNode(key, tmp, left, right);
                return;
            }
        } else {
            exit(2); // 
        }
    }
}

// функция подсчёта высоты узла
int height(Node* root){
    if (root == NULL) {
        return 0;
    } else {
        return root->height = 1 + max(height(root->left), height(root->right)); 
    }
}

Node* rotateLeft(Node* root) {
	Node* newRoot = root->right;
	root->right = newRoot->left;
	newRoot->left = root;
    height(root);
    height(newRoot);
	return newRoot;
}

Node* rotateRight(Node* root) {
	Node* newRoot = root->left;
	root->left = newRoot->right;
	newRoot->right = root;
	height(root);
	height(newRoot);
	return newRoot;
}

// Функция для большого левостороннего поворота
Node* big_rotation_left(Node* root) {
    rotateRight(root->right);
    return rotateLeft(root);
}

int bfactor(Node* root) {
	return height(root->right)-height(root->left);
}

Node* balance(Node* root) { // балансировка узла p
	// height(root);
	if(bfactor(root) == 2) {
		if( bfactor(root->right) < 0 )
			root->right = rotateRight(root->right);
		return rotateLeft(root);
	}
	if( bfactor(root)==-2 ) {
		if( bfactor(root->left) > 0  )
			root->left = rotateLeft(root->left);
		return rotateRight(root);
	}
	return root; // балансировка не нужна
}

void print_tree(int N, Node* root) {
    fout << N << endl; // печатаем кол-во вершин дерева
    queue<Node*> q; // вводим очередь
    q.push(root); // заряжаем в неё корень дерева
    int line = 1;
    while(!q.empty()) {// пока очередь не пуста
        Node* root = q.front(); // запоминаем ссылку на первый элемент
        q.pop(); // удаляем его
        int l = 0, r = 0;
        if(root->left) {// если есть левый ребёнок
            q.push(root->left); // заряжаем в очередь левого ребёнка
            l = ++line;
        }
        if(root->right) {// если есть левый ребёнок
            q.push(root->right); // заряжаем в очередь правого ребёнка
            r = ++line;
        }
        fout << root->data << " " << (l) << " " << (r) << endl; // вывод эл. и индексы на его детей
    }
}

int main() {
    Node *root = NULL;
    int N, key, left, right;
    fin >> N;

    for(int i = 0; i < N; i++) {
        fin >> key >> left >> right;
        insert(&root, key, left, right);
    }

    // calc_height(root); // запускаем функцию посчёта высоты
    Node* new_root = balance(root); // запускаем функцию для поворота дерева
    print_tree(N, new_root); // запускаем функцию вывода avl дерева

    fin.close();
    fout.close();
    return 0;
}