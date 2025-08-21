#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <exception>
#include "gmock/gmock.h"

using namespace std;

#define OP_TEST (0)

#define MAX_PLAYERS (100)
#define MAX_DAYS (7)

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

	eDayError = 7
};

enum eGrade {
	eNormal = 0,
	eGold = 1,
	eSilver = 2
};

map<string, int> idMap;
int idCount = 0;

//dat[사용자ID][요일]
int attendanceCountPerDay[MAX_PLAYERS][MAX_DAYS + 1];
int points[MAX_PLAYERS];
int grade[MAX_PLAYERS];
string names[MAX_PLAYERS];

int wednesdayAttendance[MAX_PLAYERS];
int weekendAttendance[MAX_PLAYERS];

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

int getPoint(int id, int day)
{
	const int pointPerDay[MAX_DAYS] = { 1, 1, 3, 1, 1, 2, 2 };
	return pointPerDay[day];
}

eDay convertDayStringToInt(string day)
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

	return eDayError;
}

void updatePointTable(int id, int day) {
	if (id < 0 || id >= MAX_PLAYERS) throw exception("[updatePointTable] id overflow exception");
	if (day < eMonday || day >= eDayError) throw exception("[updatePointTable] day overflow exception");

	points[id] += getPoint(id, day);
}

void updateExtraAttendanceTable(int id, int day)
{
	if (id < 0 || id >= MAX_PLAYERS) throw exception("[updateExtraAttendanceTable] id overflow exception");
	if (day < eMonday || day >= eDayError) throw exception("[updateExtraAttendanceTable] day overflow exception");

	if (day == eWednesday) {
		wednesdayAttendance[id] += 1;
	}
	else if (day == eSaturday) {
		weekendAttendance[id] += 1;
	}
	else if (day == eSunday) {
		weekendAttendance[id] += 1;
	}
	else {
		// do nothing
	}
}

void updateAttendanceCountPerDayTable(int id, int day)
{
	if (id < 0 || id >= MAX_PLAYERS) throw exception("[updateAttendanceCountPerDayTable] id overflow exception");
	if (day < eMonday || day >= eDayError) throw exception("[updateAttendanceCountPerDayTable] day overflow exception");

	attendanceCountPerDay[id][day] += 1;
}

void updateAttendanceAndPointTable(string name, string dayInString) {
	int id = getId(name);

	//디버깅용
	if (name == "Daisy") {
		int debug = 1;
	}

	int dayInInt = convertDayStringToInt(dayInString);
	
	updatePointTable(id, dayInInt);

	updateExtraAttendanceTable(id, dayInInt);

	updateAttendanceCountPerDayTable(id, dayInInt);
}

void addExtraAttendancePoints()
{
	for (int id = 1; id <= idCount; id++) {
		if (attendanceCountPerDay[id][eWednesday] > 9) {
			points[id] += 10;
		}

		if (attendanceCountPerDay[id][eSaturday] + attendanceCountPerDay[id][eSunday] > 9) {
			points[id] += 10;
		}
	}
}

void updateGradeTable() {
	const int GOLD_MINIMUM_POINT = 50;
	const int SILVER_MINIMUM_POINT = 30;

	for (int id = 1; id <= idCount; id++) {
		if (points[id] >= GOLD_MINIMUM_POINT) {
			grade[id] = eGold;
		}
		else if (points[id] >= SILVER_MINIMUM_POINT) {
			grade[id] = eSilver;
		}
		else {
			grade[id] = eNormal;
		}
	}
}

string getGradeInString(int id)
{
	if (grade[id] == eGold) {
		return "GOLD";
	}
	else if (grade[id] == eSilver) {
		return "SILVER";
	}
	else {
		return "NORMAL";
	}
}

string getName(int id)
{
	return names[id];
}

int getPoint(int id)
{
	return points[id];
}

void printPointAndGrade() {
	for (int id = 1; id <= idCount; id++) {
		cout << "NAME : " << getName(id) << ", ";
		cout << "POINT : " << getPoint(id) << ", ";
		cout << "GRADE : " << getGradeInString(id) << "\n";
	}
	std::cout << "\n";
}

bool checkGradeNormal(int id)
{
	if (grade[id] != eGold && grade[id] != eSilver) return true;
	return false;
}

bool checkAttendanceNotEnough(int id)
{
	if (wednesdayAttendance[id] == 0 && weekendAttendance[id] == 0) return true;
	return false;
}

void printRemovedPlayers() {
	std::cout << "Removed player\n";
	std::cout << "==============\n";
	for (int id = 1; id <= idCount; id++) {
		if (checkGradeNormal(id) && checkAttendanceNotEnough(id)) {
			std::cout << getName(id) << "\n";
		}
	}
}

void input(string filename) {
	ifstream fin{ filename }; //500개 데이터 입력
	for (int i = 0; i < 500; i++) {
		string name, attendDay;
		fin >> name >> attendDay;
		updateAttendanceAndPointTable(name, attendDay);
	}

	addExtraAttendancePoints();

	updateGradeTable();

	// Print results
	printPointAndGrade();
	printRemovedPlayers();
}

int main() {
#if (1 == OP_TEST)
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
#else
	try {
		string filename = "attendance_weekday_500.txt";
		input(filename);
	}
	catch (exception e){
		std::cout << e.what() << "\n";
	}
#endif
}