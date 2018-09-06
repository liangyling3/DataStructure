#include <iostream>
#include <cmath>
using namespace std;

int getSizeOfNumbers(int num) {
	int count = 0;
	while (num != 0) {
		num /= 10;
		count ++;
	}
	return count;
}

//	judge if the size of numbers is mine cleavage number
bool isMineCleavage(int num) {
	int size = getSizeOfNumbers(num);
	int flag = 0;
	for (int i = 1; i < size; ++ i) {
		int multiple = pow(10, i);
		int subNum1 = num % multiple;
		int subNum2 = num / pow(10, i);
		int newNum = subNum1 + subNum2;
		if (newNum * newNum == num)	{
			flag = 1;
			break;
		}
	}
	return flag==1 ? 1 : 0;
}

int main() {
	for (int i = 10; i < 100000000; ++ i) {		//	two numbers
		if (isMineCleavage(i))	cout << "    " << i;
	}
}
