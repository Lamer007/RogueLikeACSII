#include <iostream> 
#include <string>

#include "Hero.h" 

using namespace std;

Hero::Hero() 
{
	this->gold = 0;
	this->difficulty = 0;
}

Hero::Hero(string name) : Character(name) 
{
	this->gold = 10;
	this->difficulty = 1;
}

Hero::Hero(int gold, int difficulty, float hp, float armor, float currentArmor, float damage, string name) :
	Character(hp, armor, currentArmor, damage, name) 
{
	this->gold = gold;
	this->difficulty = difficulty;
}

void Hero::setGold(int gold) { this->gold = gold; }
void Hero::setDifficulty(int difficulty) { this->difficulty = difficulty; }

int Hero::getGold() { return this->gold; }
int Hero::getDifficulty() { return this->difficulty; }

float Hero::attack() 
{
	cout << "Your attack dealing " << getDamage() << " damage!" << endl;
	return getDamage();
}

void Hero::getInfo()
{
	cout << "HP: " << getHp() << endl << "Damage: " << getDamage() << endl << "Armor: " << getArmor() << endl
		<< "Cleared rooms: " << getDifficulty() - 1 << endl << "Gold: " << getGold() << endl;
}

Hero& Hero::operator+=(int gold)
{
	setGold(getGold() + gold);
	return *this;
}

Hero& Hero::operator-=(int gold)
{
	setGold(getGold() - gold);
	return *this;
}