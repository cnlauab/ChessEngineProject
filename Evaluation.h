
#pragma once
#include <queue>
#include <unordered_map>
#include <vector>
#include <chrono>

#include "Position.h"
#include "MoveGenerator.h"
#include "Perft.h"

class Evaluation{
public:
    static unsigned short Evaluate(Position& position);
    static void PerftSearch(Position& currPosition, int level, std::vector<Perft>& perftData, int initialDepth);
    static void PerftSearch2(Position& currPosition, int level, int initialDepth);
    static short BestMoveSearch(Position& position, int depth, bool maxingPlayer);
};