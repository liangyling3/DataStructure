/*
example input:
	48
	10
	9     6    10    11     8     4     5     7    12    13
    11     6    12     9    14    10    13     8    15     7
*/

#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

class Good {
public:
	int volume;
	int value;
};

ostream & operator << (ostream & out, vector<int> &v) {
	for (int i = 0; i < v.size(); ++ i) {
		cout << setw(5) << v[i];
	}
	return out;
}

int getMaxValue(int total, const vector<Good> &goods, int index, vector<int> &maxGroup) {
	int value = 0, maxValue = 0;
	static vector<int> temp;
	
	if (total <= 0)	{
		if(index-1 < goods.size()) 	//	if the good isn't the last one, 
			temp.pop_back();			//	delete it and try the next good
		return 0;
	}
	
	for (int i = index; i < goods.size(); ++ i) {
		if (total-goods[i].volume < 0) 
			continue;
				
		temp.push_back(goods[i].volume);	
		value = goods[i].value + getMaxValue(total-goods[i].volume, goods, index+1, maxGroup);
		
		if (value > maxValue) {
			maxValue = value;
			maxGroup = temp;
		} 
	}
	temp.pop_back();					//	each time delete one element
	return maxValue;
}

int main() {
	int total, size;
	vector<Good> goods;
	vector<int> maxGroup;
	
	cout << "Please input the total volume of the bag:" << endl << "    ";
	cin >> total;
	
	cout << "Please input the number of the goods:" << endl << "    ";
	cin >> size;
	
	cout << "Please input the volumes of these goods:" << endl << "    ";
	for (int i = 0; i < size; ++ i) {
		Good temp;
		cin >> temp.volume;
		goods.push_back(temp);
	}
	
	cout << "Please input the values of these goods:" << endl << "    ";
	for (int i = 0; i < size; ++ i) {
		cin >> goods[i].value;
	}
	
	cout << "The max value is " << getMaxValue(total, goods, 0, maxGroup) << endl;
	cout << "The goods are :" << maxGroup << endl; 
}
