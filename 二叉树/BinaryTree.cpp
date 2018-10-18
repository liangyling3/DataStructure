#include <iostream>
#include <queue>
#include <iomanip>
using namespace std;

typedef char Data;

class Node {
public:
	Data data;
	Node *left;
	Node *right;

	Node() {
		left = NULL;
		right = NULL;
	}
	~Node() {
		delete left;
		delete right;
	}
};


Node * input() {
	Data data;
	cin >> data;
	Node *p = 0;
	if(data != '#') {
		p = new Node;		// create a new node
		p->data = data;
		p->left = input();
		p->right = input();
	}
	return p;
}

void interchange(Node *p) {
	if (p != NULL) {
		Node *temp;
		temp = p->left;
		p->left = p->right;
		p->right = temp;
		interchange(p->left);
		interchange(p->right);
	}
}

void preorder(Node *p) {
	if(p!=NULL) {
		Data data;
		data = p->data;
		cout << data;
		preorder(p->left);
		preorder(p->right);
	}
}
void inorder(Node *p) {
	if(p!=NULL) {
		Data data;
		data = p->data;
		inorder(p->left);
		cout << data;
		inorder(p->right);
	}
}
void postorder(Node *p) {
	if (p!=NULL) {
		Data data;
		data = p->data;
		postorder(p->left);
		postorder(p->right);
		cout << data;
	}
}
void subCatalog() {
	cout << setw(5) << 'a' << "     ---- print the tree in preorder." << endl;
	cout << setw(5) << 'b' << "     ---- print the tree in inorder." << endl;
	cout << setw(5) << 'c' << "     ---- print the tree in postorder." << endl;
	cout << setw(5) << 'q' << "     ---- quit the show." << endl;
}
void show(Node *p) {
	subCatalog();
	char c;
	cin >> c;
	while (c != 'q') {
		if (c == 'a') {
			preorder(p);
			cout << endl;
		}
		if (c == 'b') {
			inorder(p);
			cout << endl;
		}
		if (c == 'c') {
			postorder(p);
			cout << endl;
		}
		cout << endl;
		subCatalog();
		cin >> c;
	}
}


void catalog() {
	cout << setw(5) << 's' << "     ---- show the tree." << endl;
	cout << setw(5) << 'i' << "     ---- interchange the tree." << endl;
	cout << setw(5) << 'q' << "     ---- quit the program." << endl;
}

int main() {
	Node *root = NULL;

	cout << "There is a binary tree." << endl;
	cout << setw(5) << 'i' << "     ---- input datas of the tree." << endl;
	cout << setw(5) << 'q' << "     ---- quit the program." << endl;
	
	char c;
	cin >> c;
	while (c != 'i' and c != 'q') {
		cout << "Please re-input." << endl;
		cin >> c;
	}
	if (c == 'i') {
		cout << endl << "Please input datas in pre order. " << endl;
		cout << "If the data is not exist, Please input a '#'." << endl;
		root = input();

		catalog();
		cin >> c;
		while (c != 'q') {
			if (c == 'i') interchange(root);
			if (c == 's') show(root);
			catalog();
			cin >> c;
		}
		if (c == 'q') return 0;
	}
	if (c == 'q') return 0;
}