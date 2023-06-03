#pragma once
#include <iostream>

#include "ChessUtil.h"

class Move {
public:
	//Input
	int from;
	int to;
	int piece;
	char promotionType;

	//OutCome
	int takenPiece;
	bool check;
	bool checkMate;

	Move();
	Move(int piece, int starting, int target);
	Move(int piece, int starting, int target, char promotionType);

	std::string toString();
	bool isEmpty();

	bool operator==(const Move& rhs);
};