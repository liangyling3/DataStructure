#include <iostream>
#include <vector>
#include <stack>
#include <ctime>
#include <cstdlib>
#include <iomanip>
using namespace std;

vector<int> getArbitraryNumber (int size) {
	vector<int> arbitraryNumbers;
	srand((int)time(NULL));
	int * arr = new int [size];
	//	generate non-repeating arbitrary numbers by swaping
	for (int i = 0; i < size; ++ i)		arr[i]=i+1;
	for (int i = size-1; i >= 0; -- i)	swap(arr[i], arr[rand()%(i+1)]);
	for (int i = 0; i < size; ++ i)		arbitraryNumbers.push_back(arr[i]);
	delete [] arr;
	return arbitraryNumbers;
}


void sortByStack(vector<int> &unsortedNumbers) {
	vector<int> sortedNumbers;
	vector<stack<int> > instack;
	
	while (unsortedNumbers.size() != 0) {
		int isSorted = unsortedToSorted(unsortedNumbers, sortedNumbers);
		while (isSorted == 1) {
			int count = stackToSorted(instack, sortedNumbers);
			if(count == 0) break;
		}
		if (isSorted == 0) {
			unsortedToStack(unsortedNumbers, instack);
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
	
	unsortedNumbers = sortedNumbers;
}

int unsortedToSorted(vector<int> &unsortedNumbers, vector<int> &sortedNumbers) {
	int flag = 0;
	//	the first element
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
	return flag;
} 

int stackToSorted(vector<stack<int> > &instack, vector<int> &sortedNumbers) {
	int count = 0;
	for (int i = 0; i < instack.size(); ++ i) {
		if (instack[i].top() == (sortedNumbers[sortedNumbers.size()-1]+1)) {
			sortedNumbers.push_back(instack[i].top());
			instack[i].pop(); 
			count ++;
		}
		if (instack[i].empty())	instack.erase(instack.begin()+i);
	}
	return count;
}

void unsortedToStack(vector<int> &unsortedNumbers, vector<stack<int> > &instack) {
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


int main() {
	cout << "Please enter the size of the train: " << endl;  
	int size;
	cin >> size; 
	
	vector<int> trainNumbers = getArbitraryNumber(size);
	
	cout << "The arbitrary train numbers are :" << endl;
	for (int i = 0; i < size; ++ i) {
		cout << setw(5) << trainNumbers[i];
		if ((i+1)%15==0)	cout << endl;
	}
	cout << endl << endl; 
	
	cout << "The numbers sorted are :" << endl;
	sortByStack(trainNumbers);
	for (int i = 0; i < size; ++ i) {
		cout << setw(5) << trainNumbers[i];
		if ((i+1)%15==0)	cout << endl;
	}
	cout << endl;
	
}
