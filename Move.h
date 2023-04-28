#pragma once
#include <iostream>

#include "ChessUtil.h"

class Move {
public:
	//Preset
	int from;
	int to;
	int piece;
	//OutCome
	int takenPiece;
	bool check;
	bool checkMate;
	bool firstMove;
	char promotionType;

	Move();
	Move(int piece, int starting, int target);
	//Move(int piece, int starting, int target, char promotion);
};