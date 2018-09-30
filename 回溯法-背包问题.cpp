#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

ostream & operator << (ostream & out, vector<int> &v) {
	for (int i = 0; i < v.size(); ++ i) {
		cout << setw(5) << v[i];
	}
	return out;
}

void thingsToBag(int total, vector<int> volumes, int index, vector<vector<int> > &fillWell) {
	static vector<int> temp;
	static int count = 0;
	if (total == 0)	{
		fillWell.push_back(temp);
		if(index - 1 < volumes.size()) {
			temp.pop_back();
		}
		count --;
		return;
	}
	for(int i = index; i < volumes.size(); ++ i) {
		if (total-volumes[i] < 0) {		
			continue;				
		}
		
		temp.push_back(volumes[i]); 
		count ++;
		thingsToBag(total-volumes[i], volumes, i+1, fillWell);
		
	}
	temp.pop_back();
	count --;
	return;
} 


int main() {
	cout << "Please input the total volume of the bag:" << endl << "    ";
	int total;
	cin >> total;
	
	cout << endl << "Please input the number of things:" << endl << "    ";
	int number;
	cin >> number;
	
	cout << endl << "Plese input the volume of each thing:" << endl << "    ";
	vector<int> volumes;  
	for(int i = 0; i < number; ++ i) {
		volumes.push_back(0);
		cin >> volumes[i];
	}
	
	vector<vector<int> > fillWell; 
	thingsToBag(total, volumes, 0, fillWell); 
	cout << endl << "The solutions are: " << endl;
	for (int i = 0; i < fillWell.size(); ++ i) {
		cout << fillWell[i];
		cout << endl;
	}
}
