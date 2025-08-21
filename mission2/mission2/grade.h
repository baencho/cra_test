#pragma once

enum eGrade {
	eNormal = 0,
	eGold = 1,
	eSilver = 2
};

class IGrade {
public:
	virtual int getGrade() = 0;
protected:
	eGrade grade;
};

class PointGrade : public IGrade {
public:
	PointGrade(int point);
	int getGrade() override;
private:
	const int GOLD_MINIMUM_POINT = 50;
	const int SILVER_MINIMUM_POINT = 30;
	int point;
};