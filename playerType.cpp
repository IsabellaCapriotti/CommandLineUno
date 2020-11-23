#include "playerType.h"
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std; 
//PlayerType function implementation. 


// -------------------------------------------
// The default constructor for playerType objects. 
playerType::playerType() {

	cardCount = 0; 
	move = 0; 
	name = "Default Player"; 
	winState = false; 
	playerControlled = false; 

}


// -------------------------------------------
// Deals a hand of 7 random cards to the player. Takes the deck to draw cards from as a parameter. 
void playerType::dealHand(deckType& drawDeck) {

	hand.deck.resize(7);
	cardCount = 7; 

	for (int i = 0; i < 7; i++) {

		hand.deck[i] = drawDeck.drawRandomCard();
	}
}


// -------------------------------------------
// Prints out the player's current hand. 
void playerType::showHand() {

	for (int i = 0; i < hand.getSize(); i++) {
		hand.deck[i].printCardInfo();
	}
}


// -------------------------------------------
// Adds a card to the player's hand, and prints the card's data. 
void playerType::drawCard(deckType& drawDeck) {

	cardType tempCard; 

	if (drawDeck.getSize() == 0) {
		cout << "Error; empty deck." << endl;
		return; 
	}

	tempCard = drawDeck.drawRandomCard(); 
	cout << "Drew: " << endl;
	tempCard.printCardInfo(); 
	cout << endl;
	++cardCount;
	hand.deck.push_back(tempCard);

}


// -------------------------------------------
// Removes the card at the passed index from the player's hand. 
void playerType::removeCard(int removeIndex) {

	--cardCount;
	hand.deck.erase(hand.deck.begin() + removeIndex);

}


// -------------------------------------------
// Removes the card of the passed cardType value from the player's hand. 
void playerType::removeCard(cardType removeCard) {

	int index = 0; 

	for (int i = 0; i < hand.deck.size(); i++) {
		if (hand.deck[i] == removeCard) {
			index = i; 
			break;
		}
	}

	--cardCount;
	hand.deck.erase(hand.deck.begin() + index);

}


// -------------------------------------------
// Returns the current value of the player name. 
string playerType::getName() const{

	return name; 

}


// -------------------------------------------
// Updates the current value of the player name to the passed value. 
void playerType::setName(string newName) {

	name = newName; 

}


// -------------------------------------------
// Prints the player data. 
void playerType::printPlayerData() const {

	cout << "Name: " << name << endl;
	cout << "Number of Cards: " << cardCount << endl;
	/* Debug Only
	cout << "Player Controlled: "; 

	if (playerControlled == true)
		cout << "Yes";
	else
		cout << "No"; 

	cout << endl;
	*/
	cout << "Hand: " << endl;
	hand.printDeck(); 
	cout << endl;
}


// -------------------------------------------
// Prints the player's current hand. 
void playerType::printHand() const {

	hand.printDeck(); 
	cout << endl;

}

// -------------------------------------------
// Updates the boolean condition of whether or not the player is user-controlled. 
void playerType::setPlayerControlled(bool newPlayerControlled) {
	
	playerControlled = newPlayerControlled; 

}


// -------------------------------------------
// Returns the current value of whether or not the player is user-controlled. 
bool playerType::getPlayerControlled() const {

	return playerControlled; 

}


// -------------------------------------------
// Determines if the current player has met the win condition (0 cards). 
void playerType::setWinState() {

	if (cardCount == 0)
		winState = true;

	else
		winState = false; 
}


// -------------------------------------------
// Returns the current value of the player's winState. 
bool playerType::getWinState() {

	return winState; 

}


// -------------------------------------------
// Reads in the user's desired value for their move.  
// Also sets the passed move as the new top card of the passed deck, as indicated by Uno rules. 
// If no valid move is possible, the function will return false.
bool playerType::readMove(cardType topCardToMatch, deckType& placeDeck) {

	bool matchPossible = false; 

	//Check if it is possible to play any card from the user's hand
	for (int i = 0; i < hand.deck.size(); i++) {
		if (hand.deck[i].isValidMatch(topCardToMatch)) {
			matchPossible = true;
			break;
		}
	}

	if (matchPossible == false) {
		cout << "No move is possible. Start drawing cards!" << endl;
		return false;
	}


	// Read in player move
	cout << "Enter your desired card to place: ";
	cin >> move; 
	move--; 

	// Check validity of move
	while( move < 0 || move >= hand.getSize() || (hand.deck[move].isValidMatch(topCardToMatch) == false) || cin.fail() == true) {
		cout << "Invalid move." << endl;
		cout << "Enter your desired card to place: ";
		cin.clear();
		cin.ignore(100, '\n');
		cin >> move; 
		move--; 
	}
	 
	// Add played card to the top of the play pile
	placeDeck.addTopCard(hand.deck[move]);
	// Remove played card from player's hand 
	removeCard(move);

	return true; 

}


// -------------------------------------------
// Chooses a random valid move from the calling player's hand. 
// Also sets the chosen move as the new top card of the passed deck. 
// If no valid move is possible, the function will return false. 
bool playerType::setRandomMove(cardType topCardToMatch, deckType& placeDeck) {

	bool matchPossible = false; 
	cardType testCard; 

	//Check if it is possible to play any card from the user's hand
	for (int i = 0; i < hand.deck.size(); i++) {
		if (hand.deck[i].isValidMatch(topCardToMatch)) {
			matchPossible = true;
			break;
		}
	}

	if (matchPossible == false) {
		cout << "No move is possible. Draw a card!" << endl;
		return false;
	}

	//Get random move if the hand is possible to play
	do {
		testCard = hand.viewRandomCard(); 
	} while (testCard.isValidMatch(topCardToMatch) == false);

	//Add played card to the top of the play pile
	placeDeck.addTopCard(testCard);
	//Remove played card from player's hand
	removeCard(testCard);
	return true; 
}


// -------------------------------------------
//Adds 2 random cards from the passed deck into the player's hand. 
void playerType::draw2(deckType& drawDeck) {

	cout << name << " draws 2 cards." << endl;
	for (int i = 0; i < 2; i++) {
		drawCard(drawDeck);
		cout << endl;
	}
}


// -------------------------------------------
//Adds 4 random cards from the passed deck into the player's hand.
void playerType::draw4(deckType& drawDeck) {

	cout << name << " draws 4 cards." << endl;

	for (int i = 0; i < 4; i++) {
		drawCard(drawDeck);
		cout << endl;
	}
}