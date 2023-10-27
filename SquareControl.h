#pragma once
#include <iostream>
#include <vector>
#include <string>

class SquareControl {
public:
    std::vector<short> knightSquare;

    std::vector<short> slidingSquare[8];

    std::vector<short> kingSquare;
    
    std::vector<short> pawnSquareAbove;
    std::vector<short> pawnSquareBelow;
    short whitePawnPushOneSquare;
    short blackPawnPushOneSquare;
    short whitePawnPushTwoSquare;
    short blackPawnPushTwoSquare;

    //Bitboards
    unsigned long long pawnControlUpBitboard = 0ULL;
    unsigned long long pawnControlDownBitboard = 0ULL;
    unsigned long long bishopControlBitboard = 0ULL;
    unsigned long long knightControlBitboard = 0ULL;
    unsigned long long queenControlBitboard = 0ULL;
    unsigned long long rookControlBitboard = 0ULL;
    unsigned long long kingControlBitboard = 0ULL;
    unsigned long long pawnShiftUpBitboard = 0ULL;
    unsigned long long pawnShiftDownBitboard = 0ULL;

    //Constructor
    SquareControl(short square);
    //Member
    std::string toString();
    std::vector<short> GetKnightSquare();
    std::vector<short> GetSlidingSquare(int offsetType);
    std::vector<short> GetKingSquare();
    std::vector<short> GetPawnSquare(bool upward);

    bool OnSameLine(short square);
    //Static
	static int GetRank(short square);
	static int GetFile(short square);
	static bool SquareOutbound(short startingSquare, short targetSquare, short offsetType);
};