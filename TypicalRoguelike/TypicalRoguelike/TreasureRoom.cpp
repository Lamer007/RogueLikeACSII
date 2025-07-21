#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "TreasureRoom.h" 
#include "Hero.h"

using namespace std;

void TreasureRoom::sanctuary(Hero& hero)
{
	system("cls");
	srand(time(0));
	
	int chance = rand() % 5;

	if (chance == 0)
	{
		int gold = 100 + rand() % 101;
		hero += gold;
		cout << endl << "You found chest with " << gold << " gold! Now you have: " << hero.getGold() << " gold!" << endl;
	}
	else if (chance == 1)
	{
		int health = 5 + rand() % 6;
		hero.setHp(hero.getHp() + health);
		cout << endl << "You found red bottle and drank it, you gained " << health << " hp! Now you have: " << hero.getHp() << " hp!" << endl;
	}
	else if (chance == 2)
	{
		int armor = 3 + rand() % 3;
		hero.setArmor(hero.getArmor() + armor);
		cout << "You found blue bottle and drank it, you gained " << armor << " armor per turn! Now you have: " << hero.getArmor() << " armor per turn!" << endl;
	}
	else if (chance == 3)
	{
		int damage = 4 + rand() % 4;
		hero.setDamage(hero.getDamage() + damage);
		cout << endl << "You found power-pill and ate it, you gained " << damage << " damage! Now you have: " << hero.getDamage() << " damage!" << endl;
	}
	else
	{
		cout << endl << "You found... Nothing? Good luck next time!" << endl;
	}
}

void TreasureRoom::shop(Hero& hero)
{
	string answer;

	while (true)
	{
		system("cls");
		cout << endl << "You found mysterious shop where for 100 gold you can buy:" << endl << "1. Unicorn horn (+5 hp)" << endl << "2. Lion claw (+4 damage)" << endl
			<< "3. Dragon scales (+3 armor per turn)" << endl << "(choose option 1/2/3 to buy and 0 if you want to leave)" << endl;

		cin >> answer;

		if (answer == "0")
		{
			cout << endl << "You left the shop." << endl;
			break;
		}
		else if (((answer == "1") || (answer == "2") || (answer == "3")) && (hero.getGold() >= 100))
		{
			if (answer == "1")
			{
				hero.setHp(hero.getHp() + 5);
				cout << endl << "You bought unicorn horn (+5 hp), now you have: " << hero.getHp() << " hp!" << endl;
			}
			else if (answer == "2")
			{
				hero.setDamage(hero.getDamage() + 4);
				cout << endl << "You bought lion claw (+4 damage), now you have: " << hero.getDamage() << " damage!" << endl;
			}
			else if (answer == "3")
			{
				hero.setArmor(hero.getArmor() + 3);
				cout << endl << "You bought dragon scales (+3 armor per turn), now you have: " << hero.getArmor() << " armor per turn!" << endl;
			}

			hero -= 100;
			cout << "Now you have " << hero.getGold() << " gold." << endl;
		}
		else if (((answer == "1") || (answer == "2") || (answer == "3")) && (hero.getGold() < 100))
		{
			cout << endl << "You do not have enouth gold!" << endl;
		}
		else
		{
			cout << endl << "Incorrect answer, please type 1/2/3." << endl;
		}

		system("pause");
		cin.get();
	}
}