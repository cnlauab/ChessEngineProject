#pragma once
#include <iostream>
#include <fstream>

#include "BoardRenderer.h"
#include "Position.h"

class Debug {
public:
    static void GameLog(Position& position);
    static void ClearLog();
    static void MoveMadeLog(std::vector<Move> moves);
    static void MoveSelectionLog(std::vector<Move> possibleMoves);
};
