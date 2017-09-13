/**
 * Source file for the ClassPlayer class
 * Author: Leo Huang
 * Student ID: 26886294
 * Date created: 29/8/2017
 */

#include "ClassPlayer.h"
#include "ClassCard.h"

using namespace std;

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
	for (int i = 0; i < hand.size(); i++)
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
	sortCards(hand);
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
stringstream ClassPlayer::checkSets()
{
	char rank = '0';
	stringstream output;
	output.str("");
	vector<ClassCard> temp; //temp stack
	for (int i = 0; i < hand.size(); i++) //iterates through the hand
	{
		if (temp.size() == 0) //if stack is empty
		{
			temp.push_back(getCard(i)); //push the current card on
		}
		else
		{
			if (temp.back().getRank() == hand.at(i).getRank()) //if current card has same rank as last card
			{
				temp.push_back(getCard(i));
				if (temp.size() == 4)
				{
					for (int j = 0; j < temp.size(); j++)
					{
						sets.push_back(temp.at(j));
						points += 1;
						setsCompleted += 1;
					}
					rank = temp.at(0).getRank();
					temp.clear();
				}
			}
			else
			{
				for (int j = 0; j < temp.size(); j++) //if ranks are different pop the stack back into hand
				{
					addCard(temp.at(j));
				}
				temp.clear();
			}
		}
	}
	if (rank != '0')
	{
		output << name << " has completed a set of " << rank << "s.";
	}
	return output;
}

/** 
 * Draws a card from the table
 * Returns a message of the number of cards drawn
 */
stringstream ClassPlayer::drawCard(ClassPlayer& table)
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
	return output;
}

/** Returns a stringstream showing the player's current hand */
stringstream ClassPlayer::showHand()
{
	stringstream output;
	for (int i = 0; i < getCardCount(); i++)
	{
		if (i > 0)
		{
			output << ", ";
		}
		output << hand.at(i).getRankChar() << " of " << hand.at(i).getSuit();
	}
	return output;
}

/** Comparator for 2 cards */
bool ClassPlayer::compareCards(ClassCard& card1, ClassCard& card2)
{
	return card1.getRank() < card2.getRank();
}

/** Sorts the set of cards in ascending order by value*/
void ClassPlayer::sortCards(vector<ClassCard>& cardVector)
{
	sort(cardVector.begin(), cardVector.end(), compareCards);
}

/** Randoms a number from 0 to number of players in the game that is not the argument */
int ClassPlayer::getRandomPlayerToAsk(int selfIndex, int playerCount)
{
	int playerToAsk = selfIndex;
	while (playerToAsk == selfIndex)
	{
		srand(time(NULL));
		playerToAsk = rand() % playerCount;
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