/**
 * Header file for the ClassPlayer class
 * Author: Leo Huang
 * Student ID: 26886294
 * Date created: 29/8/2017
 */

#ifndef CLASSPLAYER_H
#define CLASSPLAYER_H

#include <string>
#include <vector>
#include <ctime> //std::srand for seeding
#include <algorithm> //std::sort
#include <sstream>
#include "ClassCard.h"

using namespace std;

/** Class declaration */
class ClassPlayer
{
	public:
		ClassPlayer();
		ClassPlayer(string name);
		~ClassPlayer();
		void makeDeck();
		int have(int rank);
		void addCard(ClassCard card);
		ClassCard getCard(int i);
		ClassCard getRandomCard();
		stringstream checkSets();
		stringstream drawCard(ClassPlayer& table);
		stringstream showHand();
		bool compareCards(ClassCard& card1, ClassCard& card2);
		void sortCards(vector<ClassCard>& cardVector);
		int getRandomPlayerToAsk(int selfIndex, int playerCount);
		int getRandomCardRank();
		void setName(string name);
		string getName();
		string getType();
		int getPoints();
		int getCardCount();
		int getSetsCompleted();
	private:
		string name;
		string type;
		int points;
		static int setsCompleted;
		vector<ClassCard> hand; //the player's current hand of cards
		vector<ClassCard> sets; //the player's completed set of cards
};

#endif