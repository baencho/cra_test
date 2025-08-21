#include "grade.h"

PointGrade::PointGrade(int point)
{
	this->point = point;
}
int PointGrade::getGrade()
{
	if (point >= GOLD_MINIMUM_POINT) {
		return eGold;
	}
	else if (point >= SILVER_MINIMUM_POINT) {
		return eSilver;
	}
	else {
		return eNormal;
	}
	return grade;
}
