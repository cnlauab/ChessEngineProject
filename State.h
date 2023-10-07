
#pragma once
#include <string>
#include <vector>
#include "Position.h"
#include "Move.h"

//Game State
class State {
public:

	//End States
	bool draw = false;
	bool stalemate = false;
	bool whiteWon = false;
	bool blackWon = false;

	std::vector<std::string> prevPositionsFen;
	std::vector<Move> moveList;

	//Getter
	bool ThreeTimesRepeated();
	std::string MoveListToString();

	bool Ended();
	std::string EndMessage();

	//Mutator
	void Resign(bool white);

private:

};