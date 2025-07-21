#pragma once

#include <string> 

using namespace std;

class Character 
{
private:
	float hp, armor, currentArmor, damage;
	string name;
public:
	Character();
	Character(string name);
	Character(float hp, float armor, float currentArmor, float damage, string name);

	void setHp(float hp);
	void setArmor(float armor);
	void setCurrentArmor(float currentArmor);
	void setDamage(float damage);
	void setName(string name);

	float getHp();
	float getArmor();
	float getCurrentArmor();
	float getDamage();
	string getName();

	virtual float attack() = 0;
	virtual void getInfo() = 0;
};