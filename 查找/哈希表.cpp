#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

class node {
 public:
 	int key;
 	vector<string> info;
 	node * next;

 	node() {
 		key = 0;
 		next = NULL;
 		for (int i = 0; i < 4; ++i) {
 			info.push_back("");
 		}
 	}

 	node(int key) {
 		this->key = key;
 		next = NULL;
 	}

 	~node() {
 		key = 0;
 		info.clear();
 		delete next;
 	}
};

ostream & operator << (ostream & out, const string & str) {
	int len = str.size();
	for (int i = 0; i < len; ++i) {
		out << str[i];
	}
	return out;
}

vector<vector<string> > readFromFile() {
	vector<vector<string> > data;

	ifstream infile;
	infile.open("AddressList.csv");

	if (!infile.is_open()) {
		cout << "No such file!" << endl;
		return data;
	} 

	string line;
	while (getline(infile, line)) {
		vector<string> personInfo;
		int len = line.size();
		int index = 0;
		for (int i = 0; i < len; ++i) {
			if (line[i] == ',') {
				personInfo.push_back(line.substr(index, i-index));
				index = i + 1;
			}
			else if (i == len-1) {
				personInfo.push_back(line.substr(index));
			}
		}
		data.push_back(personInfo);
	}

	infile.close();
	return data;
}

// reference to 'hashTable' is ambigugous:与库函数中的hash重名啦
node hashTable[120];
int exist[120];

void initial(const vector<vector<string> > & data) {
	int size = data.size();		// 人数

	// 关键码 = 姓名字母序数之和; 
	vector<int> keys(size);
	for (int i = 0; i < size; ++i) {
		string name = data[i][0];
		int sum = 0, len = name.size();
		for (int j = 0; j < len; ++j) {
			if (name[j] <= 'z' and name[j] >= 'a') 
				sum += name[j] - 'a';
			if (name[j] <= 'Z' and name[j] >= 'A')
				sum += name[j] - 'A';
		}
		keys[i] = sum;
	}

	// 构造哈希表
	for (int i = 0; i < size; ++i) {
		int index = keys[i] % 100;
		if (exist[index] == 0) {
			hashTable[index].key = keys[i];
			hashTable[index].info = data[i];
			hashTable[index].next = NULL;
			exist[index] = 1;
		}
		else {	// 冲突
			node * p = &hashTable[index];
			while (p->next != NULL) {
				p = p->next;
			}
			node * temp = new node(keys[i]);
			p->next = temp;
		}
	}
}

void printNode(const node & node) {
	cout << "["  << setw(2) << node.key << "]";
	cout << setw(15) << node.info[0];
	cout << setw(12) << node.info[1];
	cout << setw(12) << node.info[2];
	cout << setw(15) << node.info[3];
	cout << endl;
}

void printHash(node * hashTable) {
	for (int i = 0; i < 120; ++i) {
		printNode(hashTable[i]);
		node * p = &hashTable[i];
		while (p->next != NULL) {
			cout << "    ";
			printNode(*(p->next));
			p = p->next;
		}
	}
}

void searching(const string & name) {
	int len = name.size();
	int key = 0;
	for (int i = 0; i < len; ++i) {
		if (name[i] <= 'z' and name[i] >= 'a')
			key += name[i] - 'a';
		if (name[i] <= 'Z' and name[i] >= 'A')
			key += name[i] - 'A';
	}
	int index = key % 100;
	node * p = &hashTable[index];
	int tag = 0;
	while (p != NULL) {
		if (p->info[0] == name) {
			printNode(*p);
			tag = 1;
			break;
		}
		else {
			p = p->next;
		}
	}
	if (tag == 0) {
		cout << "No such person!" << endl;
	}
}

void insert(node & person) {
	string name = person.info[0];
	int len = name.size();
	int key = 0;
	for (int i = 0; i < len; ++i) {
		if (name[i] <= 'z' and name[i] >= 'a')
			key += name[i] - 'a';
		if (name[i] <= 'Z' and name[i] >= 'A')
			key += name[i] - 'A';
	}
	int index = key % 100;

	if (exist[index] == 0) {
			hashTable[index].key = key;
			hashTable[index].info = person.info;
			hashTable[index].next = NULL;
			exist[index] = 1;
		}
		else {	// 冲突
			node * p = &hashTable[index];
			while (p->next != NULL) {
				p = p->next;
			}
			node * temp = &person;
			p->next = temp;
		}
}

void remove(const string & name) {
	int len = name.size();
	int key = 0;
	for (int i = 0; i < len; ++i) {
		if (name[i] <= 'z' and name[i] >= 'a')
			key += name[i] - 'a';
		if (name[i] <= 'Z' and name[i] >= 'A')
			key += name[i] - 'A';
	}
	int index = key % 100;
	node * p = &hashTable[index];
	int tag = 0;
	while (p != NULL) {
		if (p->info[0] == name and p->next == NULL) {
			exist[index] = 0;
			hashTable[index].info.clear();
			hashTable[index].key = 0;
			break;
		}
		else if (p->info[0] == name and p->next != NULL) {
			p = p->next;
			break;
		}
		else {
			p = p->next;
		}		
	}
	if (tag == 0) {
		cout << "No such person!" << endl;
	}
}

void catalog() {
	cout << "- i        --initial the hashTable table" << endl;
	cout << "- p        --print the hashTable table" << endl;
	cout << "- s        --search for a person's information" << endl;
	cout << "- is       --insert a person's information" << endl;
	cout << "- rm       --remove a person's information" << endl;
	cout << "- q        --quit the program" << endl;
}

int main() {
	string opcode;
	catalog();
	while (cin >> opcode) {
		if (opcode == "i") {
			vector<vector<string> > data = readFromFile();
			initial(data);
		}
		if (opcode == "p") {
			printHash(hashTable);
		}
		if (opcode == "s") {
			cout << "Please input the name of the person." << endl;
			string str;
			cin >> str;
			searching(str);
		}
		if (opcode == "is") {
			node * p = new node;
			cout << "Please input the person's name, gender, studentId, phone in order." << endl;
			cin >> p->info[0] >> p->info[1] >> p->info[2] >> p->info[3];
			insert(*p);
		}
		if (opcode == "rm") {
			cout << "Please input the name of the person." << endl;
			string str;
			cin >> str;
			remove(str);
		}
		if (opcode == "q") {
			return 0;
		}
		catalog();
	}
}