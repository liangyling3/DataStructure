#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

class Square{
private:
	int size;
	vector< vector<int> > values;
	
public:
	Square(int size) {
		this->size = size;
		for (int i = 0; i < size; ++ i) {
			vector<int> temp;
			values.push_back(temp);
			for (int j = 0; j < size; ++ j) {
				values[i].push_back(0);
			} 
		}
	}
	
	Square & readValues() {
		for (int i = 0; i < size; ++ i) {
			for (int j = 0; j < size; ++ j) {
				cin >> values[i][j];
			}
		}
		return *this;
	}
	
	bool isMagicSquare() {
		int flag = 1, sum = 0;
		for (int i = 0; i < size; ++ i)
			sum += values[i][i];
		
		for (int i = 0; i < size; ++ i) {
			int sumOfRow = 0, sumOfColumn = 0;
			for (int j = 0; j < size; ++ j) {
				sumOfRow += values[i][j];
				sumOfColumn += values[j][i];
			} 
			if (sumOfRow != sum || sumOfColumn != sum) {
				flag = 0;
				break;
			}	
		}
		
		if (flag == 1) {
			int sumOfDiagonal = 0;
			for (int i = size-1, j = 0; i >= 0 && j < size; -- i, ++ j) 
				sumOfDiagonal += values[j][i];
			if (sumOfDiagonal != sum)	flag == 0;
		} 
		return flag; 
	}
};

int main() {
	int size;
	cout << "Please enter the size of the square." << endl;
	cin >> size;
	
	Square square(size);
	cout << "Please enter the values of the square." << endl;
	square.readValues();
	
	if(square.isMagicSquare()) {
		cout << "This is a magic square." << endl;
	}
	else {
		cout << "It's not a magic square." << endl;
	}
}
