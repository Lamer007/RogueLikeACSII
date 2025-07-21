#include <string> 

#include "Character.h" 

using namespace std;

Character::Character() 
{
	this->hp = 0;
	this->armor = 0;
	this->currentArmor = 0;
	this->damage = 0;
	this->name = "void";
}

Character::Character(string name) 
{
	this->name = name;
	this->hp = 100;
	this->armor = 10;
	this->currentArmor = 0;
	this->damage = 10;
}

Character::Character(float hp, float armor, float currentArmor, float damage, string name)
{
	this->hp = hp;
	this->armor = armor;
	this->currentArmor = currentArmor;
	this->damage = damage;
	this->name = name;
}

void Character::setHp(float hp)
{ 
	if (hp < 0)
	{
		hp = 0;
	}

	this->hp = hp;
}
void Character::setArmor(float armor) { this->armor = armor; }
void Character::setCurrentArmor(float currentArmor) { this->currentArmor = currentArmor; }
void Character::setDamage(float damage) { this->damage = damage; }
void Character::setName(string name) { this->name = name; }

float Character::getHp() { return this->hp; }
float Character::getArmor() { return this->armor; }
float Character::getCurrentArmor() { return this->currentArmor; }
float Character::getDamage() { return this->damage; }
string Character::getName() { return this->name; }