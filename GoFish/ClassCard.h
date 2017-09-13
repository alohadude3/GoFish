/**
 * Header file for the ClassCard class
 * Author: Leo Huang
 * Student ID: 26886294
 * Date created: 29/8/2017
*/

#ifndef CLASSCARD_H
#define CLASSCARD_H

#include <string>

/** Class declaration */
class ClassCard
{
	public:
		ClassCard();
		ClassCard(int value);
		~ClassCard();
		string getSuit();
		char getRank();
		void setValue(int value);
		int getValue();
	private:
		int value;
		string suit;
		char rank;
		void setAttributes(int value);
};

#endif