#pragma once
#include <string>

using namespace std;

class Player
{
public:
	Player(string name, int id);
	string getName(void);
	int getId(void);
	int getPoint(void);
	int getGrade();
	
	int attendPerDay[7];

	void updatePoint(int day);
	void updateAttendance(int day);
	int getAttendance(int day);

private:
	string name;
	int id;
	int point;
	int grade;

	int attendWednesdayCount;
	int attendWeekendCount;
};