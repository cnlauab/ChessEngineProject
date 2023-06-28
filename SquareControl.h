#pragma once
#include <iostream>
#include <vector>
#include <string>

class SquareControl {
public:
    std::vector<int> knightSquare;

    std::vector<int> slidingSquare[8];

    std::vector<int> kingSquare;
    
    std::vector<int> pawnSquareAbove;
    std::vector<int> pawnSquareBelow;

    //Constructor
    SquareControl(int square);
    //Member
    std::string toString();
    std::vector<int> GetKnightSquare();
    std::vector<int> GetSlidingSquare(int offsetType);
    std::vector<int> GetKingSquare();
    std::vector<int> GetPawnSquare(bool isAbove);

    bool OnSameLine(int square);
    //Static
	static int GetRank(int square);
	static int GetFile(int square);
	static bool SquareOutbound(int startingSquare, int targetSquare, int offsetType);
};