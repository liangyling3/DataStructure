#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

template <typename T>
class Node {
public:
	T value;
	Node<T> *next; 
	
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
		temp->next = 0;
		if (temp->next == 0)	delete temp->next; 
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
			cout << " " << first->value;
			first = first->next; 
		}
		cout << endl; 
	}

};

template <typename T>
class Queue {
private:
	Node<T> *head;		//	at the head of the queue
	Node<T> *tail;		//	at the end of the queue
	int count;
	
public:
	Queue() {
		head = 0;
		tail = 0;
		count = 0;
	}
	
	~Queue() {
		delete head;
		if (head != tail)	delete tail;
	}
	
	Queue & push(T value) {
		Node<T> *node = new Node<T>;	//	new a node
		node->value = value;
		node->next = head;
		if(tail != 0)	tail->next = node;
		tail = node;
		if (count == 0) head = tail;
		count ++; 
		return *this;
		
	}
	
	Queue & pop() {
		Node<T> *temp = head;
		head = head->next; 
		tail->next = head;
		count --;
		temp->next = 0;				//	avoid repeated release 
		if (temp->next == 0)	delete temp->next;
		return *this;
	}
	
	T top() {
		return head->value;
	}
	
	bool empty() {
		return count == 0;
	}
	
	void show() {								//	print values in the Queue
		Node<T> *first = head;
		for(int i = 0; i < count; ++ i) {
			cout << " " << first->value;
			first = first->next; 
		}
		cout << endl; 
	}
};


int main() {
	cout << "Please chose the type you want to use ('s' stand for stack; 'q' stand for queue) :" << endl;
	char c;
	cin >> c;
	while (c != 's' and c != 'q') {
		cout << "Please reinput the right char :" << endl;
		cin >> c;
	} 
	if (c == 's') {
		Stack<char> stack; 
		cout << "Plese input the number of values you want to put in the stack:" << endl;
		int size1;
		cin >> size1;
		cout << "Please input the values:" ;
		for (int i = 0; i < size1; ++ i) {
			char temp;
			cin >> temp;
			stack.push(temp);
			stack.show();
		}
		cout << endl;
		
		cout << "Please input the number of values which you want to pop in the stack:" << endl;
		int size2;
		cin >> size2;
		while (size2>size1 or size2 < 0) {
			cout << "Please input the number between 0 ~" << size1 << "." << endl;
			cin >> size2;
		}
		for (int i = 0; i < size2; ++ i)	{
			stack.pop();
			stack.show();
		}
		cout << endl;
	}
	
	if (c == 'q') {
		Queue<char> queue; 
		cout << "Plese input the number of values you want to put in the queue:" << endl;
		int size1;
		cin >> size1;
		cout << "Please input the values:";
		for (int i = 0; i < size1; ++ i) {
			char temp;
			cin >> temp;
			queue.push(temp);
			queue.show();
		}
		cout << endl;
		
		cout << "Please input the number of values which you want to pop in the queue:" << endl;
		int size2;
		cin >> size2;
		while (size2>size1 or size2 < 0) {
			cout << "Please input the number between 0 ~" << size1 << "." << endl;
			cin >> size2;
		}
		for (int i = 0; i < size2; ++ i)	{
			queue.pop();
			queue.show();
		}
		cout << endl;
	}
}

