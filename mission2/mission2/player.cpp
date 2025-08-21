#include <string>
#include "player.h"
#include "grade.h"
using namespace std;

Player::Player(string name, int id) {
	this->name = name;
	this->id = id;
	this->point = 0;
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

int Player::getPoint(void) {
	return point;
}

void Player::addPoint(int value)
{
	point += value;
}

int Player::getGrade()
{
	return PointGrade(point).getGrade();
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