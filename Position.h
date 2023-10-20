
#pragma once
#include <algorithm>
#include <unordered_map>
#include <string>
#include <vector>
#include "Parser.h"
#include "Move.h"
#include "State.h"
#include "ChessUtil.h"
#include "Bitboards.h"

class Position {
public :
    //FEN
    bool whiteTurn = true;
    short enPassantSquare = 99;
    short halfmove = 0;
    short fullmove = 0;
	short position[64];

    //Bitboard
    unsigned long long whiteBitboard[6];
    unsigned long long blackBitboard[6];

    //Perft
    char checkedBy[2] = {99,99};
    bool ep;
    bool castle;
    bool promotion;
    bool capture;

    bool check;
    bool doubleCheck;
    bool discoverCheck;
    bool checkmate;
    bool stalemate;

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
	Position(Position& position, std::vector<Move>& moveList);

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
    std::vector<short> GetFriendlyCanReach(short target, bool attacking);
    std::vector<short> GetCheckedBy(bool white);
    bool IsChecked(bool white);
    
    bool IsEndgame();
    bool IsDraw();
    bool SufficientMaterial();

	//Mutator
	void MovePiece(Move& move);
    void prevMoveLeadToCheck(Move& move);

    //Evaluation
    short CalculateScore();
private:
    //TODO Change it to 4 bit int
    std::unordered_map<char, bool> castlingQuota = { {'K',true}, {'Q',true}, {'k',true}, {'q',true} };
};