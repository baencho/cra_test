#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <exception>
#include "gmock/gmock.h"
#include "player.h"
#include "grade.h"

using namespace std;
#define OP_TEST (1)

#define MAX_PLAYERS (100)
#define MAX_DAYS (7)


map<string, Player*> playerMap;

string getGradeInString(int grade)
{
	if (grade == eGold) {
		return "GOLD";
	}
	else if (grade == eSilver) {
		return "SILVER";
	}
	else {
		return "NORMAL";
	}
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

Player* getPlayer(string name)
{
	if (playerMap.count(name) == 0) {
		//insert in map
		playerMap.insert({ name, new Player(name, playerMap.size() + 1) });
	}
	return playerMap[name];
}

void updateAttendance(string name, string dayInString) {
	int dayInInt = convertDayStringToInt(dayInString);
	Player* player = getPlayer(name);
	player->updateAttendance(dayInInt);
}

void printPointAndGrade() {
	for (auto iter = playerMap.begin(); iter != playerMap.end(); iter++)
	{
		Player* player = iter->second;
		cout << "NAME : " << player->getName() << ", ";
		cout << "POINT : " << player->calculateFinalPoint() << ", ";
		cout << "GRADE : " << getGradeInString(player->getGrade()) << "\n";
	}
	std::cout << "\n";
}

bool checkGradeNormal(Player* player)
{
	int grade = player->getGrade();
	if (grade == eNormal) return true;
	return false;
}

bool checkAttendanceNotEnough(Player* player)
{
	int wednesdayAttendance = player->getAttendance(eWednesday);
	int weekendAttendance = player->getAttendance(eSaturday) + player->getAttendance(eSunday);
	if (wednesdayAttendance == 0 && weekendAttendance == 0) return true;
	return false;
}

void printRemovedPlayers() {
	std::cout << "Removed player\n";
	std::cout << "==============\n";
	for (auto iter = playerMap.begin(); iter != playerMap.end(); iter++)
	{
		Player* player = iter->second;
		if (checkGradeNormal(player) && checkAttendanceNotEnough(player)) {
			std::cout << player->getName() << "\n";
		}
	}
}
void input(string filename) {
	ifstream fin{ filename }; //500개 데이터 입력
	for (int i = 0; i < 500; i++) {
		string name, attendDay;
		fin >> name >> attendDay;
		updateAttendance(name, attendDay);
	}

	//addExtraAttendancePointsWithPlayerMap();

	// Print results
	printPointAndGrade();
	printRemovedPlayers();
}

void ResetAllData(){
	playerMap.clear();
}

class TestFixture : public ::testing::Test
{
	void SetUp() override {
		ResetAllData();
	}
};

// Test 정의
TEST_F(TestFixture, CheckRemovedPlayersRight)
{
	testing::internal::CaptureStdout();
	
	try {
		string filename = "attendance_weekday_500.txt";
		input(filename);
	}
	catch (exception e) {
		std::cout << e.what() << "\n";
	}

	string output = testing::internal::GetCapturedStdout();

	string line;
	ifstream answerFile("answer.txt");
	if (!answerFile.is_open()) {
		cerr << "Could not open the file" << endl;
	}

	while (getline(answerFile, line)) {
		EXPECT_THAT(output, ::testing::HasSubstr(line));
	}
}

TEST_F(TestFixture, CheckGetIdProcess)
{
	Player* player = getPlayer("Ian");
	Player* player2 = getPlayer("Ian"); // expect same id
	Player* player3 = getPlayer("Susan");

	EXPECT_EQ(1, player->getId());
	EXPECT_EQ(1, player2->getId());
	EXPECT_EQ(2, player3->getId());
	EXPECT_EQ(2, playerMap.size());
}

TEST_F(TestFixture, CheckUpdateAttendance)
{
	updateAttendance("Harry", "wednesday");
	EXPECT_EQ(1, playerMap.size());
	EXPECT_EQ("Harry", playerMap["Harry"]->getName());
	EXPECT_EQ(1, playerMap["Harry"]->getId());
	EXPECT_EQ(1, playerMap["Harry"]->getAttendance(eWednesday));
}

TEST_F(TestFixture, CheckAttendanceInputWellManaged)
{
	try {
		string filename = "attendance_weekday_500.txt";
		ifstream fin{ filename }; //500개 데이터 입력
		for (int i = 0; i < 500; i++) {
			string name, attendDay;
			fin >> name >> attendDay;
			updateAttendance(name, attendDay);
		}
	}
	catch (exception e) {
		std::cout << e.what() << "\n";
	}

	EXPECT_EQ(19, playerMap.size());
}

TEST_F(TestFixture, CheckPointWellCalculated)
{
	try {
		string filename = "attendance_weekday_500.txt";
		ifstream fin{ filename }; //500개 데이터 입력
		for (int i = 0; i < 500; i++) {
			string name, attendDay;
			fin >> name >> attendDay;
			updateAttendance(name, attendDay);
		}
	}
	catch (exception e) {
		std::cout << e.what() << "\n";
	}
	EXPECT_EQ(19, playerMap.size());
	EXPECT_EQ(127, playerMap["Hannah"]->calculateFinalPoint());
}

TEST_F(TestFixture, CalculateOnceTest)
{
	try {
		string filename = "attendance_weekday_500.txt";
		ifstream fin{ filename }; //500개 데이터 입력
		for (int i = 0; i < 500; i++) {
			string name, attendDay;
			fin >> name >> attendDay;
			updateAttendance(name, attendDay);
		}
	}
	catch (exception e) {
		std::cout << e.what() << "\n";
	}
	EXPECT_EQ(19, playerMap.size());
	EXPECT_EQ(127, playerMap["Hannah"]->calculateFinalPoint());
}

TEST_F(TestFixture, CheckGradeWellCalculated)
{
	try {
		string filename = "attendance_weekday_500.txt";
		ifstream fin{ filename }; //500개 데이터 입력
		for (int i = 0; i < 500; i++) {
			string name, attendDay;
			fin >> name >> attendDay;
			updateAttendance(name, attendDay);
		}
	}
	catch (exception e) {
		std::cout << e.what() << "\n";
	}
	EXPECT_EQ(19, playerMap.size());
	EXPECT_EQ(eGold, playerMap["Hannah"]->getGrade());
	EXPECT_EQ(eSilver, playerMap["George"]->getGrade());
	EXPECT_EQ(eNormal, playerMap["Quinn"]->getGrade());
}

int main() {
#if (1)
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
#else
	try {
		string filename = "attendance_weekday_500.txt";
		input(filename);
	}
	catch (exception e) {
		std::cout << e.what() << "\n";
	}
#endif
}