#pragma once
#include "cardType.h"
#include "deckType.h"
#include <vector>
#include <iostream>

class playerType{

public:
	
	//Default constructor
	playerType(); 
	
	//Player's hand
	deckType hand; 

	//Hand operations
	void dealHand(deckType&); 
	void showHand(); 
	void drawCard(deckType&);
	void removeCard(int);
	void removeCard(cardType); 
	void draw2(deckType&);
	void draw4(deckType&);
	
	//Getters and Setters
	string getName() const; 
	void setName(string); 
	void setPlayerControlled(bool);
	bool getPlayerControlled() const;
	void setWinState(); 
	bool getWinState(); 
	bool readMove(cardType, deckType&); 
	bool setRandomMove(cardType, deckType&);  

	//Display operations
	void printPlayerData() const;
	void printHand() const; 
private: 

	//Stored data
	int cardCount; 
	int move; 
	string name; 
	bool winState; 
	bool playerControlled; 

};
