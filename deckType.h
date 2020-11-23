#pragma once
#include "cardType.h"

class deckType {

public: 	

	//Deck operations
	void generateDeck(); 
	void clearDeck(); 
	cardType drawTopCard();
	cardType drawRandomCard(); 
	cardType viewRandomCard(); 
	void addCard(cardType);
	void addTopCard(cardType);
	void swapDeck(deckType&); 
	
	//Getters and Setters
	int getSize() const; 

	//Display functions
	void printDeck() const;

	//Operator overloads
	deckType operator=(const deckType&);

	//Deck data
	vector<cardType> deck;
};