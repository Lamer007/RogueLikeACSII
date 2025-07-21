#pragma once

#include <string>
#include <vector>

using namespace std;

class Printer 
{
public:
	void printASCII(string fileName);
	void formatASCII(string fileName);
	void printBattleRoom(vector<string>& enemiesNames);
};
