#include <fstream>
#include <iostream>

using namespace std;

struct SearchTree {
	int key = 0;
	SearchTree* parent = NULL;
	SearchTree* leftKid = NULL;
	SearchTree* rightKid = NULL;
};

bool check(SearchTree* tree, int min, int max) {
	if (tree == NULL)  return true;
	if ((tree->key <= min) || (max <= tree->key)) return false;
	return (check(tree->leftKid, min, tree->key) && check(tree->rightKid, tree->key, max));
}

bool isBinarySearchTree(SearchTree* tree) {
	return check(tree, -1000000001, 1000000001);
}

int main() {
	SearchTree* tree = new SearchTree[200001];
	int N, key, leftKid, rightKid;
	fstream in, out;
	in.open("check.in", ios::in);
	in >> N;
	int i;
	for (i = 0; i < N; i++) {
		in >> key >> leftKid >> rightKid;
		tree[i].key = key;
		if ((i != 0) && (tree[i].parent == NULL)) {
			i = -1;
			break;
		}
		if (leftKid != 0) {
			tree[i].leftKid = &tree[leftKid - 1];
			tree[leftKid - 1].parent = &tree[i];
		}
		if (rightKid != 0) {
			tree[i].rightKid = &tree[rightKid - 1];
			tree[rightKid - 1].parent = &tree[i];
		}

	}

	in.close();

	out.open("check.out", ios::out);
	if (i == -1) {
		out << "NO";
		out.close();
		return 0;
	};
	if (isBinarySearchTree(tree)) out << "YES";
	else out << "NO";
	out.close();
	return 0;
}