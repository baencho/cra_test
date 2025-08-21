#pragma once
#include <string>

using namespace std;
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
class Player
{
public:
	Player(string name, int id);
	string getName(void);
	int getId(void);
	int getGrade();

	void updatePoint(int day);
	void updateAttendance(int day);
	int getAttendance(int day);
	int calculateFinalPoint();
	bool checkGradeNormal();
	bool checkAttendanceNotEnough();

private:
	string name;
	int id;
	int finalPoint;
	int attendPerDay[7] = { 0, 0, 0, 0, 0, 0, 0 };
};