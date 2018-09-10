#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

void print(int arr[], int size) {
	for (int i = 0; i < size; ++ i) {
		cout << setw(5) << arr[i];
		if ((i+1) % 10 == 0)	cout << endl;
	}
	cout << endl << endl;
}

int * choseSort (int arr[], int size) {
	int *sortedArr = arr; 
	for (int i = 0; i < size; ++ i) {
		int min = sortedArr[i], index = i;
		for (int j = i+1; j < size; ++ j) {
			if (sortedArr[j] < min)	{
				min = sortedArr[j];
				index = j;
			}
		}
		sortedArr[index] = sortedArr[i];
		sortedArr[i] = min;
		print(sortedArr, size);
	}
}

int main() {
	cout << "Please enter the size of the arbitrary array." << endl; 
	int size;
	cin >> size;
	int *arr = new int [size];
	
	//	generate an array including arbitrary numbers between 1-1000
	srand((int)time(NULL));
	for (int i = 0; i < size; ++ i) {
		arr[i] = rand()%1000;
	} 
	
	cout << "The initial array:" << endl;
	print(arr, size);
	cout << "===========" <<  endl;
	
	cout << "Chosing Sort: " << endl << endl;
	int *sortedArr = choseSort(arr, size);
	cout << "-----------" << endl;
	
	delete [] arr;
} 
