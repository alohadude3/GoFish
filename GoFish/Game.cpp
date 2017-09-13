/**
 * Source file for the ClassPlayer class
 * Author: Leo Huang
 * Student ID: 26886294
 * Date created: 12/9/2017
 */

#include "Game.h"
#include "ClassPlayer.h"
#include "ClassCard.h"

using namespace std;

/** Empty constructor */
Game::Game()
{

}

/** Constructor for specifying number of players */
Game::Game(int playerCount)
{
	this->playerCount = playerCount;
	table = ClassPlayer("Table"); //the table will just be holding whatever cards are in the deck
	table.makeDeck();
	ClassPlayer myPlayer = ClassPlayer(getPlayerName());
	players.push_back(myPlayer);
	/** Add the AIs */
	for (int i = 0; i < playerCount - 1; i++)
	{
		string tempName = "AI" + (i + 1);
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
	}
}

/** Destructor */
Game::~Game()
{

}


/** Game loop */
void Game::play()
{
	bool gameOngoing = true;
	while (gameOngoing)
	{
		turn();
		if (table.getSetsCompleted() == 13)
		{
			gameOngoing = false;
		}
	}
}

/** Turn loop */
void Game::turn()
{
	bool turnOngoing = true;
	while (turnOngoing)
	{
		int playerToAsk, cardValue;
		system("cls");
		cout << players.at(currentPlayer).getName() << "'s turn.\n";
		/** Selecting a player to ask and a card rank to ask for */
		if (currentPlayer == 0) //if it is our turn
		{
			cout << "There are currently " << table.getCardCount() << "left on the table.\n";
			for (int i = 0; i < playerCount; i++)
			{
				cout << "(" << i << ") " << players.at(i).getName() << " has " << players.at(i).getCardCount() << " cards.\n";
			}
			cout << "Your current hand:\n" << players.at(0).showHand().rdbuf() << "\n";
			playerToAsk = getPlayerToAsk();
			cardValue = getCardRank();
		}
		else
		{
			playerToAsk = players.at(currentPlayer).getRandomPlayerToAsk(currentPlayer, playerCount);
			cardValue = players.at(currentPlayer).getRandomCardRank();
		}
		cout << players.at(currentPlayer).getName() << " asks " << players.at(playerToAsk).getName() << " for " << cardValue << "s" << endl;
		cout << "Press enter to continue.\n";
		cin.get();
		if (players.at(playerToAsk).have(cardValue) > -1) //if they have the card of requested rank
		{
			while (players.at(playerToAsk).have(cardValue) > -1) //while they still have the cards of the requested rank
			{
				ClassCard card = players.at(playerToAsk).getCard(players.at(playerToAsk).have(cardValue));
				players.at(currentPlayer).addCard(card); //take the cards
				cout << players.at(playerToAsk).getName() << " gives " << players.at(currentPlayer).getName() << " a " << card.getRank() << " of " << card.getSuit() << endl;
			}
			checkPlayerForSets(players.at(currentPlayer));
		}
		else //draw card (go fish)
		{
			cout << players.at(playerToAsk).getName() << " tells " << players.at(currentPlayer).getName() << " to go fish.\n";
			ClassCard tempCard = table.getRandomCard();
			players.at(currentPlayer).addCard(tempCard);
			checkPlayerForSets(players.at(currentPlayer));
			if (tempCard.getRank() != cardValue) //if the drawn card isn't what was asked, turn over
			{
				turnOngoing = false;
				cout << endl;
			}
			else
			{
				cout << players.at(currentPlayer).getName() << " draws a " << tempCard.getRank() << " of " << tempCard.getSuit() << endl;
			}
		}
	}
	currentPlayer += 1;
	currentPlayer %= playerCount;
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
		if (playerToAsk > 0 && playerToAsk << playerCount)
		{
			validCommand == true;
		}
		else
		{
			cout << "Invalid command. Please try again.\n";
		}
	}
	return playerToAsk;
}

/** Retrieves an int representing the rank of the card the player would like to ask for */
int Game::getCardRank()
{
	int intRank;
	char charRank;
	bool validCommand = false;
	while (!validCommand)
	{
		cout << "What card would you like to ask for?";
		cin >> charRank;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		charRank = tolower(charRank);
		if ((charRank > (char)0 && charRank < (char)10) || charRank == 'j' || charRank == 'q' || charRank == 'k' || charRank == 'a')
		{
			switch (charRank)
			{
				case 'j':
				{
					intRank = 11;
					break;
				}
				case 'q':
				{
					intRank = 12;
					break;
				}
				case 'k':
				{
					intRank = 13;
					break;
				}
				case 'a':
				{
					intRank = 1;
					break;
				}
				default:
				{
					intRank = (int)charRank - 48;
					break;
				}
			}
			if (players.at(0).have(intRank) > -1)
			{
				cout << "You cannot ask for a card you do not have.\n";
			}
		}
		else
		{
			cout << "Invalid card. Please try again.\n";
		}
	}
	return intRank;
}

/** Checks the player for sets then draw if needed */
void Game::checkPlayerForSets(ClassPlayer& player)
{
	cout << players.at(currentPlayer).checkSets() << endl;
	if (players.at(currentPlayer).getCardCount() == 0)
	{
		cout << players.at(currentPlayer).drawCard() << endl;
	}	checkPlayerForSets(player);
}