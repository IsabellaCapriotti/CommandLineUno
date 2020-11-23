#pragma once
#include <vector>
#include <iostream>

using namespace std; 

enum class cardLabelType { NORMAL, REVERSE, SKIP, DRAW2, DRAW4, WILD };
enum class colorType { RED, YELLOW, BLUE, GREEN, ANY };
enum class directionType {CLOCKWISE, COUNTERCLOCKWISE};


//Labels for printing out enumerated types
struct enumLabels {
	vector<string> cardLabelTypeLabels{ "NORMAL", "REVERSE", "SKIP", "DRAW 2", "DRAW 4", "WILD" }; 
	vector<string> colorTypeLabels{ "RED", "YELLOW", "BLUE", "GREEN", "ANY" }; 
};
