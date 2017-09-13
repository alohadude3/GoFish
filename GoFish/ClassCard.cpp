/**
 * Source file for the ClassCard class
 * Author: Leo Huang
 * Student ID: 26886294
 * Date created: 29/8/2017
*/

#include "ClassCard.h"

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
			break;
		}
		case 1:
		{
			suit = "Clubs";
			break;
		}
		case 2:
		{
			suit = "Hearts";
			break;
		}
		case 3:
		{
			suit = "Spades";
			break;
		}
	}
	rank = value / 4 + 1;
}

/** Getter for card suit */
string ClassCard::getSuit()
{
	return suit;
}

/** Getter for int value card rank */
int ClassCard::getRank()
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