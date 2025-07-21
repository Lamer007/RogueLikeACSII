#include <iostream>
#include <string>

#include "Enemy.h"

using namespace std;

Enemy::Enemy() 
{
	this->difficultyLevel = 0;
}

Enemy::Enemy(int difficultyLevel, float hp, float armor, float currentArmor, float damage, string name) :
	Character(hp, armor, currentArmor, damage, name) 
{
	this->difficultyLevel = difficultyLevel;
}

void Enemy::setDifficultyLevel(int difficultyLevel) { this->difficultyLevel = difficultyLevel; }

int Enemy::getDifficultyLevel() { return this->difficultyLevel; }

float Enemy::attack()
{
	cout << getName() << " attacked! You got " << getDamage() << " damage!" << endl;
	return getDamage();
}

void Enemy::getInfo()
{
	cout << endl << getName() << " lvl " << getDifficultyLevel() << endl << "HP: " << getHp() << endl
		<< "Armor: " << getCurrentArmor() << " (+" << getArmor() << " per turn)" << endl << "Damage: " << getDamage() << endl;
}