
#pragma once
#include <queue>
#include <unordered_map>
#include <vector>
#include <chrono>

#include "Position.h"
#include "MoveGenerator.h"
#include "Perft.h"
#include "Score.h"

class Evaluation{
public:
    static unsigned short Evaluate(Position& position);
    static void PerftSearch(Position& currPosition, int level, std::vector<Perft>& perftData, int initialDepth, std::vector<std::string> trackMoves = {});
    static void PerftSearch2(Position& currPosition, int level, int initialDepth, std::vector<std::string> trackMoves = {});
    static short BestMoveSearch(Position& position, Score& score, int depth, bool maxingPlayer);
private:
    short GetScore(Position& position, Score& score);
};