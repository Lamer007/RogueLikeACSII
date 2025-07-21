#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string> 
#include <vector>
#include <numeric>
#include <fstream>
#include <algorithm>
#include <sstream>

#include "BattleRoom.h"
#include "Enemy.h"
#include "Hero.h"

using namespace std;

BattleRoom::BattleRoom()
{
    string line = "";
    ifstream inFile;
    this->maxLevel = 0;
    vector<int> enemiesLevels;

    inFile.open("./txt/enemies.txt");

    if (inFile.is_open())
    {
        while (getline(inFile, line))
        {
            auto ss = istringstream(line);
            vector<string> vs;
            string line2;

            while (getline(ss, line2, ' '))
            {
                int currentLevel = stoi(line2);

                if (!enemiesLevels.empty()) 
                {
                    if (find(enemiesLevels.begin(), enemiesLevels.end(), currentLevel) == enemiesLevels.end()) 
                    {
                        enemiesLevels.push_back(currentLevel);
                    }
                }
                else {
                    enemiesLevels.push_back(currentLevel);
                }

                if (this->maxLevel < currentLevel)
                {
                    this->maxLevel = currentLevel;
                }
                break;
            }

        }
    }
    inFile.close();

    vector<vector<vector<string>>> pullOfEnemies(maxLevel + 1, vector<vector<string>>(0, vector<string>(0)));

    inFile.open("./txt/enemies.txt");

    if (inFile.is_open())
    {
        while (getline(inFile, line))
        {
            auto ss = istringstream(line);
            vector<string> vs;
            string line2;

            while (getline(ss, line2, ' '))
            {
                vs.push_back(line2);
            }
            pullOfEnemies[stoi(vs[0])].push_back(vs);
        }
    }
    inFile.close();

    this->enemiesLevels = enemiesLevels;
    this->pullOfEnemies = pullOfEnemies;

}

void generateCombinations(vector<int> arr, int size, int start, vector<int>& current, vector<vector<int>>& result, int difficulty)
{
    if (current.size() == size) {
        int sum = accumulate(current.begin(), current.end(), 0);
        if (sum == difficulty)
        {
            result.push_back(current);
        }
        return;
    }

    for (int i = 0; i < arr.size(); i++) {
        current.push_back(arr[i]);
        generateCombinations(arr, size, i, current, result, difficulty);
        current.pop_back();
    }
}

vector<int> splitNumber(int num, int n) {
    vector<int> result(n, num / n);

    for (int i = 0; i < num % n; ++i) {
        result[i] += 1;
    }

    return result;
}

vector<Enemy> BattleRoom::enemiesGeneration(int difficulty)
{
	srand(time(0));
    vector<vector<int>> combinations;
    vector<int> line;
    int size = 3;

    vector<int> additionalStatsV(size, 0);
    int additionalStats = 0;
    
    if (difficulty > this->maxLevel * 3)
    {
        additionalStats = difficulty - this->maxLevel * 3;
        difficulty = this->maxLevel * 3;

        additionalStatsV = splitNumber(additionalStats, size);
    }

    generateCombinations(enemiesLevels, size, 0, line, combinations, difficulty);

    line = combinations[rand() % combinations.size()];

    vector<Enemy> groupOfEnemies;
    
    for (int i = 0; i < line.size(); i++)
    {
        int enemiesNumber = rand() % (pullOfEnemies[line[i]].size());
        groupOfEnemies.push_back(Enemy(additionalStatsV[i] + line[i], stof(pullOfEnemies[line[i]][enemiesNumber][4]) + (additionalStatsV[i] * 5),
            stof(pullOfEnemies[line[i]][enemiesNumber][3]) + additionalStatsV[i], 0,
            stof(pullOfEnemies[line[i]][enemiesNumber][2]) + (additionalStatsV[i] * 2), pullOfEnemies[line[i]][enemiesNumber][1]));
    }

    return groupOfEnemies;
}