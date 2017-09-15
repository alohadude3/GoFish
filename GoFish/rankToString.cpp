/**
 * Source file for the rankToString function
 * Author: Leo Huang
 * Student ID: 26886294
 * Date created: 13/9/2017
*/

#include "rankToString.h"

string rankToString(int rank)
{
	string output = "";
	if (rank > 1 && rank < 10)
	{
		output += (char)rank + 48;
	}
	else
	{
		switch (rank)
		{
			case 1:
			{
				output = "Ace";
				break;
			}
			case 10:
			{
				output = "10";
				break;
			}
			case 11:
			{
				output = "Jack";
				break;
			}
			case 12:
			{
				output = "Queen";
				break;
			}
			case 13:
			{
				output = "King";
				break;
			}
		}
	}
	return output;
}