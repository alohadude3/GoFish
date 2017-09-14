/**
 * Main file for GoFish
 * Author: Leo Huang
 * Student ID: 26886294
 * Date created: 29/8/2017
*/

#include <iostream>
#include "Game.h"

using namespace std;

/** Asks and returns the number of players */
int getPlayerCount()
{
	int playerCount = 0;
	while (playerCount < 2 || playerCount > 4)
	{
		cout << "How many players would you like? (2 - 4) ";
		cin >> playerCount;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //flush the cin buffer
		if (playerCount < 2 || playerCount > 4)
		{
			cout << "The number of players must be between 2 and 4 (inclusive).\n";
		}
	}
	return playerCount;
}

/** Retrieves the player's command to whether they want to play a new game or load an existing game */
char getCommand()
{
	char command = ' ';
	while (command != 'n' && command != 'l')
	{
		cout << "Would you like to start a (n)ew game or (l)oad an existing game? ";
		cin >> command;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		if (command != 'n' && command != 'l')
		{
			cout << "Invalid command. Please try again.\n";
		}
	}
	return command;
}

/** Main function */
int main()
{
	bool playGame = true;
	cout << "Welcome to Go Fish.\n";
	while (playGame)
	{
		Game game = Game();
		char command = getCommand();
		switch (command)
		{
			case 'n':
			{
				game.setup(getPlayerCount());
				break;
			}
			case 'l':
			{
				game.load();
				break;
			}
		}
		playGame = game.play();
	}
	return 0;
}