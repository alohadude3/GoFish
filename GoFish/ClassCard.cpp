/**
 * Source file for the ClassCard class
 * Author: Leo Huang
 * Student ID: 26886294
 * Date created: 29/8/2017
 */

#include "ClassCard.h"

using namespace std;

/** Empty constructor */
ClassCard::ClassCard()
{

}

/** Constructor with suit and rank */
ClassCard::ClassCard(int value)
{
	this->value = value;
	setAttributes(value);
}

/** Destructor */
ClassCard::~ClassCard()
{

}

/** Sets the suit and rank based on value of the card */
void ClassCard::setAttributes(int value)
{
	int suitValue = value % 4;
	switch (suitValue)
	{
		case 0:
		{
			suit = "Diamonds";
		}
		case 1:
		{
			suit = "Clubs";
		}
		case 2:
		{
			suit = "Hearts";
		}
		case 3:
		{
			suit = "Spades";
		}
	}
	int intRank = value / 4;
	if (intRank < 11 && intRank > 1)
	{
		rank = (char)intRank + 48;
	}
	else
	{
		switch (rank)
		{
			case 1:
			{
				rank = 'A';
				break;
			}
			case 11:
			{
				rank = 'J';
				break;
			}
			case 12:
			{
				rank = 'Q';
				break;
			}
			case 13:
			{
				rank = 'K';
				break;
			}
		}
	}
}

/** Getter for card suit */
string ClassCard::getSuit()
{
	return suit;
}

/** Getter for card rank */
char ClassCard::getRank()
{
	return rank;
}

/** Setter for card value */
void ClassCard::setValue(int value)
{
	this->value = value;
}

/** Getter for card value */
int ClassCard::getValue()
{
	return value;
}