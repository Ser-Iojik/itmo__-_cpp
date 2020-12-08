#include <fstream>
#include <iostream>

#define MAXN 1000

using namespace std;

struct ListNode {
	string key;
	string value;
	ListNode *nextInChain;
	ListNode *next;
	ListNode *prev;
};

class LinkedMap {
private:
    ListNode *start;
public:
	LinkedMap() {
        start = new ListNode();
        start->key = "";
        start->value = "";
        start->nextInChain = NULL;
    }

    void Insert(string key, string value, ListNode *Head) {
        ListNode *newNode = Search(key);

        if (Search(key) == NULL) {
            newNode = new ListNode;
            newNode->key = key;
            newNode->value = value;
            newNode->nextInChain = start->nextInChain;
            start->nextInChain = newNode;
            ListNode *Tail = Head->prev;
            Tail->next = newNode;
            Head->prev = newNode;
            newNode->next = Head;
            newNode->prev = Tail;
        }
        else {
            newNode->value = value;
        }
    }

    void Delete(string key, ListNode *Head) {
        ListNode *curNode = start;

        while (curNode->nextInChain != NULL) {
            if (curNode->nextInChain->key == key) {
                ListNode *del = curNode->nextInChain;
                curNode->nextInChain = curNode->nextInChain->nextInChain;
                ListNode *PrevListNode = del->prev, *NextListNode = del->next;
                del->prev->next = NextListNode;
                del->next->prev = PrevListNode;
                delete del;

                break;
            }
            else {
                curNode = curNode->nextInChain;
            }
        }
    }

    ListNode* Search(string key) {

        ListNode *curNode = start;

        while (curNode->nextInChain != NULL) {
            if (curNode->nextInChain->key == key) {
                return curNode->nextInChain;
            }
            else {
                curNode = curNode->nextInChain;
            }
        }

        return NULL;
    }
};

class UpgradeLinkedMap {
private:
    LinkedMap mp[MAXN];
	ListNode *Head;
public:
	UpgradeLinkedMap() {
        Head = new ListNode;
        Head->next = Head->prev = Head;
        Head->value = Head->key = "HEAD";
    }

    int findID(string key) {
        unsigned int result = 0;
        unsigned int power = 1;
        unsigned int p = 31;

        for(int i = 0; i < key.length(); i++) {
            result += (key[i] - 'A') * power;
            power *= p;
        }

        return result % MAXN;
    }

    void Put(string key, string value) {
        mp[findID(key)].Insert(key, value, Head);
    }

    string Get(string key) {

        ListNode *result = mp[findID(key)].Search(key);

        if (result == NULL) {
            return "none";
        }
        else {
            return result->value;
        }
    }

    void Delete(string key) {
        mp[findID(key)].Delete(key, Head);
    }

    string Next(string key) {

        ListNode *result = mp[findID(key)].Search(key); 

        if (result == NULL || result->next == Head) {
            return "none"; 
        }
        else {
            return result->next->value;
        }
    }

    string Prev(string key) {

        ListNode *result = mp[findID(key)].Search(key); 

        if (result == NULL || result->prev == Head) {
            return "none";
        }
        else {
            return result->prev->value;
        }
    }
};

int main() {
	ifstream fin("linkedmap.in");
	ofstream fout("linkedmap.out");

	UpgradeLinkedMap lm;

	string cmd;
	while (fin >> cmd) {
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
