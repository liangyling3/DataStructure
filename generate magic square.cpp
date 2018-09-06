#include <iostream>
#include <iomanip> 
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
	
	Square & toMagicSquare() {
		int num = 0, row = 1, col = (size-1) / 2 - 1;		//	initial numbers
		while(num < size*size) { 
			num ++, row --, col ++;
			if (row < 0)	row += size;
			if (col >= size)	col -= size;
		
			if (values[row][col] == 0)	{
				values[row][col] = num;	
			}
			else if (values[row][col] != 0 ) {
				row += 2;
				col --;
				if (row >= size)	row -= size;
				if (col < 0)	col += size;
				if (values[row][col] != 0)	break;
				else 
					values[row][col] = num;
			}	
			else	break;
		}
		
		return *this;
	}
	
	void print() {
		for (int i = 0; i < size; ++ i) {
			for (int j = 0; j < size; ++ j) {
				cout << setw(5) << values[i][j];
			}
			cout << endl;
		}
	}
};

int main() {
	int size;
	cout << "Please enter the size of the square.(odd number)" << endl;
	cin >> size;
	while (size % 2 == 0)	{
		cout << "Please reput a odd number.";
		cin >> size;
	}
	
	Square square(size);
	square.toMagicSquare();
	square.print();
}
