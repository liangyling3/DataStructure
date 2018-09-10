#include <iostream>
#include <vector>
#include <string> 
#include <iomanip> 
using namespace std;;

class Year{
private:
	vector< vector<int> > months;
	int firstDay;
	
public:
	Year(int year) {
		//	set firstDay
		if (year == 2000)	firstDay = 6;
		else
			firstDay = 6 + ((366*((year-2001)/4+1) + 365*((year-2001)/4*3+(year-2001)%4)) % 7);
		if (firstDay>7)	firstDay -= 7;
	 	
		//	set days
		for (int i = 1; i <= 12; ++ i) {
			vector<int> days;
			if (i == 4 or i == 6 or i == 9 or i == 11) {
				for (int j = 0; j < 30; ++ j)	days.push_back(j+1);
			}
			else if (i == 2) {
				for (int j = 0; j < 28; ++ j)	days.push_back(j+1); 
				if ((year%100) / 4 == 0)	days.push_back(29);
			}  
			else {
				for (int j = 0; j < 31; ++ j)	days.push_back(j+1);
			}
			months.push_back(days);
		}
	}
	
	void printCalendar() {
		//	print weeks
		cout << setw(11) << "Monday" 
			 << setw(11) << "Tuesday"
			 << setw(11) << "Wednesday"
			 << setw(11) << "Thursday"
			 << setw(11) << "Friday"
			 << setw(11) << "Saturday"
			 << setw(11) << "Sunday" << endl;
		
		//	print months
		int weekDay = firstDay;
		for (int i = 0; i < 12; ++ i) {
			switch(i+1){
				case 1:
					cout << "[January]" << endl;
					break;
				case 2:
					cout << "[February]" << endl;
					break;
				case 3:
					cout << "[March]" << endl;
					break;
				case 4:
					cout << "[April]" << endl;
					break;
				case 5:
					cout << "[May]" << endl;  
					break;
				case 6:
					cout << "[June]" << endl;
					break;
				case 7:
					cout << "[July]" << endl;
					break;
				case 8:
					cout << "[August]" << endl;
					break;
				case 9:
					cout << "[September]" << endl;
					break;
				case 10:
					cout << "[October]"	<< endl;
					break;
				case 11:
					cout << "[November]" << endl;
					break;
				case 12:
					cout << "[December]" << endl;
					break;
				}
			
			//	fill with days
			for (int k = 0; k < weekDay-1; ++ k)	cout << "           ";
			for (int j = 0; j < months[i].size(); ++ j) {
				cout << setw(11) << months[i][j];
				weekDay ++;
				if (weekDay > 7)	weekDay -= 7;
				if (weekDay == 1 or j == months[i].size()-1)	cout << endl;		
			}
		}
	}
};

int inputTime() {
	cout << "Please enter the year whose calendar you want to check:" << endl;
	int time;
	cin >> time;
	while (time < 2000 or time > 2100) {
		cout << "Your input is not in the range (2000-2100), please change it." << endl;
		cin >> time;
	}
	return time;
}

int main() {
	int time = inputTime();
	Year year(time);
	year.printCalendar();
}
