
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
    int takenPieceType = 99;
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

    //Bitboard
    Bitboards bitboards;

    //Perft
    short checkedAt[2] = {99,99};
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

    std::stack<PositionState> stateStack;

    //Pinned piece
    //std::unordered_map<short,short> pinnedPiece;//piece,direction

    char castlingQuota = 0;

	//Constructor
	Position();
    Position(std::string fen);
	Position(Position& position, unsigned short& move);
	Position(Position& position, std::vector<unsigned short>& moveList);

    //Getter
    bool GetCastlingQuota(short piece, bool kingSide);
    bool GetCastlingQuota(char type);
    std::string PositionToFen();
    std::string PositionToString();

    std::vector<short> GetCheckedByAndUpdatePin(bool white);
    bool IsChecked(bool white);
    
    bool IsEndgame();
    bool IsDraw();
    bool SufficientMaterial();

    std::string MoveToUCIString(unsigned short move);
    std::string MoveToPNGString(unsigned short move);

	//Mutator
    void UpdateCheck(short attackingFrom);
    void SetCastlingQuota(char type, bool on);
	void MovePiece(unsigned short& move);
	void UnmovePiece();

    //Evaluation
    short CalculateScore();
private:
};
