#include <fstream>
#include <iostream>

using namespace std;

struct SearchTree {
	int key = 0;
	SearchTree* parent = NULL;
	SearchTree* leftKid = NULL;
	SearchTree* rightKid = NULL;
	int height = 1;
};

int main() {
	SearchTree* tree = new SearchTree[200001];
	int N, key, leftKid, rightKid, maxHeight = 0;
	fstream in, out;
	in.open("height.in", ios::in);
	in >> N;
    // cin >> N;
	if (N == 1) maxHeight = 1;
	for (int i = 1; i <= N; i++) {
		in >> key >> leftKid >> rightKid;
        // cin >> key >> leftKid >> rightKid;
		tree[i].key = key; // int key = 0;
		if (leftKid != 0) {
			tree[i].leftKid = &tree[leftKid]; // 
			tree[leftKid].parent = &tree[i];
			tree[leftKid].height = tree[i].height + 1;
			if (tree[leftKid].height > maxHeight) maxHeight = tree[leftKid].height;
		}
		if (rightKid != 0) {
			tree[i].rightKid = &tree[rightKid];
			tree[rightKid].parent = &tree[i];
			tree[rightKid].height = tree[i].height + 1;
			if (tree[rightKid].height > maxHeight) maxHeight = tree[rightKid].height;
		}

	}
    // cout << maxHeight;
	in.close();

	out.open("height.out", ios::out);
	out << maxHeight;
	out.close();
    return 0;
}