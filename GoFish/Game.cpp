/**
 * Source file for the ClassPlayer class
 * Author: Leo Huang
 * Student ID: 26886294
 * Date created: 12/9/2017
*/

#include <iostream>
#include <ctime> //std::srand for seeding
#include <fstream> //ifstream and ofstream
#include <sstream> //stringstream
#include "conio.h" //_getch
#include "Game.h"
#include "ClassPlayer.h"
#include "ClassCard.h"
#include "rankToString.h"
#include "XOR.h"

string Game::key = "key";
string Game::hashkey = "hashkey";

/** Empty constructor */
Game::Game()
{

}

/** Destructor */
Game::~Game()
{

}

/** Sets up the game */
void Game::setup(int playerCount)
{
	this->playerCount = playerCount;
	table = ClassPlayer("Table"); //the table will just be holding whatever cards are in the deck
	table.makeDeck();
	ClassPlayer myPlayer = ClassPlayer(getPlayerName());
	players.push_back(myPlayer);
	/** Add the AIs */
	for (int i = 0; i < playerCount - 1; i++)
	{
		string tempName = "AI" + to_string(i + 1);
		ClassPlayer tempPlayer = ClassPlayer(tempName);
		players.push_back(tempPlayer);
	}
	srand(time(NULL));
	currentPlayer = rand() % playerCount; //random player goes first
	for (int i = 0; i < playerCount; i++) //each players draw 7 cards
	{
		for (int j = 0; j < 7; j++)
		{
			players.at(i).addCard(table.getRandomCard());
		}
		checkPlayerForSets(players.at(i));
	}
}

/** Game loop */
bool Game::play()
{
	bool gameOngoing = true;
	while (gameOngoing)
	{
		if (!turn())
		{
			return false;
		}
		if (table.getSetsCompleted() == 13)
		{
			gameOngoing = false;
		}
	}
	system("cls");
	highestPoint = gethighestPoint();
	getWinningPlayers(winningPlayers);
	if (winningPlayers.size() > 1)
	{
		cout << "It is a draw between ";
		for (size_t i = 0; i < winningPlayers.size(); i++)
		{
			if (i > 0)
			{
				cout << " and ";
			}
			cout << players.at(winningPlayers.at(i)).getName();
		}
		cout << " at " << highestPoint << " points each!\n";
	}
	else
	{
		cout << players.at(winningPlayers.at(0)).getName() << " wins with " << highestPoint << " points!\n";
	}
	return getTryAgain();
}

/** Turn loop */
bool Game::turn()
{
	bool turnOngoing = true;
	while (turnOngoing)
	{
		system("cls");
		cout << "There are currently " << table.getCardCount() << " cards left on the table.\n\n";
		for (int i = 0; i < playerCount; i++)
		{
			cout << players.at(i).getName() << " has " << players.at(i).getCardCount() << " cards and " << players.at(i).getPoints() << " points.\n";
		}
		cout << "\nYour current hand:\n" << players.at(0).showHand() << "\n\n";
		int playerToAsk, cardValue;
		cout << players.at(currentPlayer).getName() << "'s turn.\n";
		if (players.at(currentPlayer).getCardCount() == 0)
		{
			turnOngoing = false;
			break;
		}
		/** Selecting a player to ask and a card rank to ask for */
		if (currentPlayer == 0) //if it is our turn
		{
			playerToAsk = getPlayerToAsk();
			cardValue = getCardRank();
		}
		else
		{
			playerToAsk = players.at(currentPlayer).getRandomPlayerToAsk(currentPlayer, playerCount);
			cardValue = players.at(currentPlayer).getRandomCardRank();
		}
		cout << players.at(currentPlayer).getName() << " asks " << players.at(playerToAsk).getName() << " for " << rankToString(cardValue) << "s\n";
		wait();
		if (players.at(playerToAsk).have(cardValue) > -1) //if they have the card of requested rank
		{
			while (players.at(playerToAsk).have(cardValue) > -1) //while they still have the cards of the requested rank
			{
				ClassCard card = players.at(playerToAsk).getCard(players.at(playerToAsk).have(cardValue));
				players.at(currentPlayer).addCard(card); //take the cards
				cout << players.at(playerToAsk).getName() << " gives " << players.at(currentPlayer).getName() << " a " << rankToString(card.getRank()) << " of " << card.getSuit() << endl;
				wait();
			}
			checkPlayerForSets(players.at(currentPlayer));
		}
		else //draw card (go fish)
		{
			cout << players.at(playerToAsk).getName() << " tells " << players.at(currentPlayer).getName() << " to go fish.\n";
			wait();
			if (table.getCardCount() > 0)
			{
				ClassCard tempCard = table.getRandomCard();
				players.at(currentPlayer).addCard(tempCard);
				if (currentPlayer != 0)
				{
					cout << players.at(currentPlayer).getName() << " draws a card from the table.\n";
					wait();
				}
				else
				{
					cout << "You draw a " << rankToString(tempCard.getRank()) << " of " << tempCard.getSuit() << endl;
					wait();
				}
				if (tempCard.getRank() != cardValue) //if the drawn card isn't what was asked, turn over
				{
					turnOngoing = false;
				}
				else
				{
					if (currentPlayer != 0)
					{
						cout << players.at(currentPlayer).getName() << " draws a " << rankToString(tempCard.getRank()) << " of " << tempCard.getSuit() << endl;
						wait();
					}
				}
				checkPlayerForSets(players.at(currentPlayer));
			}
			else
			{
				turnOngoing = false;
			}
		}
	}
	currentPlayer += 1;
	currentPlayer %= playerCount;
	char command = getEndTurnCommand();
	if (command == 's')
	{
		if (save() == 0)
		{
			return false;
		}
		cout << "Cannot write to save file.\n";
	}
	else
	{
		return true;
	}
}

/** Retrieves and returns the name of the player */
string Game::getPlayerName()
{
	string name;
	while (name.empty())
	{
		cout << "What is your name? ";
		cin >> name;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		if (name.empty())
		{
			cout << "Name cannot be empty, please try again.\n";
		}
	}
	return name;
}

/** Retrieves an int for which player the player would like to ask a card from */
int Game::getPlayerToAsk()
{
	int playerToAsk;
	bool validCommand = false;
	while (!validCommand)
	{
		cout << "Which player would you like to ask?\n";
		for (int i = 1; i < playerCount; i++)
		{
			cout << "(" << i << ") " << players.at(i).getName() << endl;
		}
		cin >> playerToAsk;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		if (playerToAsk > 0 && playerToAsk < playerCount)
		{
			validCommand = true;
		}
		else
		{
			cout << "Invalid command. Please try again.\n";
		}
	}
	return playerToAsk;
}

/** Retrieves an int representing the rank of the card the player would like to ask for */
char Game::getCardRank()
{
	int rank;
	bool validCommand = false;
	while (!validCommand)
	{
		cout << "What card would you like to ask for? (1 - 13) ";
		cin >> rank;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		if (rank < 1 || rank > 13)
		{
			cout << "Invalid card. Please try again.\n";
		}
		else if (players.at(0).have(rank) == -1)
		{
			cout << "You cannot ask for a card you do not have.\n";
		}
		else
		{
			validCommand = true;
		}
	}
	return rank;
}

/** Checks the player for sets then draw if needed */
void Game::checkPlayerForSets(ClassPlayer& player)
{
	player.sortCards();
	string temp = player.checkSets();
	if (!temp.empty())
	{
		cout << temp << endl;
		wait();
	}
	while (player.getCardCount() == 0 && table.getCardCount() > 0)
	{
		cout << player.drawCard(table) << endl;
		wait();
		player.sortCards();
		string temp = player.checkSets();
		if (!temp.empty())
		{
			cout << temp << endl;
			wait();
		}
	}
}

/** Waits for enter to be pressed before resuming the program */
void Game::wait()
{
	while (_getch() != '\r')
	{
		//do nothing
	}
}

/** Returns the highest point between all the players */
int Game::gethighestPoint()
{
	int max = 0;
	for (size_t i = 0; i < players.size(); i++)
	{
		if (max < players.at(i).getPoints())
		{
			max = players.at(i).getPoints();
		}
	}
	return max;
}

/** Adds the indices of all the players who have the highest points */
void Game::getWinningPlayers(vector<int>& winningPlayers)
{
	for (size_t i = 0; i < players.size(); i++)
	{
		if (players.at(i).getPoints() == highestPoint)
		{
			winningPlayers.push_back(i);
		}
	}
}

/**
 * Asks the player if they want to try again
 * Returns true if player says yes
 * Returns false otherwise
*/
bool Game::getTryAgain()
{
	char response = ' ';
	while (response != 'y' && response != 'n')
	{
		cout << "Would you like to play again? (y/n) ";
		cin >> response;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		if (response != 'y' && response != 'n')
		{
			cout << "Invalid command. Please try again.\n";
		}
	}
	return (response == 'y');
}

/**
 * Saves the game state to the file data.save
 * Returns 0 if successful, 1 otherwise
*/
 int Game::save()
 {
	 ofstream theFile;
	 theFile.open("data.save");
	 if (theFile.good())
	 {
		stringstream outputstream;
		/** Game variables */
		outputstream << playerCount << ' ';
		outputstream << currentPlayer << ' ';
		/** table variables */
		outputstream << table.getName() << ' ';
		outputstream << table.getSetsCompleted()  << ' ';
		int tableCardCount = table.getCardCount();
		outputstream << tableCardCount << ' ';
		/** table cards */
		for (int i = 0; i < tableCardCount; i++)
		{
			outputstream << table.getCardValue(i) << ' ';
		}
		/** Player variables */
		for (int i = 0; i < playerCount; i++)
		{
			outputstream << players.at(i).getName() << ' ';
			outputstream << players.at(i).getPoints() << ' ';
			int playerCardCount = players.at(i).getCardCount();
			outputstream << playerCardCount << ' ';
			/** Player hand cards */
			for (int j = 0; j < playerCardCount; j++)
			{
				outputstream << players.at(i).getCardValue(j) << ' ';
			}
			int playerSetCardCount = players.at(i).getSetCardCount();
			outputstream << playerSetCardCount << ' ';
			/** Player set cards */
			for (int j = 0; j < playerSetCardCount; j++)
			{
				outputstream << players.at(i).getSetCardValue(j) << ' ';
			}
		}
		string output = outputstream.str();
		output = XOR(output, hashkey); //make hash digest
		outputstream << endl << output; //append to new line
		output = outputstream.str();
		output = XOR(output, key); //encrypt data + digest
		theFile << output;
		theFile.close();
		return 0;
	 }
	 theFile.close();
	 return 1;
 }
 
/**
  * Loads the game state from the file data.save
  * Returns 0 if successful, 1 if the file cannot be accessed, 2 if the save file is corrupted
*/
 int Game::load()
 {
	 string tempString;
	 int tempInt;
	 ifstream theFile;
	 theFile.open("data.save");
	 if (theFile.good())
	 {
		string input((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
		input = XOR(input, key);
		stringstream inputstream(input);
		string data, hashdigest;
		getline(inputstream, data);
		getline(inputstream, hashdigest);
		if (hashdigest.compare(XOR(data, hashkey)) == 0)
		{
			stringstream datastream(data);
			/** Game variables */
			datastream >> playerCount;
			datastream >> currentPlayer;
			/** table variables */
			datastream >> tempString;
			table.setName(tempString);
			datastream >> tempInt;
			table.setSetsCompleted(tempInt);
			/** table cards */
			datastream >> tempInt;
			for (int i = 0; i < tempInt; i++)
			{
				int cardValue;
				datastream >> cardValue;
				ClassCard tempCard = ClassCard(cardValue);
				table.addCard(tempCard);
			}
			/** Player variables */
			for (int i = 0; i < playerCount; i++)
			{
				datastream >> tempString;
				ClassPlayer tempPlayer = ClassPlayer(tempString);
				datastream >> tempInt;
				tempPlayer.setPoints(tempInt);
				datastream >> tempInt;
				/** player cards */
				for (int j = 0; j < tempInt; j++)
				{
					int cardValue;
					datastream >> cardValue;
					ClassCard tempCard = ClassCard(cardValue);
					tempPlayer.addCard(tempCard);
				}
				datastream >> tempInt;
				/** player set cards */
				for (int j = 0; j < tempInt; j++)
				{
					int cardValue;
					datastream >> cardValue;
					ClassCard tempCard = ClassCard(cardValue);
					tempPlayer.addSetCard(tempCard);
				}
				players.push_back(tempPlayer);
			}
			theFile.close();
			return 0;
		}
		else
		{
			theFile.close();
			return 2;
		}
	 }
	 theFile.close();
	 return 1;
 }

/** Retrieves and returns a char representing the command of whether the player wants to continue or save and quit the game */
char Game::getEndTurnCommand()
{
	char command = ' ';
	while (command != 'c' && command != 's')
	{
		cout << "End of turn. Would you like to (c)ontinue or (s)ave and quit the game? ";
		cin >> command;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		if (command != 'c' && command != 's')
		{
			cout << "Invalid command. Please try again.\n";
		}
	}
	return command;
}