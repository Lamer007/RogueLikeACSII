#include <iostream>
#include <string>
#include <fstream>

#include "Printer.h" 

using namespace std;

void Printer::printASCII(string fileName)
{
	try
	{
		string line = "";
		ifstream inFile;
		inFile.open("./txt/" + fileName);
		if (inFile.is_open())
		{
			while (getline(inFile, line))
			{
				cout << line << endl;
			}
			cout << endl;
		}
		else
		{
			throw "File load failed";
		}

		inFile.close();
	}
	catch (...)
	{
		cout << "File load failed! Check the integrity of your files." << endl;
	}
}

void Printer::formatASCII(string fileName)
{
	try
	{
		string line = "";
		ifstream inFile;
		ofstream outFile;
		int maxLength = 0;

		inFile.open("./txt/" + fileName);
		outFile.open("./txt/reformator.txt");

		if (inFile.is_open() && outFile.is_open())
		{
			while (getline(inFile, line))
			{
				if (maxLength < line.size()) 
				{ 
					maxLength = line.size();
				}
			}

			inFile.clear();
			inFile.seekg(0);

			while (getline(inFile, line))
			{
				if (maxLength != line.size())
				{
					string spaces(maxLength - line.size(), ' ');
					line.append(spaces);

				}

				outFile << line << endl;
			}

			inFile.close();
			outFile.close();
			inFile.open("./txt/reformator.txt");
			outFile.open("./txt/" + fileName);

			while (getline(inFile, line))
			{
				outFile << line << endl;
			}
		}
		else
		{
			throw "File load failed!";
		}
		inFile.close();
		outFile.close();
	}
	catch (...)
	{
		cout << "File load failed! Check the integrity of your files." << endl;
	}
}


void Printer::printBattleRoom(vector<string>& enemiesNames)
{
	try
	{
		int maxLines = 0;

		for (int i = 0; i < enemiesNames.size(); i++)
		{
			formatASCII(enemiesNames[i] + ".txt");

			string line = "";
			int counter = 0;
			ifstream inFile;
			inFile.open("./txt/" + enemiesNames[i] + ".txt");

			if (inFile.is_open())
			{
				while (getline(inFile, line))
				{
					counter++;
				}

				if (maxLines < counter)
				{
					maxLines = counter;
				}
			}
			else
			{
				throw "File load failed";
			}

			inFile.close();
		}
		vector<string> battleRoom(maxLines, "");

		for (int i = 0; i < enemiesNames.size(); i++)
		{
			string line = "";
			int counter = 0;
			int lineLength = 0;
			ifstream inFile;
			inFile.open("./txt/" + enemiesNames[i] + ".txt");

			if (inFile.is_open())
			{
				while (getline(inFile, line))
				{
					battleRoom[counter].append(line);
					counter++;

					if (lineLength < line.size())
					{
						lineLength = line.size();
					}
				}

				if (counter < maxLines)
				{
					for (int j = 0; j < maxLines - counter; j++)
					{
						battleRoom[counter + j].append(lineLength, ' ');
					}
				}
			}
			else
			{
				throw "File load failed";
			}
			inFile.close();
		}
		ofstream outFile;
		outFile.open("./txt/battleroom.txt");

		for (int i = 0; i < battleRoom.size(); i++)
		{
			outFile << battleRoom[i] << endl;
		}
		outFile.close();

		printASCII("battleroom.txt");
	}
	catch (...)
	{
		cout << "File load failed! Check the integrity of your files." << endl;
	}
}