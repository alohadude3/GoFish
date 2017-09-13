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

int main()
{
	cout << "Welcome to Go Fish.\n";
	Game game = Game(getPlayerCount());
	game.play();
	cin.get();
	return 0;
}