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
	void addPoint(int value);
	int getGrade();
	void setGrade(int grade);
	

	void updatePoint(int day);
	void updateAttendance(int day);
	int getAttendance(int day);

private:
	string name;
	int id;
	int point;
	int grade;
	int attendPerDay[7] = { 0, 0, 0, 0, 0, 0, 0 };
};