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

    SquareControl(int square);

    std::string toString();

	static int GetRank(int square);
	static int GetFile(int square);
	static bool SquareOutbound(int startingSquare, int targetSquare, int offsetType);
};