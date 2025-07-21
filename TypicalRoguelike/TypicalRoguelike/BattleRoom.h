#pragma once

#include <iostream>
#include <string> 
#include <vector>

#include "Enemy.h"
#include "Hero.h"

using namespace std;

class BattleRoom 
{
private:
	
	vector<int> enemiesLevels;
	vector<vector<vector<string>>> pullOfEnemies;
	int maxLevel;
public:
	BattleRoom();

	vector<Enemy> enemiesGeneration(int difficulty);
};