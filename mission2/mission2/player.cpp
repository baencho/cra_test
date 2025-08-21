#include <string>
#include "player.h"
#include "grade.h"
using namespace std;

Player::Player(string name, int id) {
	this->name = name;
	this->id = id;
	for (int i = 0; i < 7; i++)
	{
		this->attendPerDay[i] = 0;
	}
}

string Player::getName(void)
{
	return name;
}

int Player::getId(void) {
	return id;
}

int Player::getGrade()
{
	return PointGrade(calculateFinalPoint()).getGrade();
}

void Player::updatePoint(int day)
{
	const int pointPerDay[7] = { 1, 1, 3, 1, 1, 2, 2 };
	point += pointPerDay[day];
}

void Player::updateAttendance(int day)
{
	attendPerDay[day]++;
}

int Player::getAttendance(int day)
{
	return attendPerDay[day];
}

int Player::calculateFinalPoint()
{
	int finalPoint = 0;
	const int pointPerDay[7] = { 1, 1, 3, 1, 1, 2, 2 };
	for (int i = 0; i < 7; i++) {
		finalPoint += attendPerDay[i] * pointPerDay[i];
	}
	if (attendPerDay[eWednesday] > 9) finalPoint += 10;
	if (attendPerDay[eSaturday] + attendPerDay[eSunday] > 9) finalPoint += 10;

	return finalPoint;
}