
#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include "Parser.h"
#include "Move.h"
#include "ChessUtil.h"

class Position {
public :
    bool whiteTurn = true;
    int enPassantSquare = 99;
    int halfmove = 0;
    int fullmove = 0;
	int position[64];

	//Constructor
	Position();
    Position(std::string fen);
	Position(Position& position, Move& move);

    //Getter
    int GetPieceLocation(int piece);
    bool TargetIsEmpty(int target) const;
    bool TargetIsOppositeColor(int piece, int target) const;
    bool EnpassantSquareIsOppositeColor(int piece) const;
    std::string PositionToFen();

	//Mutator
	void MovePiece(Move& move);
private:
    std::unordered_map<int, int> pieceLocation = {
        {-32,99},
        {-31,99},
        {-30,99},
        {-29,99},
        {-28,99},
        {-27,99},
        {-26,99},
        {-25,99},
        {-24,99},
        {-23,99},
        {-22,99},
        {-21,99},
        {-20,99},
        {-19,99},
        {-18,99},
        {-17,99},
        {-16,99},
        {-15,99},
        {-14,99},
        {-13,99},
        {-12,99},
        {-11,99},
        {-10,99},
        {-9,99},
        {-8,99},
        {-7,99},
        {-6,99},
        {-5,99},
        {-4,99},
        {-3,99},
        {-2,99},
        {-1,99},
        {0,0},
        {1,1},
        {2,2},
        {3,3},
        {4,4},
        {5,5},
        {6,6},
        {7,7},
        {8,8},
        {9,9},
        {10,10},
        {11,11},
        {12,12},
        {13,13},
        {14,14},
        {15,15},
        {48,48},
        {49,49},
        {50,50},
        {51,51},
        {52,52},
        {53,53},
        {54,54},
        {55,55},
        {56,56},
        {57,57},
        {58,58},
        {59,59},
        {60,60},
        {61,61},
        {62,62},
        {63,63},
        {64,99},
        {65,99},
        {66,99},
        {67,99},
        {68,99},
        {69,99},
        {70,99},
        {71,99},
        {72,99},
        {73,99},
        {74,99},
        {75,99},
        {76,99},
        {77,99},
        {78,99},
        {79,99},
        {80,99},
        {81,99},
        {82,99},
        {83,99},
        {84,99},
        {85,99},
        {86,99},
        {87,99},
        {88,99},
        {89,99},
        {90,99},
        {91,99},
        {92,99},
        {93,99},
        {94,99},
        {95,99}
    };
    std::unordered_map<char, bool> castlingQuota = { {'K',true}, {'Q',true}, {'k',true}, {'q',true} };
};