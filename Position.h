
#pragma once
#include <algorithm>
#include <unordered_map>
#include <string>
#include <vector>
#include "Parser.h"
#include "Move.h"
#include "State.h"
#include "ChessUtil.h"
#include "BitUtil.h"
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
    Bitboards bitboards;

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
    unsigned short prevMove;
    std::vector<short> whitePieceOnBoard;
    std::vector<short> blackPieceOnBoard;
    short whiteKingLocation;
    short blackKingLocation;

    //Pinned piece
    std::unordered_map<short,short> pinnedPiece;//piece,direction

	//Constructor
	Position();
    Position(std::string fen);
	Position(Position& position, unsigned short& move);
	Position(Position& position, std::vector<unsigned short>& moveList);

    //Getter
    short ReadPosition(short location);
    short GetPieceLocation(short piece);
    bool GetCastlingQuota(short piece, bool kingSide);
    bool GetCastlingQuota(char type);
    bool TargetIsEmpty(short target) const;
    bool TargetIsOppositeColor(short piece, short target) const;
    bool EnpassantSquareIsOppositeColor(short piece) const;
    std::string PositionToFen();

    bool OpponentCanReach(short target, bool white);
    std::vector<short> GetFriendlyCanReach(short target, bool attacking);
    std::vector<short> GetCheckedByAndUpdatePin(bool white);
    bool IsChecked(bool white);
    
    bool IsEndgame();
    bool IsDraw();
    bool SufficientMaterial();

    std::string MoveToUCIString(unsigned short move);
    std::string MoveToString(unsigned short move);

	//Mutator
    void SetCastlingQuota(char type, bool on);
	void MovePiece(unsigned short& move);

    //Evaluation
    short CalculateScore();
private:
    char castlingQuota = 15;
};