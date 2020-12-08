#include <fstream>
#include <iostream>

#define MAXN 1000

using namespace std;


struct ListNode {
	string key;
	string value;
	ListNode *next;
};

class Map {
private:
    ListNode *start;
public:
	Map() {
        start = new ListNode();
        start->value = "";
        start->key = "";
        start->next = NULL;
    }

    void Insert(string key, string value) {
        ListNode *newNode = Search(key);
        if (Search(key) == NULL) {
            ListNode *newNode = new ListNode;
            newNode->key = key;
            newNode->value = value;
            newNode->next = start->next;
            start->next = newNode;
        }
        else {
            ListNode *exNode = Search(key);
            exNode->value = value;
        }
    }

    void Delete(string key) {
        ListNode *curNode = start;

        while (curNode->next != NULL) {
            if (curNode->next->key == key) {
                ListNode *del = curNode->next;
                curNode->next = curNode->next->next;

                delete del;

                break;
            }
            else {
                curNode = curNode->next;
            }
        }
    }

    ListNode* Search(string key) {
        ListNode *curNode = start;

        while (curNode->next != NULL) {
            if (curNode->next->key == key) {
                return curNode->next;
            }
            else {
                curNode = curNode->next;
            }
        }

        return NULL;
    }
};

class UpgradeMap {
private:
    Map mp[MAXN];
public:
    int findID(string key) {
        unsigned int res = 0;
        unsigned int pow = 1;
        unsigned int p = 31;

        for(int i = 0; i < key.length(); i++) {
            res += (key[i] - 'A') * pow;
            pow *= p;
        }

        return res % MAXN;
    }

    void Put(string key, string value) {
        mp[findID(key)].Insert(key, value);
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
        mp[findID(key)].Delete(key);
    }
};

int main() {
	ifstream fin("map.in");
	ofstream fout("map.out");

	UpgradeMap mp;

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
