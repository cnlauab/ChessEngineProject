#include "State.h"

State::State(Position& position_) : position(position_){}

bool State::Ended() {
	return draw || stalemate || whiteWon || blackWon;
}

void State::Resign() {
	if (position.whiteTurn) {
		blackWon = true;
	}
	else {
		whiteWon = true;
	}
}