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
		if (firstDay>7)		firstDay -= 7;
	 	
		//	set days
		for (int i = 1; i <= 12; ++ i) {
			vector<int> days;
			if (i == 4 or i == 6 or i == 9 or i == 11) {
				for (int j = 0; j < 30; ++ j)	days.push_back(j+1);
			}
			else if (i == 2) {
				for (int j = 0; j < 28; ++ j)	days.push_back(j+1); 
				if ((year%100) % 4 == 0)	days.push_back(29);
			}  
			else {
				for (int j = 0; j < 31; ++ j)	days.push_back(j+1);
			}
			months.push_back(days);
		}
	}
	
	string getDayOfWeek(int month, int day) {
		int weekDay = firstDay;
		for (int i = 1; i <= month; ++ i) {
			if (i < month) {
				for (int j = 0; j < months[i].size(); ++ j) {
					weekDay ++;
					if (weekDay > 7)	weekDay -= 7;
				}
			}
			else {
				for (int j = 0; j < day; ++ j) {
					weekDay ++;
					if (weekDay > 7)	weekDay -= 7;
				}
			} 
		}
		
		switch(weekDay) {
			case 1:	return "Monday";
			case 2:	return "Tuesday";
			case 3:	return "Wednesday";
			case 4:	return "Thursday";
			case 5: return "Friday";
			case 6: return "Saturday";
			case 7:	return "Sunday";
		}
	}
};

int main() {
	int time, month, day;
	cout << "Please enter the date (year, month, day)."  << endl;
	cin >> time >> month >> day; 
	Year year(time);
	cout << year.getDayOfWeek(month, day);
}
