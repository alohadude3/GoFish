/**
 * Header file for the Game class
 * Author: Leo Huang
 * Student ID: 26886294
 * Date created: 12/9/2017
*/

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include "ClassPlayer.h"

using namespace std;

class Game
{
	public:
		Game();
		~Game();
		void setup(int playerCount);
		bool play();
		bool turn();
		string getPlayerName();
		int getPlayerToAsk();
		char getCardRank();
		void checkPlayerForSets(ClassPlayer& player);
		void wait();
		int gethighestPoint();
		void getWinningPlayers(vector<int>& winningPlayers);
		bool getTryAgain();
		int save();
		int load();
		char getEndTurnCommand();
	private:
		static string key;
		static string hashkey;
		int playerCount;
		int currentPlayer;
		ClassPlayer table;
		vector<ClassPlayer> players;
		int highestPoint;
		vector<int> winningPlayers;
};

#endif