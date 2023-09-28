#pragma once

#include <iostream>
#include "Position.h"

class LegalChecker {
public :
    //static bool OpponentCanReach(short target, Position& position, bool white);
    //static std::vector<short> GetOpponentCanReach(short target, Position& position, bool white);
    //static std::vector<short> IsChecked(Position& position);
    //static std::vector<short> IsChecked(Position& position, bool white);
    static bool IsLegal(Position& position, Move& move);
    static std::vector<Move> EliminateIllegalMoves(Position& position, std::vector<Move>& possibleMoves);
};