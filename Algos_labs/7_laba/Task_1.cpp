#include <fstream>
// #include <cstdlib>
#include <vector>
   
using namespace std;
   
// typedef int T;
// typedef int L;
// typedef int R;
// typedef int ID;
 
// #define RT(a, b) ((a) > (b))
// #define LT(a, b) ((a) < (b))
  
// // Структура дерева
// struct Node {
//     T data;
//     struct Node *left;
//     struct Node *right;
//     struct Node *parent;
//     L leftkey;
//     R rightkey;
//     ID id;
// };

// int n = 1;
// // Функция создания нового узла
// Node* getFreeNode(T value, Node *parent, L leftkey, R rightkey) {
//     Node* tmp = (Node*) malloc(sizeof(Node));
//     tmp->left = tmp->right = NULL;
//     tmp->data = value;
//     tmp->parent = parent;
//     tmp->leftkey = leftkey;
//     tmp->rightkey = rightkey;
//     tmp->id = n;
//     n++;
//     return tmp;
// }

// Класс для хранения узла
class Uzel {
public:
    int key;
    int leftKid;
    int rightKid;
    int h = 0;
    Uzel(int _key, int _left, int _right) : key(_key), leftKid(_left), rightKid(_right) {}
};
   
// void insert(Node **head, int key, int left, int right) {
           
//     Node *tmp = NULL;
//     int j = 1;
//     // Проверяем, если дерево пустое, то вставляем корень
//     if (*head == NULL) {
//         *head = getFreeNode(key, NULL, left, right);
//         return;
//     }
 
//     // Проходим по дереву и ищем место для вставки
//     tmp = *head;
//     // Пока не дошли до пустого узла
//     while (tmp) {
//         // Если значение больше, чем значение текущего узла
//         if (RT(key, tmp->data)) {
//             // Если при этом правый узел не пустой, то за корень теперь считаем правую ветвь и начинаем цикл сначала
//             if (tmp->right) {
//                 tmp = tmp->right;
//                 continue;
//             // Если правой ветви нет, то вставляем узел справа
//             } else {
//                 tmp->right = getFreeNode(key, tmp, left, right);
//                 return;
//             }
//         // Также обрабатываем левую ветвь
//         } else if (LT(key, tmp->data)) {
//             if (tmp->left) {
//                 tmp = tmp->left;
//                 continue;
//             } else {
//                 tmp->left = getFreeNode(key, tmp, left, right);
//                 return;
//             }
//         } else {
//             exit(2);
//         }
//     }
// }
   
// // функция подсчёта высоты узла
// int height(Node* root){
//     if (root == NULL) {
//         return 0;
//     } else {
//         return 1 + max(height(root->left), height(root->right)); 
//     }
// }

// Функция для поиска высоты справа
int right_height(int i, vector<Uzel>& root) {
    if (root[i].rightKid == -1) {
        return 0;
    }
    return root[root[i].rightKid].h;
}
// Функция для поиска высоты слева
int left_height(int i, vector<Uzel>& root) {
    if (root[i].leftKid == -1) {
        return 0;
    }
    return root[root[i].leftKid].h;
}

// Функция для подсчёта высоты узла
void height(int i, vector<Uzel>& root) {
    if (root[i].leftKid != -1) {
        height(root[i].leftKid, root);
    }
    if (root[i].rightKid != -1) {
        height(root[i].rightKid, root);
    }
    root[i].h = max(left_height(i, root), right_height(i, root)) + 1;
}

int balance(int i, vector<Uzel>& root) {
    int Right = 0, Left = 0;

    Right = root[i].rightKid;
    if (Right != -1) {
        Right = root[root[i].rightKid].h;
    } else {
        Right = 0;
    }

    Left = root[i].leftKid;
    if (Left != -1) {
        Left = root[root[i].leftKid].h;
    } else {
        Left = 0;
    }
    return Right - Left;
}

// void preOrderTravers(Node* root, int i) {
//     if (root) {
//         if (root->id == i) {
//             fout << height(root->right) - height(root->left) << endl;
//             // fout << height(root->right) - height(root->left) << " Data: " << root->data << " ID: " << root->id << endl;
//         }
//         preOrderTravers(root->left, i);
//         preOrderTravers(root->right, i);
//     }
// }
   
// функция построения дерева для проверки
// void printTree(Node *root, const char *dir, int level) {
//     if (root) {
//         fout << "lvl " << level << " " << dir << " = " << root->data << " ID: " << root->id << "\n";
//         printTree(root->left, "left", level+1);
//         printTree(root->right, "right", level+1);
//     }
// }
   
int main() {
    ifstream fin("balance.in");
    ofstream fout("balance.out");
    // ifstream fin("balancein.txt");
    // ofstream fout("balanceout.txt");
    // Node *root = NULL;
    int N, key, left, right;
    fin >> N;
    vector <Uzel> root;
    // for(int i = 0; i < N; i++) {
    //     fin >> key >> left >> right;
    //     insert(&root, key, left, right);
    // }
    for (int i = 0; i < N; i++) {
        fin >> key >> left >> right;
        root.push_back(Uzel(key, left - 1, right - 1));
    }
    height(0, root);
    for (int i = 0; i < N; i++) {
        fout << balance(i, root) << endl;
    }
    // for(int i = 1; i <= N; i++) {
    //     // fout << arrID[i] << " ";
    //     preOrderTravers(root, i);
    // }
    // fout << endl;
    // OBXOD_DEREVA(root);
 
    // printTree(root, "head", 1);
    fin.close();
    fout.close();
    return 0;
}