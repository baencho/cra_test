#pragma once
#include <string>
#define MAX_DAYS (7)
using namespace std;
enum eDay {
	eMonday = 0,
	eTuesday,
	eWednesday,
	eThursday,
	eFriday,
	eSaturday,
	eSunday,

	eDayError = MAX_DAYS
};
class Player
{
public:
	Player(string name, int id);
	string getName(void);
	int getId(void);
	int getGrade();

	void updateAttendance(int day);
	int getAttendance(int day);
	int calculateFinalPoint();
	bool checkGradeNormal();
	bool checkAttendanceNotEnough();

private:
	string name;
	int id;
	int attendPerDay[MAX_DAYS] = { 0, 0, 0, 0, 0, 0, 0 };
};