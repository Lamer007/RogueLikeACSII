#pragma once

#include <string>

#include "Character.h"

using namespace std;

class Hero : public Character 
{
private:
	int gold, difficulty;
public:
	Hero();
	Hero(string name);
	Hero(int gold, int difficulty, float hp, float armor, float currentArmor, float damage, string name);

	void setGold(int gold);
	void setDifficulty(int difficulty);

	int getGold();
	int getDifficulty();

	virtual float attack() override;
	virtual void getInfo() override;

	Hero& operator +=(int gold);
	Hero& operator -=(int gold);
};