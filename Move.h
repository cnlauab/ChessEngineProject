#pragma once
#include <iostream>

#include "ChessUtil.h"

class Move {
public:
	//Input
	short from;
	short to;
	short piece;
	char promotionType;

	//OutCome
	short takenPiece;
	bool check;
	bool checkMate;
	bool rankAmbiguity;
	bool fileAmbiguity;

	Move();
	Move(std::string uci);
	Move(short starting, short target);
	Move(short starting, short target, char promotionType);

	void UpdateCheck(bool check, bool checkMate);
	void UpdateAmbiguity(bool rankAmbiguity, bool fileAmbiguity);
	bool IsShortCastling();
	bool IsLongCastling();

	std::string toSimpleString();
	std::string toString();
	bool isEmpty();
	bool operator==(const Move& rhs);
};