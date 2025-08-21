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
#define OP_TEST (0)

class StringConverter {
private:
	StringConverter() {}
public:
	static StringConverter* getInstance() {
		static StringConverter stringConverter;
		return &stringConverter;
	}

	string getGradeInString(int grade)
	{
		const string gradeString[3] = { "NORMAL" , "GOLD", "SILVER" };
		return gradeString[grade];
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
};

class AttendanceManager
{
public:
	map<string, Player*> playerMap;

	Player* getPlayer(string name)
	{
		if (playerMap.count(name) == 0) {
			//insert in map
			playerMap.insert({ name, new Player(name, playerMap.size() + 1) });
		}
		return playerMap[name];
	}

	void updateAttendance(string name, string dayInString) {
		int dayInInt = StringConverter::getInstance()->convertDayStringToInt(dayInString);
		Player* player = getPlayer(name);
		player->updateAttendance(dayInInt);
	}

	void printPointAndGrade() {
		for (auto iter = playerMap.begin(); iter != playerMap.end(); iter++)
		{
			Player* player = iter->second;
			cout << "NAME : " << player->getName() << ", ";
			cout << "POINT : " << player->calculateFinalPoint() << ", ";
			cout << "GRADE : " << StringConverter::getInstance()->getGradeInString(player->getGrade()) << "\n";
		}
		std::cout << "\n";
	}

	void printRemovedPlayers() {
		std::cout << "Removed player\n";
		std::cout << "==============\n";
		for (auto iter = playerMap.begin(); iter != playerMap.end(); iter++)
		{
			Player* player = iter->second;
			if (player->checkGradeNormal() && player->checkAttendanceNotEnough()) {
				std::cout << player->getName() << "\n";
			}
		}
	}

	int getPlayerMapSize() {
		return playerMap.size();
	}
};

void input(string filename) {
	AttendanceManager manager;
	ifstream fin{ filename }; //500개 데이터 입력
	for (int i = 0; i < 500; i++) {
		string name, attendDay;
		fin >> name >> attendDay;
		manager.updateAttendance(name, attendDay);
	}

	manager.printPointAndGrade();
	manager.printRemovedPlayers();
}

class TestFixture : public ::testing::Test
{
public:
	AttendanceManager* manager;
	void SetUp() override {
		manager = new AttendanceManager();
	}

	void TearDown() override {
		delete(manager);
	}

	void getInputAndUpdateAttendance() {
		string filename = "C:\\Users\\User\\Desktop\\test\\mission2\\mission2\\attendance_weekday_500.txt";;
		ifstream fin{ filename }; //500개 데이터 입력
		for (int i = 0; i < 500; i++) {
			string name, attendDay;
			fin >> name >> attendDay;
			manager->updateAttendance(name, attendDay);
		}
	}
};

// Test 정의
TEST_F(TestFixture, CheckRemovedPlayersRight)
{
	testing::internal::CaptureStdout();
	
	string filename = "attendance_weekday_500.txt";
	input(filename);

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
	Player* player = manager->getPlayer("Ian");
	Player* player2 = manager->getPlayer("Ian"); // expect same id
	Player* player3 = manager->getPlayer("Susan");

	EXPECT_EQ(1, player->getId());
	EXPECT_EQ(1, player2->getId());
	EXPECT_EQ(2, player3->getId());
	EXPECT_EQ(2, manager->getPlayerMapSize());
}

TEST_F(TestFixture, CheckUpdateAttendance)
{
	manager->updateAttendance("Harry", "wednesday");

	EXPECT_EQ(1, manager->getPlayerMapSize());
	EXPECT_EQ("Harry", manager->getPlayer("Harry")->getName());
	EXPECT_EQ(1, manager->getPlayer("Harry")->getId());
	EXPECT_EQ(1, manager->getPlayer("Harry")->getAttendance(eWednesday));
}

TEST_F(TestFixture, CheckAttendanceInputWellManaged)
{
	getInputAndUpdateAttendance();

	EXPECT_EQ(19, manager->getPlayerMapSize());
}

TEST_F(TestFixture, CheckPointWellCalculated)
{
	getInputAndUpdateAttendance();

	EXPECT_EQ(19, manager->getPlayerMapSize());
	EXPECT_EQ(127, manager->playerMap["Hannah"]->calculateFinalPoint());
}

TEST_F(TestFixture, CalculateOnceTest)
{
	getInputAndUpdateAttendance();

	EXPECT_EQ(19, manager->getPlayerMapSize());
	EXPECT_EQ(127, manager->playerMap["Hannah"]->calculateFinalPoint());
}

TEST_F(TestFixture, CheckGradeWellCalculated)
{
	getInputAndUpdateAttendance();

	EXPECT_EQ(19, manager->getPlayerMapSize());
	EXPECT_EQ(eGold, manager->playerMap["Hannah"]->getGrade());
	EXPECT_EQ(eSilver, manager->playerMap["George"]->getGrade());
	EXPECT_EQ(eNormal, manager->playerMap["Quinn"]->getGrade());
}

TEST_F(TestFixture, CheckGradeNormal)
{
	Player p("Jonh", 0);
	p.updateAttendance(eWednesday);
	p.updateAttendance(eWednesday);
	p.updateAttendance(eWednesday);
	p.updateAttendance(eWednesday);
	p.updateAttendance(eWednesday);
	p.updateAttendance(eWednesday);
	p.updateAttendance(eWednesday);
	p.updateAttendance(eWednesday);
	p.updateAttendance(eWednesday);
	p.updateAttendance(eWednesday);
	EXPECT_EQ(false, p.checkGradeNormal());	
}

TEST_F(TestFixture, CheckAttendanceNormal)
{
	Player p("Jonh", 0);
	p.updateAttendance(eWednesday);
	p.updateAttendance(eWednesday);
	p.updateAttendance(eWednesday);
	
	EXPECT_EQ(false, p.checkAttendanceNotEnough());
}
int main() {
#if (OP_TEST)
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
#else
	string filename = "attendance_weekday_500.txt";
	input(filename);
#endif
}