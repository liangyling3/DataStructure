#include <iostream>
#include <cmath>
#include <ctime>
using namespace std;

int OrdinaryMethod(int exp, int num, int coefficient[]) {
	int sumOfPolynomial = 0;
	for (int i = 0; i < exp+1; ++ i) {
		sumOfPolynomial += coefficient[i] * pow(num, i);
	}
	return sumOfPolynomial;
} 

int QinjiushaoMethod(int exp, int num, int coefficient[]) {
	int sumOfPolynomial = coefficient[exp];
	for (int i = exp-1; i >= 0; -- i) {
		sumOfPolynomial = sumOfPolynomial*num + coefficient[i];
	}
	return sumOfPolynomial;
} 

void getRunningTime(int (*f)(int exp, int num, int coefficient[]),
					int exp, int num, int coefficient[]) {
	clock_t start, stop;
	start = clock();
	int result;
	for (int i = 0; i < 10000000; ++ i) {			//	call the function repeatly to measure enough time
		result = f(exp, num, coefficient);
	}
	stop = clock();
	
	double duration = ((double)(stop - start)) / CLK_TCK;
	cout << "    " << "Result: " << result << endl;
	cout << "    " << "Time: " << duration << endl;
}

int main() {
	int exp, num;
	cout << "Please enter the max exponent." << endl;
	cin >> exp;
	cout << "Please enter the value of x."	<< endl;
	cin >> num;
	
	int *coefficient = new int [exp+1];
	for (int i = 0; i < exp+1; ++ i) {
		coefficient[i] = i;
	}
	
	cout << "Ordinary Method: "	<< endl;
	getRunningTime(OrdinaryMethod, exp, num, coefficient);
	cout << "Qinjiushao Method: " << endl;
	getRunningTime(QinjiushaoMethod, exp, num, coefficient); 
	
	delete [] coefficient;
} 
