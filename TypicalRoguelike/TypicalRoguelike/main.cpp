#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <chrono>
#include <thread>

#include "Character.h"
#include "Hero.h"
#include "Enemy.h"
#include "Printer.h"
#include "BattleRoom.h"
#include "TreasureRoom.h" 

using namespace std;

bool ifZeroHp(vector<Enemy>& groupOfEnemies)
{
	float enemiesHp = 0;

	for (int i = 0; i < groupOfEnemies.size(); i++)
	{
		enemiesHp += groupOfEnemies[i].getHp();
	}

	if (enemiesHp == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int main()
{
	srand(time(0));
	Printer printer;
	TreasureRoom treasureRoom;
	BattleRoom battleRoom = BattleRoom();
	string answer;

	cout << "To display ASCII images correctly, please, open the application in full screen." << endl;

	printer.printASCII("logo.txt");
	
	cout << "Welcome to Typical Roguelike, please, choose option: " << endl;

	while (true) 
	{

		cout << "1. Start new game" << endl << "2. Load save" << endl << "3. Exit" << endl;
		cin >> answer;

		if ((answer == "1") || (answer == "2"))
		{
			bool gameRun = true;
			Hero hero;

			if (answer == "1")
			{
				cout << endl << "Type name of your character: " << endl;
				cin >> answer;
				hero = Hero(answer);
			}
			else
			{
				vector<string> saves;
				string line = "";
				bool flag = true;

				ifstream inFile;
				inFile.open("saves.txt");

				if (inFile.is_open())
				{
					while (getline(inFile, line))
					{
						saves.push_back(line);
					}	
				}
				else
				{
					cout << "Save file load failed! Check the integrity of your files." << endl;
					system("pause");
					flag = false;
					gameRun = false;
				}
				inFile.close();

				if (saves.size() == 0)
				{
					cout << "Save file is empty." << endl;
					system("pause");
					flag = false;
					gameRun = false;
				}

				while (flag)
				{
					system("cls");
					cout << "Choose save: " << endl;

					for (int i = 0; i < saves.size(); i++)
					{
						cout << i + 1 << ". " << saves[i] << endl;
					}

					cin >> answer;

					if (!answer.empty() && find_if(answer.begin(),
						answer.end(), [](unsigned char c) { return !isdigit(c); }) == answer.end())
					{
						if ((stoi(answer) > 0) && (stoi(answer) <= saves.size()))
						{
							auto ss = istringstream(saves[stoi(answer) - 1]);
							vector<string> save;

							while (getline(ss, line, ' '))
							{
								save.push_back(line);
							}
							hero = Hero(stoi(save[1]), stoi(save[2]), stof(save[3]), stof(save[4]), stof(save[5]), stof(save[6]), save[0]);
							break;
						}
						else
						{
							cout << "Incorrect answer, plese type save's number 1/2/3 etc." << endl;
							system("pause");
						}
					}
					else
					{
						cout << "Incorrect answer, plese type save's number 1/2/3 etc." << endl;
						system("pause");
					}
				}
			}

			while (gameRun)
			{
				system("cls");
				cout << "You found two doors, choose in which you go:" << endl << "1. Left one is noisy (guaranteed battle)." << endl
					<< "2. Right one is silent (treasure or difficult battle)." << endl << "3. Quit game" << endl;
				cin >> answer;
				int chance = rand() % 2;

				if ((answer == "1") || ((answer == "2") && (chance == 0)))
				{
					
					cout << endl << "A battle!" << endl;

					vector<Enemy> groupOfEnemies = battleRoom.enemiesGeneration(hero.getDifficulty() + 5 * (stoi(answer) - 1));
					vector<string> enemiesNames;

					for (int i = 0; i < groupOfEnemies.size(); i++)
					{
						enemiesNames.push_back(groupOfEnemies[i].getName());
					}

					system("pause");

					while (true)
					{
						system("cls");
						hero.setCurrentArmor(0);
						int turns = groupOfEnemies.size();

						printer.printBattleRoom(enemiesNames);
						cout << endl << "Monsters: " << endl;

						for (int i = 0; i < groupOfEnemies.size(); i++)
						{
							cout << i + 1 << ". ";
							groupOfEnemies[i].getInfo();
							cout << endl;
						}

						cout << endl << "Your stats: " << endl << "HP: " << hero.getHp() << endl
							<< "Armor: " << hero.getCurrentArmor() << " (+" << hero.getArmor() << " per turn)" << endl << "Damage: " << hero.getDamage() << endl;
						
						for (int i = 0; i < groupOfEnemies.size(); i++)
						{
							bool flag = false;

							while (true)
							{
								cout << endl << "Left turns: " << turns << endl << "Choose your action:" << endl << "1. Attack" << endl << "2. Protect" << endl;

								cin >> answer;

								if (answer == "1")
								{
									while (true)
									{
										system("cls");
										printer.printBattleRoom(enemiesNames);

										for (int i = 0; i < groupOfEnemies.size(); i++)
										{
											cout << i + 1 << ". " << groupOfEnemies[i].getName() << endl;
										}

										cout << "Choose the enemy you want to attack: " << endl;
										cin >> answer;

										if (!answer.empty() && find_if(answer.begin(),
											answer.end(), [](unsigned char c) { return !isdigit(c); }) == answer.end())
										{
											if ((stoi(answer) > 0) && (stoi(answer) <= groupOfEnemies.size()))
											{
												groupOfEnemies[stoi(answer) - 1].setCurrentArmor(groupOfEnemies[stoi(answer) - 1].getCurrentArmor() - hero.attack());

												if (groupOfEnemies[stoi(answer) - 1].getCurrentArmor() < 0)
												{
													groupOfEnemies[stoi(answer) - 1].setHp(groupOfEnemies[stoi(answer) - 1].getHp() + groupOfEnemies[stoi(answer) - 1].getCurrentArmor());
													groupOfEnemies[stoi(answer) - 1].setCurrentArmor(0);
												}

												cout << endl << groupOfEnemies[stoi(answer) - 1].getName() << " now has " << groupOfEnemies[stoi(answer) - 1].getHp()
													<< " hp and " << groupOfEnemies[stoi(answer) - 1].getCurrentArmor() << " armor." << endl;

												if (ifZeroHp(groupOfEnemies))
												{
													flag = true;
												}
												break;
											}
											else
											{
												cout << "Incorrect answer, plese type enemies's number 1/2/3 etc." << endl;
												system("pause");
											}
										}
										else
										{
											cout << "Incorrect answer, plese type enemies's number 1/2/3 etc." << endl;
											system("pause");
										}
									}
									break;
								}
								else if (answer == "2")
								{
									hero.setCurrentArmor(hero.getCurrentArmor() + hero.getArmor());
									cout << "Your armor now: " << hero.getCurrentArmor() << endl;
									break;
								}
								else
								{
									cout << endl << "Incorrect answer, please type 1/2." << endl;
									system("pause");
								}
							}

							if (flag)
							{
								break;
							}

							turns--;
						}

						system("pause");
						system("cls");

						if (ifZeroHp(groupOfEnemies))
						{
							cout << "You won!" << endl;
							hero.setDifficulty(hero.getDifficulty() + 1);
							
							int goldCalc = 0;
							for (int i = 0; i < groupOfEnemies.size(); i++)
							{
								goldCalc += groupOfEnemies[i].getDifficultyLevel() * 10;
							}

							hero += goldCalc;
							cout << endl << "You gained: " << goldCalc << " gold! Now you have: " << hero.getGold() << endl;

							system("pause");
							break;
						}

						printer.printBattleRoom(enemiesNames);

						for (int i = 0; i < groupOfEnemies.size(); i++)
						{
							if(groupOfEnemies[i].getHp() != 0)
							{
								groupOfEnemies[i].setCurrentArmor(0);
								chance = rand() % 4;

								if (chance > 0)
								{
									hero.setCurrentArmor(hero.getCurrentArmor() - groupOfEnemies[i].attack());

									if (hero.getCurrentArmor() < 0)
									{
										hero.setHp(hero.getHp() + hero.getCurrentArmor());
										hero.setCurrentArmor(0);
									}

									cout << endl << "You now have " << hero.getHp() << " hp and " << hero.getCurrentArmor() << " armor." << endl;
								}
								else
								{
									groupOfEnemies[i].setCurrentArmor(groupOfEnemies[i].getCurrentArmor() + groupOfEnemies[i].getArmor());
									cout << endl << groupOfEnemies[i].getName() << " protected. Now it's armor: " << groupOfEnemies[i].getCurrentArmor() << endl;
								}
								system("pause");
							}
							
						}

						if (hero.getHp() == 0)
						{
							system("cls");
							cout << endl << "You dead! You had: " << endl;
							hero.getInfo();
							printer.printASCII("gameover.txt");
							cout << endl << "Game over" << endl;
							gameRun = false;
							break;
						}
						
					}
				}
				else if ((answer == "2") && (chance == 1))
				{
					chance = rand() % 4;
					
					if (chance > 0)
					{
						treasureRoom.sanctuary(hero);
					}
					else
					{
						treasureRoom.shop(hero);
					}

					system("pause");
				}
				else if (answer == "3")
				{
					gameRun = false;
					while (true)
					{
						cout << "Do you want to save?" << endl << "1. Yes" << endl << "2. No" << endl;
						cin >> answer;

						if (answer == "1")
						{
							fstream outFile;
							outFile.open("saves.txt", ofstream::app);

							if(outFile.is_open())
							{
								string save = "";

								save.append(hero.getName() + " " + to_string(hero.getGold()) + " " + to_string(hero.getDifficulty()) + " " +
									to_string(hero.getHp()) + " " + to_string(hero.getArmor()) + " " + to_string(hero.getCurrentArmor()) +
									" " + to_string(hero.getDamage()));

								outFile << save << endl;

								cout << "Game saved!" << endl;
							}
							else
							{
								cout << "Save file load failed! Check the integrity of your files." << endl;
							}
							outFile.close();

							break; 
						}
						else if (answer == "2")
						{
							break;
						}
						else
						{
							cout << endl << "Incorrect answer, please type 1/2." << endl;
							system("pause");
						}
					}
				}
				else 
				{
					cout << endl << "Incorrect answer, please type 1/2/3." << endl;
					system("pause");
				}

			}
		}
		else if (answer == "3") 
		{
			cout << "See you!" << endl;
			break;
		}
		else 
		{
			cout << endl << "Incorrect answer, please type 1/2/3." << endl;
		}

	}

	system("pause");

	return 0;
}