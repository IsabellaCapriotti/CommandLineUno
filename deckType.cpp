#include "deckType.h"
#include <vector>

//Deck type class implementation. 

// -------------------------------------------
//Generates classic UNO deck.
void deckType::generateDeck() {
	int currentNumber = 0;
	cardType currentCard;
	colorType currentColor = colorType::RED;
	cardLabelType currentType = cardLabelType::REVERSE;

	//Normal numbered cards
	//Outer loop for 4 colors
	for (int i = 0; i < 4; i++) {
		currentNumber = 0;

		//Increment through the 4 colors
		if (i != 0) {
			switch (currentColor) {
			case colorType::RED:
				currentColor = colorType::YELLOW;
				break;
			case colorType::YELLOW:
				currentColor = colorType::BLUE;
				break;
			case colorType::BLUE:
				currentColor = colorType::GREEN;
				break;
			}
		}

		//Inner loop for 19 cards of each
		for (int j = 0; j < 19;) {

			//Set label and color
			currentCard.setLabel(cardLabelType::NORMAL);
			currentCard.setColor(currentColor);

			//Set number
			currentCard.setNumber(currentNumber);

			//One zero card
			if (currentNumber == 0) {
				deck.push_back(currentCard);
				j++;
			}

			//Two cards of all other values
			else {
				deck.push_back(currentCard);
				deck.push_back(currentCard);
				j += 2;
			}

			++currentNumber;
		}
	}

	//Action cards: 3 types(Draw 2, Reverse, Skip)    2 of each color for each type

	//Outer loop for 3 types
	for (int i = 0; i < 3; i++) {
		currentColor = colorType::RED;

		//Set current type of card
		if (i != 0) {
			switch (currentType) {
			case cardLabelType::REVERSE:
				currentType = cardLabelType::SKIP;
				break;
			case cardLabelType::SKIP:
				currentType = cardLabelType::DRAW2;
				break;
			}
		}

		//Inner loop for 4 colors
		for (int j = 0; j < 4; j++) {

			//Increment through 4 colors
			if (j != 0) {
				switch (currentColor) {
				case colorType::RED:
					currentColor = colorType::YELLOW;
					break;
				case colorType::YELLOW:
					currentColor = colorType::BLUE;
					break;
				case colorType::BLUE:
					currentColor = colorType::GREEN;
					break;
				}
			}

			//Update card values
			currentCard.setNumber(-1);
			currentCard.setLabel(currentType);
			currentCard.setColor(currentColor);

			//Add two of each
			deck.push_back(currentCard);
			deck.push_back(currentCard);
		}
	}

	//Wild cards
	currentCard.setNumber(-1);
	currentCard.setLabel(cardLabelType::WILD);
	currentCard.setColor(colorType::ANY);
	for (int i = 0; i < 4; i++) {
		deck.push_back(currentCard);
	}

	//Wild Draw 4's
	currentCard.setLabel(cardLabelType::DRAW4);
	for (int i = 0; i < 4; i++) {
		deck.push_back(currentCard);
	}

}


// -------------------------------------------
//Resets the deck to an empty deck. 
void deckType::clearDeck() {
	
	if (deck.size() != 0)
		deck.resize(0);

}


// -------------------------------------------
//Prints out the full deck. 
void deckType::printDeck() const{
	cout << "Number of cards: " << deck.size() << endl;
	for (int i = 0; i < deck.size(); i++) {
		deck[i].printCardInfo(); 
		cout << endl;
	}
}


// -------------------------------------------
//Adds the passed card data into the deck. 
void deckType::addCard(cardType newCard){

	deck.push_back(newCard);
}


// -------------------------------------------
//Adds the passed card data to the top of the deck. 
void deckType::addTopCard(cardType newCard) {

	deck.insert(deck.begin(), newCard); 

}

// -------------------------------------------
//Returns the top card from the deck, and removes it from the deck. 
cardType deckType::drawTopCard() {

	cardType temp;

	temp = deck[0];
	deck.erase(deck.begin());

	return temp; 
}


// -------------------------------------------
//Returns a random card from the deck, and removes it from the deck. 
cardType deckType::drawRandomCard() {

	cardType temp; 
	int index = 0; 

	index = rand() % deck.size();
	temp = deck[index];
	deck.erase(deck.begin() + index);
	return temp; 

}


// -------------------------------------------
//Returns a random card from the deck without removing it from the deck.
cardType deckType::viewRandomCard() {

	int index = 0; 
	
	index = rand() % deck.size(); 
	return deck[index];
}


// -------------------------------------------
//Overloads the = operator to copy the passed deckType object into the calling deckType object. 
deckType deckType::operator=(const deckType& rhs) {

	clearDeck();

	if (rhs.getSize() == 0)
		return *this; 

	else {

		for (int i = 0; i < rhs.getSize(); i++) {
			addCard(rhs.deck[i]);
		}
	}

	return *this; 

}


// -------------------------------------------
//Returns the current size of the deck. 
int deckType::getSize() const{

	return deck.size(); 

}


// -------------------------------------------
// Copies the contents of the passed deck into the calling deck, and then 
// clears the passed deck. 
void deckType::swapDeck(deckType& toCopy) {

	cardType temp; 

	//Clear the deck to copy into, if it was not already empty
	if (this->getSize() != 0) {
		this->clearDeck(); 
	}

	//Place the top card of the deck to copy in a temp variable
	temp = toCopy.deck[0]; 

	//Copy all members from the deck to copy into the new deck, except for the top card
	for (int i = 1; i < toCopy.getSize(); i++) {
		deck.push_back(toCopy.deck[i]); 
	}

	//Clear deck that was copied into old deck
	toCopy.clearDeck(); 

	//Add top card back to cleared deck so gameplay can resume
	toCopy.deck.push_back(temp);


}