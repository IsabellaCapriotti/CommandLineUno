#include "gameType.h"
#include <string>
#include <iostream>

// GameType Function Implementation. 

// -------------------------------------------
// Reads in a value for the number of user-controlled players (the rest will have random moves). 
void gameType::readPlayerData() {
	string tempName; 

	// Get number of user controlled players
	cout << "Enter number of user controlled players (1-4):  ";
	cin >> playerCount; 

	while (playerCount < 1 || playerCount > 4 || cin.fail() == true) {
		cout << "Error; invalid player count." << endl << "Enter number of user controlled players (1-4): ";
		cin.clear();
		cin.ignore(200, '\n'); 
		cin >> playerCount; 
	}

	//Populate players array with user-controlled players
	players.resize(4);

	//Clear stream
	cin.clear(); 
	cin.ignore(100, '\n');
	
	for (int i = 0; i < playerCount; i++) {
		cout << "Enter Player " << i + 1 << "'s Name: ";
		getline(cin, tempName);

		while (cin.fail() == true) {
			cout << "Error; invalid name." << endl << "Enter Player " << i + 1 << "'s Name: ";
			getline(cin, tempName);
		}

		players[i].setName(tempName); 
		players[i].setPlayerControlled(true);


	}

	//Give remaining COM players random names. 
	for (int i = playerCount; i < 4; i++){
		tempName = "Player " + to_string((i + 1)); 
		players[i].setName(tempName); 
		players[i].setPlayerControlled(false); 
	}
}


// -------------------------------------------
// Returns the value of the number of user-controlled players. 
int gameType::getPlayerCount() {

	return playerCount;

}


// -------------------------------------------
// Prints out all of the data for the current player set. 
void gameType::printPlayersStatus() const{

	for (int i = 0; i < 4; i++) {
		players[i].printPlayerData(); 
	}
}


// -------------------------------------------
// Sets the index for the current player in the players vector to be active. Prints an error if passed an
// invalid index. 
void gameType::setCurrentPlayer(int newPlayer) {


	//Wrap-around
	if (newPlayer < 0){
		currentPlayer = abs(4 + newPlayer);
		return;
	}

	else if (newPlayer > 3) {
		currentPlayer = abs(4 - newPlayer); 
		return;
	}

	//Standard case
	else
		currentPlayer = newPlayer; 
}


// -------------------------------------------
// Returns the index of the current player in the players vector. 
int gameType::getCurrentPlayer() {

	return currentPlayer; 

}


// -------------------------------------------
// Determines if the win state has been met for any player. 
void gameType::setPlayerWon() {

	for (int i = 0; i < 4; i++) {
		players[i].setWinState();
		if (players[i].getWinState()) {
			hasPlayerWon = true;
			return;
		}
	}

	hasPlayerWon = false; 
}


// -------------------------------------------
// Returns whether or not any player has entered the win state. 
bool gameType::getPlayerWon() {

	return hasPlayerWon; 

}


// -------------------------------------------
// Draws a new top card from the passed deck.
void gameType::initTopCard(deckType& drawDeck) {

	topCard = drawDeck.drawRandomCard();

}


// -------------------------------------------
// Sets the class member variable topCard to the card at the top of the passed deck. 
void gameType::setTopCard(deckType& drawDeck) {

	topCard = drawDeck.deck[0];

}


// -------------------------------------------
// Returns the current top card. 
cardType gameType::getTopCard() const{

	return topCard; 

}


// -------------------------------------------
// Sets the class member variable gameDirection to the passed directionType value. 
void gameType::setGameDirection(directionType newDirection) {

	gameDirection = newDirection;

}


// -------------------------------------------
// Returns the current value of the gameDirection class member. 
directionType gameType::getGameDirection() {

	return gameDirection; 

}


// -------------------------------------------
// Reads in the color to be used for the wild card, and updates the wild card to that value. 
// This function assumes that the wild card is set as the topCard class member variable. 
void gameType::readWildColor() {

	char colorChoice = ' '; 
	bool validColor = false; 
	enumLabels printLabel;

	//Prompt and receive color choice
	cout << "Enter color for the wild card (R/Y/B/G): "; 

	cin >> colorChoice; 

	//Invalid character entered
	while (cin.fail() == true) {
		cin.clear(); 
		cin.ignore(100, '\n');
		cout << "Error; invalid color choice." << endl;
		cout << "Enter color for the wild card (R/Y/B/G): ";
		cin >> colorChoice; 
	}


	//Determine what color to switch to if valid character is provided, update top card correspondingly
	while (validColor == false) {
		switch (colorChoice) {
		case 'R':
		case 'r':
			topCard.setColor(colorType::RED);
			validColor = true; 
			break;
		case 'Y':
		case 'y':
			topCard.setColor(colorType::YELLOW);
			validColor = true; 
			break;
		case 'B':
		case 'b':
			topCard.setColor(colorType::BLUE); 
			validColor = true; 
			break;
		case 'G': 
		case 'g': 
			topCard.setColor(colorType::GREEN);
			validColor = true;
			break;
		default:
			cout << "Error; invalid color choice." << endl;
			cin.clear(); 
			cin.ignore(100, '\n'); 
			validColor = false;
			cin >> colorChoice; 
			break;
		}
	}

	//Print message
	cout << "Color has been switched to " << printLabel.enumLabels::colorTypeLabels[static_cast<int>(topCard.getColor())] << endl;
}


// -------------------------------------------
// Updates the drawActive class member variable to the passed value. 
void gameType::setDrawActive(bool newDrawActive) {

	drawActive = newDrawActive;

}


// -------------------------------------------
// Returns the current value of class member variable drawActive. 
bool gameType::getDrawActive() {

	return drawActive; 

}


// -------------------------------------------
// Updates the wildActive class member variable to the passed value. 
void gameType::setWildActive(bool newWildActive) {

	wildActive = newWildActive; 

}


// -------------------------------------------
// Returns the current value of class member variable wildActive. 
bool gameType::getWildActive() {

	return wildActive; 

}



// -------------------------------------------
// Updates the reverseActive class member variable to the passed value. 
void gameType::setReverseActive(bool newReverseActive) {

	reverseActive = newReverseActive;

}


// -------------------------------------------
// Returns the current value of class member variable reverseActive. 
bool gameType::getReverseActive() {

	return reverseActive;

}


// -------------------------------------------
// Updates the skipActive class member variable to the passed value. 
void gameType::setSkipActive(bool newSkipActive) {

	skipActive = newSkipActive; 

}


// -------------------------------------------
// Returns the current value of class member variable skipActive. 
bool gameType::getSkipActive() {

	return skipActive;

}