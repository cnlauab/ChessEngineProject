
#pragma once
#include <algorithm>
#include <unordered_map>
#include <string>
#include <vector>
#include "Parser.h"
#include "Move.h"
#include "ChessUtil.h"

class Position {
public :
    //FEN
    bool whiteTurn = true;
    short enPassantSquare = 99;
    short halfmove = 0;
    short fullmove = 0;
	short position[64];

    //Perft
    char checkedBy[2] = {99,99};
    bool ep;
    bool castle;
    bool promotion;
    bool capture;

    bool check;
    bool doubleCheck;
    bool discoverCheck;

    //States
    Move prevMove;
    std::vector<short> whitePieceOnBoard;
    std::vector<short> blackPieceOnBoard;
    short whiteKingLocation;
    short blackKingLocation;

	//Constructor
	Position();
    Position(std::string fen);
	Position(Position& position, Move& move);

    //Getter
    short ReadPosition(short location);
    short GetPieceLocation(short piece);
    bool GetCastlingQuota(short piece, bool kingSide);
    bool TargetIsEmpty(short target) const;
    bool TargetIsOppositeColor(short piece, short target) const;
    bool EnpassantSquareIsOppositeColor(short piece) const;
    std::string PositionToFen();

    bool OpponentCanReach(short target, bool white);
    std::vector<short> GetOpponentCanReach(short target, bool white);
    std::vector<short> GetCheckedBy(bool white);
    bool IsChecked(bool white);

	//Mutator
	void MovePiece(Move& move);
    void prevMoveLeadToCheck(Move& move);
private:
    std::unordered_map<char, bool> castlingQuota = { {'K',true}, {'Q',true}, {'k',true}, {'q',true} };
};