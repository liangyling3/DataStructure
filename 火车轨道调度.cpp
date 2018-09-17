#include <iostream>
#include <vector>
#include <stack>
#include <ctime>
#include <cstdlib>
#include <iomanip>
using namespace std;

vector<int> SortByStack(vector<int> unsortedNumbers) {
	vector<int> sortedNumbers;
	vector<stack<int> > instack;
	
	while (unsortedNumbers.size() != 0) {
		//	unsortedNumbers to sortedNumbers
		int flag = 0;
		if (sortedNumbers.size() == 0 && unsortedNumbers[0] == 1) {
			sortedNumbers.push_back(1);
			unsortedNumbers.erase(unsortedNumbers.begin());
			flag = 1;
		}	 
		else if (sortedNumbers.size() != 0 && (unsortedNumbers[0] == sortedNumbers[sortedNumbers.size()-1] + 1)) {
			sortedNumbers.push_back(unsortedNumbers[0]);
			unsortedNumbers.erase(unsortedNumbers.begin());
			flag = 1;
		}
		
		//	stack to sortedNumbers
		while (flag == 1) {
			int count = 0;
			for (int i = 0; i < instack.size(); ++ i) {
				if (instack[i].top() == (sortedNumbers[sortedNumbers.size()-1]+1)) {
					sortedNumbers.push_back(instack[i].top());
					instack[i].pop(); 
					count ++;
				}
				if (instack[i].empty())	instack.erase(instack.begin()+i);
			}
			if (count == 0)	break;
		}
		
		//	unsortedNumbers to stack
		if (flag == 0) {
			int count = 0;
			for (int i = 0; i < instack.size(); ++ i) {
				if (unsortedNumbers[0] < instack[i].top()) {
					instack[i].push(unsortedNumbers[0]);
					unsortedNumbers.erase(unsortedNumbers.begin());
					count = 1;
					break;
				}
			}	
			if (count == 0) {
				stack<int> s;
				instack.push_back(s);
				instack[instack.size()-1].push(unsortedNumbers[0]);
				unsortedNumbers.erase(unsortedNumbers.begin());
			}
		}
	}
	
	while (instack.size() != 0) {
		for (int i = 0; i < instack.size(); ++ i) {
			if (instack[i].top() == sortedNumbers[sortedNumbers.size()-1] + 1) {
				sortedNumbers.push_back(instack[i].top());
				instack[i].pop(); 
			}
			if (instack[i].empty())	instack.erase(instack.begin()+i); 
		}
	}
	
	return sortedNumbers;
}

vector<int> getArbitraryNumber (int size) {
	vector<int> arbitraryNumbers;
	srand((int)time(NULL));
	int * arr = new int [size];
	//	generate non-repeating arbitrary numbers by swaping
	for (int i = 0; i < size; ++ i)		arr[i]=i+1;
	for (int i = size-1; i >= 0; -- i) 	swap(arr[i], arr[rand()%(i+1)]);
	for (int i = 0; i < size; ++ i)		arbitraryNumbers.push_back(arr[i]);
	delete [] arr;
	return arbitraryNumbers;
}

int main() {
	cout << "Please enter the size of the train: " << endl;  
	int size;
	cin >> size; 
	
	vector<int> trainNumbers = getArbitraryNumber(size);
	
	cout << "The arbitrary train numbers are :" << endl;
	for (int i = 0; i < size; ++ i)
		cout << setw(5) << trainNumbers[i];
	cout << endl << endl; 
	
	cout << "The numbers sorted are :" << endl;
	vector<int> sortedNumbers = SortByStack(trainNumbers);
	for (int i = 0; i < size; ++ i) 
		cout << setw(5) << sortedNumbers[i];
	cout << endl;
}
