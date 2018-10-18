#include <iostream>
#include <iomanip>
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
			cout << setw(5) << first->value;
			first = first->next; 
		}
		cout << endl; 
	}
};

int main() {
	Queue<char> queue;
	queue.push('C');
	queue.show();
	queue.push('O');
	queue.show();
	queue.push('M');
	queue.show();
	queue.push('P');
	queue.show();
	queue.push('U');
	queue.show();
	queue.push('T');
	queue.show();
	queue.push('E');
	queue.show();
	queue.push('R');
	queue.show();
	cout << endl;
	

	cout << endl << "The top value is : "<< queue.top() << endl;
	cout << endl << "Judge if the queue is empty : " << queue.empty() << endl << endl;
	
	for (int i = 0; i < 8; ++ i) {
		queue.pop();
		queue.show();
	}
	
	cout << endl << "Judge if the queue is empty : " << queue.empty() << endl << endl;	
	
}

