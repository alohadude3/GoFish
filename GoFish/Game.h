/**
 * Header file for the Game class
 * Author: Leo Huang
 * Student ID: 26886294
 * Date created: 12/9/2017
 */

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <string>
#include <ctime> //std::srand for seeding
#include "ClassPlayer.h"

class Game
{
	public:
		Game();
		Game(int playerCount);
		~Game();
		void play();
		void turn();
		string getPlayerName();
		int getPlayerToAsk();
		int getCardRank();
		void checkPlayerForSets(ClassPlayer& player);
	private:
		int playerCount;
		int currentPlayer;
		ClassPlayer table;
		vector<ClassPlayer> players;
};

#endif