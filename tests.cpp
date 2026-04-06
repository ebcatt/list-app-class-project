#define CATCH_CONFIG_MAIN
#include <iostream>
#include "catch.hpp"
#include "main.cpp"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdio>

using namespace std;


//viewTasks sad path by Emily Catt
TEST_CASE("viewTasks sad path - empty vector"){
	vector<Task> tasks;

	stringstream buffer;
	streambuf* oldCout = cout.rdbuf(buffer.rdbuf());
	viewTasks(tasks);

	cout.rdbuf(oldCout);
	string output = buffer.str();

	REQUIRE(output.find("No tasks available.") != string::npos);
}


//viewTasks happy path by Emily Catt
TEST_CASE("viewTasks happy path - non-empty vector"){
        vector<Task> tasks = {
                {"1", "01/01/2025", "Work", false, 1},
                {"2", "02/02/2025", "Personal", true, 3}
        };

        stringstream buffer;
        streambuf* oldCout = cout.rdbuf(buffer.rdbuf());

        viewTasks(tasks);

        cout.rdbuf(oldCout);
        string output = buffer.str();

        REQUIRE(output.find("1") != string::npos);
        REQUIRE(output.find("2") != string::npos);
}


//filterByTag sad path by CW
TEST_CASE("filterByTag sad path - tag does not exist"){
        vector<Task> tasks = {
                {"1", "01/01/2025", "Work", false, 1},
                {"2", "02/02/2025", "Personal", true, 3}
        };

        stringstream buffer;
        streambuf* oldCout = cout.rdbuf(buffer.rdbuf());

	istringstream input("School\n");
	cin.rdbuf(input.rdbuf());

        filterByTag(tasks);

        cout.rdbuf(oldCout);
	cin.rdbuf(cin.rdbuf());
        string output = buffer.str();

        REQUIRE(output.find("No tasks found") != string::npos);
}

//filterByTag happy path by CW
TEST_CASE("filterByTag happy path - tag exsist"){
        vector<Task> tasks = {
                {"1", "01/01/2025", "Work", false, 1},
                {"2", "02/02/2025", "Personal", true, 3}
        };

        stringstream buffer;
        streambuf* oldCout = cout.rdbuf(buffer.rdbuf());

        istringstream input("Work\n");
        cin.rdbuf(input.rdbuf());

        filterByTag(tasks);

        cout.rdbuf(oldCout);
        cin.rdbuf(cin.rdbuf());
        string output = buffer.str();

        REQUIRE(output.find("1") != string::npos);
}

//saveFile sad path by S
TEST_CASE("saveFile sad path - empty vector"){
        vector<Task> tasks;

	saveFile(tasks);

	ifstream file("Tasks.txt");
	REQUIRE(file.is_open());

	string line;
	REQUIRE_FALSE(getline(file, line));

	file.close();
	remove("Tasks.txt");
}

//saveFile happy path by S
TEST_CASE("saveFile happy path - non-empty vector"){
        vector<Task> tasks = {
                {"1", "01/01/2025", "Work", false, 1},
                {"2", "02/02/2025", "Personal", true, 3}
        };

	saveFile(tasks);

	ifstream file("Tasks.txt");
	REQUIRE(file.is_open());

	string line;
	getline(file, line);
	REQUIRE(line.find("1") != string::npos);
	getline(file, line);
	REQUIRE(line.find("2") != string::npos);

	file.close();
	remove("Tasks.txt");
}



