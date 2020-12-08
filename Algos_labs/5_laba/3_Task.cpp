#include <fstream>

using namespace std;

struct SearchTree
{
	int key = 0;
	SearchTree* parent = NULL;
	SearchTree* leftKid = NULL;
	SearchTree* rightKid = NULL;
};

SearchTree* Insert(SearchTree* tree, int key) {
	SearchTree* newElem = new SearchTree;
	newElem->key = key;
	if (tree == NULL) return newElem;
	SearchTree* next = tree;
	while (true) {
		if (newElem->key == next->key) return tree;
		if (newElem->key > next->key) {
			if (next->rightKid == NULL) {
				next->rightKid = newElem;
				newElem->parent = next;
				break;
			}
			else next = next->rightKid;
		}
		else if (newElem->key < next->key) {
			if (next->leftKid == NULL) {
				next->leftKid = newElem;
				newElem->parent = next;
				break;
			}
			else next = next->leftKid;
		}
	}
	return tree;
}

SearchTree* Search(SearchTree* tree, int key) {
	if (tree == NULL) return NULL;
	if (tree->key == key) return tree;
	if (key > tree->key) return Search(tree->rightKid, key);
	else if (key < tree->key) return Search(tree->leftKid, key);
}

SearchTree* SearchPlace(SearchTree* tree, int key) {
	if (tree == NULL) return NULL;
	SearchTree* next = tree;
	SearchTree* result = new SearchTree;
	while (true) {
		if (key == next->key) return next;
		if (key > next->key) {
			if (next->rightKid == NULL) {
				result->parent = next;
				result->key = key;
				return result;
			}
			else next = next->rightKid;
		}
		else if (key < next->key) {
			if (next->leftKid == NULL) {
				result->parent = next;
				result->key = key;
				return result;
			}
			else next = next->leftKid;
		}
	}
}

SearchTree* Min(SearchTree* tree) {
	while (tree->leftKid != NULL) tree = tree->leftKid;
	return tree;
}

SearchTree* Next(SearchTree* Elem) {
	if (Elem == NULL) return NULL;
	if (Elem->rightKid != NULL) return Min(Elem->rightKid);
	SearchTree* temp = Elem->parent;
	while ((temp != NULL) && (Elem->key > temp->key)) {
		Elem = temp;
		temp = temp->parent;
	}
	return temp;
}

SearchTree* Max(SearchTree* tree) {
	while (tree->rightKid != NULL) tree = tree->rightKid;
	return tree;
}

SearchTree* Prev(SearchTree* Elem) {
	if (Elem == NULL) return NULL;
	if (Elem->leftKid != NULL) return Max(Elem->leftKid);
	SearchTree* temp = Elem->parent;
	while ((temp != NULL) && (Elem->key < temp->key)) {
		Elem = temp;
		temp = temp->parent;
	}
	return temp;
}

SearchTree* Delete(SearchTree* tree, int key) {
	SearchTree* Elem = Search(tree, key);
	if (Elem == NULL) return tree;
	if (Elem->parent != NULL) {
		if ((Elem->leftKid == NULL) && (Elem->rightKid == NULL)) {				//if leaf
			if (Elem->parent->leftKid == Elem) Elem->parent->leftKid = NULL;
			else Elem->parent->rightKid = NULL;
			return tree;
		}

		else if ((Elem->leftKid == NULL) ^ (Elem->rightKid == NULL)) {			//if only one kid
			if (Elem->leftKid != NULL) {
				if (Elem->parent->leftKid == Elem) Elem->parent->leftKid = Elem->leftKid;
				else Elem->parent->rightKid = Elem->leftKid;
				Elem->leftKid->parent = Elem->parent;
			}
			else {
				if (Elem->parent->leftKid == Elem) Elem->parent->leftKid = Elem->rightKid;
				else Elem->parent->rightKid = Elem->rightKid;
				Elem->rightKid->parent = Elem->parent;
			}
			return tree;
		}
TwoKids:
		if ((Elem->leftKid != NULL) && (Elem->rightKid != NULL)) {				//if two kids
			SearchTree* temp = new SearchTree;
			temp = Min(Elem->rightKid);
			Elem->key = temp->key;
			if (temp->parent->leftKid == temp) {
				if (temp->rightKid != NULL) {									//if temp have kid
					temp->parent->leftKid = temp->rightKid;
					temp->rightKid->parent = temp->parent;
				}
				else temp->parent->leftKid = NULL;
			}
			else Elem->rightKid = temp->rightKid;
			return tree;
		}
	}
	else {																		//if root
		if ((Elem->leftKid == NULL) && (Elem->rightKid == NULL)) return NULL;	//if no kids

		else if ((Elem->leftKid == NULL) ^ (Elem->rightKid == NULL))			//if only one kid
			if (Elem->leftKid != NULL) {
				Elem->leftKid->parent = NULL;
				return Elem->leftKid;
			}
			else {
				Elem->rightKid->parent = NULL;
				return Elem->rightKid;
			}

		else if ((Elem->leftKid != NULL) && (Elem->rightKid != NULL)) goto TwoKids;		//if two kids
	}
}

int main()
{
	SearchTree* tree = NULL;
	SearchTree* temp = new SearchTree;
	int key;
	string command;
	fstream in, out;
	in.open("bstsimple.in", ios::in);
	out.open("bstsimple.out", ios::out);
	while (in >> command >> key)
	{
		if (command == "insert") tree = Insert(tree, key);
		else if (command == "delete") tree = Delete(tree, key);
		else if (command == "exists") 
			if (Search(tree, key) != NULL) out << "true\n";
			else out << "false\n";
		else if (command == "next") {
			temp = SearchPlace(tree, key);
			temp = Next(temp);
			if (temp != NULL) out << temp->key << '\n';
			else out << "none\n";
		}
		else if (command == "prev") {
			temp = SearchPlace(tree, key);
			temp = Prev(temp);
			if (temp != NULL) out << temp->key << '\n';
			else out << "none\n";
		}
	}

	in.close();
	out.close();
	return 0;
}