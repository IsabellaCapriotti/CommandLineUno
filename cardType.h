#pragma once
#include "unoEnums.h"
using namespace std;

class cardType {	
public:
	//Constructors
	cardType(); 
	cardType(cardLabelType, colorType, int); 

	//Getters and setters
	cardLabelType getLabel() const;
	void setLabel(cardLabelType); 
	colorType getColor() const; 
	void setColor(colorType); 
	int getNumber() const; 
	void setNumber(int); 

	//Print function
	void printCardInfo() const; 

	//Equality operations
	bool operator==(cardType);
	bool isValidMatch(cardType); 

private:
	//Stored values
	cardLabelType label;
	colorType color;
	int number;

};