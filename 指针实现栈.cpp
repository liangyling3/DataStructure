#include <iostream>
#include <iomanip>
using namespace std;

template <typename T>
class Node {
public:
	T value;
	Node *next; 
	
	Node() {
		value = 0;
		next = 0;
	} 
	
	~Node() {
		delete next;
	}
};

template <typename T>
class Stack {
private:
	Node<T> *head;		//	the node at the top of the stack 
	int count;
	
public:
	Stack() {
		head = 0;
		count = 0;
	}
	
	~Stack() {
		delete head;
	}
	
	Stack & push(T value) {
		Node<T> *node = new Node<T>;	//	new a node
		node->value = value;
		node->next = head;
		head = node;
		count ++;
		return *this;
		
	}
	
	Stack & pop() {
		Node<T> *temp = head;
		head = head->next;
		delete temp->next;
		count --;
		return *this;
	}
	
	T top() {
		return head->value;
	}
	
	bool empty() {
		return count == 0;
	}
	
	void show() {								//	print values in the stack
		Node<T> *first = head;
		for(int i = 0; i < count; ++ i) {
			cout << setw(5) << first->value;
			if (first->next == 0)	break;
			first = first->next; 
		}
		cout << endl; 
	}
};

int main() {
	Stack<char> stack;
	
	stack.push('C');
	stack.show();
	stack.push('O');
	stack.show();
	stack.push('M');
	stack.show();
	stack.push('P');
	stack.show();
	stack.push('U');
	stack.show();
	stack.push('T');
	stack.show();
	stack.push('E');
	stack.show();
	stack.push('R');
	stack.show();
	cout << endl;
	
	for (int i = 0; i < 5; ++ i) {
		stack.pop();
		stack.show();
	}
	
	cout << endl << "The top value is : "<< stack.top() << endl;
	cout << endl << "Judge if the stack is empty : " << stack.empty() << endl;
	
}

