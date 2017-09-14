/**
 * Source file for the ClassPlayer class
 * Author: Leo Huang
 * Student ID: 26886294
 * Date created: 29/8/2017
*/

#include <ctime> //std::srand for seeding
#include <algorithm> //std::sort
#include <sstream>
#include "ClassPlayer.h"
#include "ClassCard.h"
#include "rankToString.h"

int ClassPlayer::setsCompleted = 0;

/** Empty Constructor */
ClassPlayer::ClassPlayer()
{

}

/**
 * Constructor for player
 * param name: the name of the player
 */
ClassPlayer::ClassPlayer(string name)
{
	this->name = name;
	points = 0;
}

/** Destructor */
ClassPlayer::~ClassPlayer()
{

}

/** Constructs a deck of playing cards */
void ClassPlayer::makeDeck()
{
	for (int i = 0; i < 52; i++)
	{
		hand.push_back(ClassCard(i));
	}
}

/**
 * Method have
 * Returns the index of the first card with the rank found
 * Returns -1 otherwise
 */
int ClassPlayer::have(int rank)
{
	for (size_t i = 0; i < hand.size(); i++)
	{
		if (hand.at(i).getRank() == rank)
		{
			return i;
		}
	}
	return -1;
}

/** Adds a card to the hand */
void ClassPlayer::addCard(ClassCard card)
{
	hand.push_back(card);
}

/** Removes the card from the hand at index i and returns it */
ClassCard ClassPlayer::getCard(int i)
{
	ClassCard temp = hand.at(i);
	hand.erase(hand.begin() + i);
	return temp;
}

/** Removes a random card in the hand and returns it */
ClassCard ClassPlayer::getRandomCard()
{
	srand(time(NULL));
	return getCard(rand() % hand.size());
}

/**
 * Checks to see if there are sets of 4 of the same rank cards in the hand
 * Moves the set from the hand to the sets if there are
 * Returns a stringstream message of the set found
 */
string ClassPlayer::checkSets()
{
	int rank = 0;
	stringstream output;
	output.str("");
	vector<ClassCard> temp; //temp queue
	size_t size = hand.size();
	for (size_t i = 0; i < size; i++) //iterates through the hand
	{
		if (temp.size() == 0) //if queue is empty
		{
			temp.push_back(getCard(0)); //serve the first card on
		}
		else
		{
			if (temp.back().getRank() == hand.at(0).getRank()) //if current card has same rank as last card
			{
				temp.push_back(getCard(0));
				if (temp.size() == 4)
				{
					for (size_t j = 0; j < temp.size(); j++)
					{
						sets.push_back(temp.at(j));
					}
					points += 1;
					setsCompleted += 1;
					rank = temp.at(0).getRank();
					temp.clear();
					break;
				}
			}
			else
			{
				for (size_t j = 0; j < temp.size(); j++) //if ranks are different serve the queue back into hand
				{
					addCard(temp.at(j));
				}
				temp.clear();
				temp.push_back(getCard(0));
			}
		}
	}
	for (size_t i = 0; i < temp.size(); i++)
	{
		addCard(temp.at(i)); //serve the rest of the remaining cards from the queue back to the player's hand
	}
	if (rank != 0)
	{
		output << name << " has completed a set of " << rankToString(rank) << "s." << endl;
	}
	return output.str();
}

/** 
 * Draws a card from the table
 * Returns a message of the number of cards drawn
 */
string ClassPlayer::drawCard(ClassPlayer& table)
{
	stringstream output;
	output << name << "draws ";
	if (table.getCardCount() >= 7)
	{
		for (int i = 0; i < 7; i++)
		{
			addCard(table.getRandomCard());
		}
		output << 7;
	}
	else
	{
		int i;
		for (i = 0; i < table.getCardCount(); i++)
		{
			addCard(table.getRandomCard());
		}
		output << i;
	}
	output << " cards from the table.";
	return output.str();
}

/** Returns a stringstream showing the player's current hand */
string ClassPlayer::showHand()
{
	stringstream output;
	for (size_t i = 0; i < hand.size(); i++)
	{
		if (i > 0)
		{
			output << ", ";
		}
		output << rankToString(hand.at(i).getRank()) << " of " << hand.at(i).getSuit();
	}
	return output.str();
}

/** Comparator for 2 cards */
bool ClassPlayer::compareCards(ClassCard& card1, ClassCard& card2)
{
	return card1.getRank() < card2.getRank();
}

/** Sorts the set of cards in ascending order by value*/
void ClassPlayer::sortCards()
{
	sort(hand.begin(), hand.end(), compareCards);
}

/** Randoms a number from 0 to number of players in the game that is not the argument */
int ClassPlayer::getRandomPlayerToAsk(int selfIndex, int playerCount)
{
	int playerToAsk;
	vector<int> indices;
	for (int i = 0; i < playerCount; i++)
	{
		indices.push_back(i);
	}
	srand(time(NULL));
	random_shuffle(indices.begin(), indices.end());
	playerToAsk = indices.at(0);
	if (playerToAsk == selfIndex)
	{
		playerToAsk = indices.at(1);
	}
	return playerToAsk;
}

/** Returns the rank of a random card the player possesses */
int ClassPlayer::getRandomCardRank()
{
	srand(time(NULL));
	return hand.at(rand() % hand.size()).getRank();
}

/** Setter for player name */
void ClassPlayer::setName(string name)
{
	this->name = name;
}

/** Getter for player name */
string ClassPlayer::getName()
{
	return name;
}

/** Getter for points */
int ClassPlayer::getPoints()
{
	return points;
}

/** Getter for number of cards in hand */
int ClassPlayer::getCardCount()
{
	return hand.size();
}

/** Getter for number of sets completed */
int ClassPlayer::getSetsCompleted()
{
	return setsCompleted;
}