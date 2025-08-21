#include <string>
#include "player.h"

using namespace std;

Player::Player(string name, int id) {
	this->name = name;
	this->id = id;
	this->grade = 0;
	memset(this->attendPerDay, 0, sizeof(int) * 7);
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
int Player::getGrade()
{
	return grade;
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