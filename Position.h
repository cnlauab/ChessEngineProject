
#pragma once
#include <algorithm>
#include <unordered_map>
#include <string>
#include <vector>
#include <stack>
#include "Parser.h"
#include "State.h"
#include "ChessUtil.h"
#include "BitUtil.h"
#include "Bitboards.h"

struct PositionState{
    unsigned short prevMove;
    short takenPiece = 99;
    short enPassantSquare = 99;
    short prevEnPassantSquare = 99;
    char castlingQuota1 = ' ';
    char castlingQuota2 = ' ';
    short halfMove = 0;
};

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
    unsigned short bestMove;
    std::vector<short> whitePieceOnBoard;
    std::vector<short> blackPieceOnBoard;
    short whiteKingLocation;
    short blackKingLocation;

    std::stack<PositionState> stateStack;

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
    std::string PositionToString();

    bool OpponentCanReach(short target, bool white);
    std::vector<short> GetFriendlyCanReach(short target, bool attacking);
    std::vector<short> GetCheckedByAndUpdatePin(bool white);
    bool IsChecked(bool white);
    
    bool IsEndgame();
    bool IsDraw();
    bool SufficientMaterial();

    std::string MoveToUCIString(unsigned short move);
    std::string MoveToPNGString(unsigned short move);

	//Mutator
    void UpdateCheck(short attackingPiece);
    void SetCastlingQuota(char type, bool on);
	void MovePiece(unsigned short& move);
	void UnmovePiece();

    //Evaluation
    short CalculateScore();
private:
    char castlingQuota = 15;
};
