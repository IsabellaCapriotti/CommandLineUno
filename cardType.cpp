#include "cardType.h"
#include <iostream>

using namespace std; 

// Function implementation for cardType class

//Default constructor
cardType::cardType() {
	label = cardLabelType::NORMAL; 
	color = colorType::RED;
	number = 0; 
}

//Constructor with given values
cardType::cardType(cardLabelType newLabel, colorType newColor, int newNumber) {
	label = newLabel;
	color = newColor; 
	number = newNumber; 
}

//Get label
cardLabelType cardType::getLabel() const {
	return label;
}

//Set label
void cardType::setLabel(cardLabelType newLabel) {
	label = newLabel; 
}

//Get color
colorType cardType::getColor() const {
	return color; 
}

//Set color
void cardType::setColor(colorType newColor) {
	color = newColor; 
}

//Get number
int cardType::getNumber() const {
	return number; 
}

//Set number
void cardType::setNumber(int newNumber) {
	number = newNumber; 
}

//Print card info
void cardType::printCardInfo() const{

	enumLabels printLabel;

	cout << "Type: " << printLabel.enumLabels::cardLabelTypeLabels[static_cast<int>(label)] << endl;
	cout << "Color: " << printLabel.enumLabels::colorTypeLabels[static_cast<int>(color)] << endl;

	if(number != -1)
		cout << "Number: " << number << endl;
}

//Compare equality of 2 cards
bool cardType::operator==(cardType rhs) {
	
	if (label == rhs.label && color == rhs.color && number == rhs.number) {
		return true;
	}

	else
		return false; 

}

//Check if it is valid to place one card on top of the other card. 
bool cardType::isValidMatch(cardType rhs) {

	// Color check
	if (color == rhs.color || color == colorType::ANY || rhs.color == colorType::ANY)
		return true; 

	// Number check (Normal cards only)
	if (number != -1 && rhs.number != -1 && number == rhs.number) {
		return true; 
	}

	// Type check (Non-numbered cards)
	if (number == -1 && rhs.number == -1 && (label == rhs.label || rhs.label == cardLabelType::WILD)) {
		return true;
	}

	else
		return false; 
}