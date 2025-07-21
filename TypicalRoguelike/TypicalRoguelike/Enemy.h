#pragma once

#include "Character.h"
#include <string>

using namespace std;

class Enemy : public Character
{
private:
	int difficultyLevel;
public:
	Enemy();
	Enemy(int difficultyLevel, float hp, float armor, float currentArmor, float damage, string name);

	void setDifficultyLevel(int difficultyLevel);

	int getDifficultyLevel();

	virtual float attack() override;
	virtual void getInfo() override;
};