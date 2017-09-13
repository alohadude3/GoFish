/**
 * Source file for the ClassPlayer class
 * Author: Leo Huang
 * Student ID: 26886294
 * Date created: 12/9/2017
*/

#include <iostream>
#include <ctime> //std::srand for seeding
#include "conio.h" //_getch
#include "Game.h"
#include "ClassPlayer.h"
#include "ClassCard.h"
#include "rankToString.h"

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
		system("cls");
		cout << "There are currently " << table.getCardCount() << " cards left on the table.\n\n";
		for (int i = 0; i < playerCount; i++)
		{
			cout << players.at(i).getName() << " has " << players.at(i).getCardCount() << " cards and " << players.at(i).getPoints() << " points.\n";
		}
		cout << "\nYour current hand:\n" << players.at(0).showHand() << "\n\n";
		int playerToAsk, cardValue;
		cout << players.at(currentPlayer).getName() << "'s turn.\n";
		wait();
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
	cout << "End of turn";
	wait();
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