#pragma once
#include "deckType.h"
#include "playerType.h"
#include <iostream>

class gameType : public deckType, public playerType {

public: 
	//Player data
	vector<playerType> players;

	//Getters and Setters
	int getPlayerCount(); 
	void readPlayerData(); 
	void setCurrentPlayer(int); 
	int getCurrentPlayer();
	void setPlayerWon(); 
	bool getPlayerWon(); 
	void initTopCard(deckType&);
	void setTopCard(deckType&);
	cardType getTopCard() const; 
	void setGameDirection(directionType);
	directionType getGameDirection(); 
	void readWildColor(); 
	void setDrawActive(bool); 
	bool getDrawActive(); 
	void setWildActive(bool); 
	bool getWildActive(); 
	void setReverseActive(bool); 
	bool getReverseActive(); 
	void setSkipActive(bool);
	bool getSkipActive(); 

	//Display functions
	void printPlayersStatus() const; 

private: 
	//Stored data

	//Game data
	int roundCount; 
	int playerCount; 
	int currentPlayer; 
	bool hasPlayerWon; 
	cardType topCard; 
	directionType gameDirection;

	//Card states
	bool drawActive;
	bool wildActive;
	bool skipActive; 
	bool reverseActive; 
};