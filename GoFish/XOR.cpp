/**
 * Source file for the XOR function
 * Author: Leo Huang
 * Student ID: 26886294
 * Date created: 13/9/2017
*/

#include "XOR.h"

using namespace std;

string XOR(string theString, string key)
{
	for (int i = 0; i < theString.size(); i++)
	{
		theString[i] ^= key[i % key.size()];
	}
	return theString;
}