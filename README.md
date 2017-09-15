# FIT1048 Assignment 2
### Title: GoFish
### Author: Leo Huang
### Student ID: 16886294
### Due Date: 15/09/2017

## Instructions
Go Fish is a console based text game controlled by command line inputs.
Most inputs will require a single character or number to be entered.
Available commands will usually be hinted by the game sometimes in brackets.

### For example:
`(c)ontinue or (s)ave and exit`

Enter the command `c` to continue with the game.

The game will follow standard basic Go Fish rules.
The winner will be decided once there are no cards left available.
The winner will be the person with the most points.

### Gameplay
The game will require the user to press `enter` to continue showing the next action. This feature is implemented with the intention of giving the user time to read through each individual action taken so they can process the information.

### Saving and Loading
The saving and loading feature of the game will require read and write access at the directory the program is located at. The program will write and read from the file `data.save` as its reference to the game save.

## Features
* Range of players (2 - 4)
* Name customisation for the player
* Keep track of points and cards each player have
* Keep track of cards left on the table
* Simple AI for computer opponents
* Error handling for invalid commands
* Dynamic constraint checking
* Saving and loading of game states
* Encryption for save file
* Checks for access permissions to save file
* Integrity check for save file with digital signature
* Automatic sorting of hands
* Support for draws between multiple players