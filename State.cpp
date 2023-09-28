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

std::string State::EndMessage(){
	if(draw) return "Draw";
	if(stalemate) return "Stalemate";
	if(whiteWon) return "whiteWon";
	if(blackWon) return "BlackWon";
	return "Game Ended by Program";
}