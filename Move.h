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
	bool rankAmbiguity;
	bool fileAmbiguity;

	Move();
	Move(int piece, int starting, int target);
	Move(int piece, int starting, int target, char promotionType);

	void UpdateCheck(bool check, bool checkMate);
	void UpdateAmbiguity(bool rankAmbiguity, bool fileAmbiguity);
	bool IsShortCastling();
	bool IsLongCastling();

	std::string toSimpleString();
	std::string toString();
	bool isEmpty();
	bool operator==(const Move& rhs);
};