
#pragma once
#include <vector>
#include <string>
#include <ctype.h>
#include <unordered_map>
#include "Move.h"

class Parser {
public:
	void FenToPosition(std::string fen, int position[]);
	
private:
	int whitePawns[8] = {8,9,10,11,12,13,14,15};
	int blackPawns[8] = {48,49,50,51,52,53,54,55};
	int whiteRooks[10] = { 0,7,-24,-23,-22,-21,-20,-19,-18,-17 };
	int blackRooks[10] = { 56,63,80,81,82,83,84,85,86,87 };
	int whiteKnights[10] = { 1,6,-32,-31,-30,-29,-28,-27,-26,-25 };
	int blackKnights[10] = { 57,62,88,89,90,91,92,93,94,95 };
	int whiteBishops[10] = { 2,5,-16,-15,-14,-13,-12,-11,-10,-9 };
	int blackBishops[10] = { 58,61,72,73,74,75,76,77,78,79 };
	int whiteQueen[9] = { 3,-8,-7,-6,-5,-4,-3,-2,-1};
	int blackQueen[9] = { 59,64,65,66,67,68,69,70,71};
};