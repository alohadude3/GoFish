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
		void addSetCard(ClassCard card);
		int getCardValue(int i);
		int getSetCardValue(int i);
		ClassCard getCard(int i);
		ClassCard getRandomCard();
		string checkSets();
		string drawCard(ClassPlayer& table);
		string showHand();
		static bool compareCards(ClassCard& card1, ClassCard& card2);
		void sortCards();
		int getRandomPlayerToAsk(int selfIndex, int playerCount);
		int getRandomCardRank();
		void setName(string name);
		string getName();
		void setPoints(int points);
		int getPoints();
		int getCardCount();
		int getSetCardCount();
		void setSetsCompleted(int setsCompleted);
		int getSetsCompleted();
	private:
		string name;
		int points;
		static int setsCompleted;
		vector<ClassCard> hand; //the player's current hand of cards
		vector<ClassCard> sets; //the player's completed set of cards
};

#endif