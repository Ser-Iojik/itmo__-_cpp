#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#define SIZE 100000

class Node {
    friend class HashTable;
    private:
        Node* next;
        int data;
    public:
        Node(int d, Node* n) {
            data = d;
            next = n;
        }
};

class HashTable {
public:
    int size;
    vector<Node*>* Nodes;
    HashTable(int s) {
        size = s;
        Nodes = new vector<Node*>(size);
    }

    void insert(int data) {
        int index = getHashByDivision(data);
        if (Nodes -> at(index) == NULL) {
            Nodes -> at(index) = new Node(data, NULL);
            return;
        }
        Node* p = Nodes -> at(getHashByDivision(data));
        while (p != NULL){
            if (p -> next == NULL) {
                p -> next = new Node(data, NULL);
                break;
            }
            p = p -> next;
        }
    }
    
    int getSize() {
        return size;
    }

    int getHashByDivision(int key) {
        return (key % getSize());
    }

    int exists(int data) {
        for (Node* pos = Nodes -> at(getHashByDivision(data)); pos; pos = pos -> next) {
            if (pos -> data == data)
                return 1;
        }
        return 0;
    }

    int del(int data) {
        for (Node* pos = Nodes -> at(getHashByDivision(data)); pos; pos = pos -> next) {
            if (pos -> data == data)
               Nodes -> at(data) = new Node(0, NULL);
        }
    }

    // void print(int start) {
    //     ofstream fout("setout.txt");
    //     int lineCount = 0;
    //     for (int i = start; i < Nodes -> size(); i++){
    //         fout << i << "\t";
    //         Node* p = Nodes -> at(i);
    //         while (p != NULL){
    //             fout << p -> data << " ";
    //             p = p -> next;
    //         }
    //         fout << endl;
    //     }
    // }

};

int main() {
    ifstream fin("set.in");
    ofstream fout("set.out");
    // ifstream fin("setin.txt");
    // ofstream fout("setout.txt");
    
    HashTable* hash = new HashTable(SIZE);

    string command;
    while(fin >> command) {
            if (command == "insert") {
                int Num;
                fin >> Num;
                // if (hash -> exists(Num) == 0) {
                    hash -> insert(Num);
                // } else if (hash -> exists(Num) == 1) {
                //     continue;
                // }
        } else if (command == "delete") {
            int Num;
            fin >> Num;
            hash -> del(Num);
            // if (hash -> exists(Num) == 1) {
            //     hash -> del(Num);
            // }
        } else if (command == "exists") {
            int Num;
            fin >> Num;
            hash -> exists(Num);
            if (hash -> exists(Num) == 1) {
                fout << "true" << endl;
            } else if (hash -> exists(Num) == 0) {
                fout << "false" << endl;
            }
        }
    }

    // hash -> print(0);

    return 0;
}