
#pragma once
#include "Position.h"
//Game State
class State {
public:

	//End States
	bool draw = false;
	bool stalemate = false;
	bool whiteWon = false;
	bool blackWon = false;

	State(Position& position_);

	//Getter
	bool Ended();

	//Mutator
	void Resign();

private:
	Position& position;
};