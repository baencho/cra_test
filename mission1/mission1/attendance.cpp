#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

#define MAX_PLAYERS (100)
#define MAX_DAYS (100)

struct Node {
	string name;
	string attendDay;
};

enum eDay {
	eMonday = 0,
	eTuesday,
	eWednesday,
	eThursday,
	eFriday,
	eSaturday,
	eSunday,

	eError = 7
};

map<string, int> idMap;
int idCount = 0;

//dat[사용자ID][요일]
int attendanceCountPerDay[MAX_PLAYERS][MAX_DAYS];
int points[MAX_PLAYERS];
int grade[MAX_PLAYERS];
string names[MAX_PLAYERS];

int wednesdayAttendance[100];
int weekendAttendance[100];

int getId(string name)
{
	// put given person in idMap and return his id
	if (idMap.count(name) == 0) {
		idMap.insert({ name, ++idCount });

		if (name == "Daisy") {
			int debug = 1;
		}

		names[idCount] = name;
	}
	return idMap[name];
}

int getPoint(int id, string day)
{
	int add_point = 0;
	int index = 0;
	if (day == "monday") {
		index = eMonday;
		add_point++;
	}
	if (day == "tuesday") {
		index = eTuesday;
		add_point++;
	}
	if (day == "wednesday") {
		index = eWednesday;
		add_point += 3;
		wednesdayAttendance[id] += 1;
	}
	if (day == "thursday") {
		index = eThursday;
		add_point++;
	}
	if (day == "friday") {
		index = eFriday;
		add_point++;
	}
	if (day == "saturday") {
		index = eSaturday;
		add_point += 2;
		weekendAttendance[id] += 1;
	}
	if (day == "sunday") {
		index = eSunday;
		add_point += 2;
		weekendAttendance[id] += 1;
	}

	return add_point;
}

eDay getAttendDay(string day)
{
	if (day == "monday") {
		return eMonday;
	}
	if (day == "tuesday") {
		return eTuesday;
	}
	if (day == "wednesday") {
		return eWednesday;
	}
	if (day == "thursday") {
		return eThursday;
	}
	if (day == "friday") {
		return eFriday;
	}
	if (day == "saturday") {
		return eSaturday;
	}
	if (day == "sunday") {
		return eSunday;
	}

	return eError;
}

void makeAttendanceAndPointTable(string name, string day) {
	//ID 부여
	int id = getId(name);

	//디버깅용
	if (name == "Daisy") {
		int debug = 1;
	}

	int add_point = getPoint(id, day);
	int index = getAttendDay(day);

	//사용자ID별 요일 데이터에 1씩 증가
	attendanceCountPerDay[id][index] += 1;
	points[id] += add_point;
}

void input() {
	ifstream fin{ "attendance_weekday_500.txt" }; //500개 데이터 입력
	for (int i = 0; i < 500; i++) {
		string name, attendDay;
		fin >> name >> attendDay;
		makeAttendanceAndPointTable(name, attendDay);
	}

	for (int i = 1; i <= idCount; i++) {
		if (attendanceCountPerDay[i][2] > 9) {
			points[i] += 10;
		}

		if (attendanceCountPerDay[i][5] + attendanceCountPerDay[i][6] > 9) {
			points[i] += 10;
		}

		if (points[i] >= 50) {
			grade[i] = 1;
		}
		else if (points[i] >= 30) {
			grade[i] = 2;
		}
		else {
			grade[i] = 0;
		}

		cout << "NAME : " << names[i] << ", ";
		cout << "POINT : " << points[i] << ", ";
		cout << "GRADE : ";

		if (grade[i] == 1) {
			cout << "GOLD" << "\n";
		}
		else if (grade[i] == 2) {
			cout << "SILVER" << "\n";
		}
		else {
			cout << "NORMAL" << "\n";
		}
	}

	std::cout << "\n";
	std::cout << "Removed player\n";
	std::cout << "==============\n";
	for (int i = 1; i <= idCount; i++) {

		if (grade[i] != 1 && grade[i] != 2 && wednesdayAttendance[i] == 0 && weekendAttendance[i] == 0) {
			std::cout << names[i] << "\n";
		}
	}
}

int main() {
	input();
}