#pragma once

#include <iostream>
#include "Position.h"
#include "MoveGenerator.h"

class LegalChecker {
public :
    static bool IsCheckedAt(int target, Position& position, bool white);
    static bool IsChecked(Position& position);
    static bool IsChecked(Position& position, bool white);
    static bool IsLegal(Position& position, Move& move);
    static std::vector<Move> EliminateIllegalMoves(Position& position, std::vector<Move>& possibleMoves);
};