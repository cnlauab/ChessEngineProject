
#pragma once
#include <string>
#include <vector>
#include "ChessUtil.h"
#include "BitUtil.h"
#include "Bitboards.h"
#include "Position.h"

class Score{
    public:
        int materialScore;
        int pawnStructureScore;
        int pieceCordinationScore;
        int pieceActivityScore;
        int kingSafetyScore;
        int kingActivityScore;
        int futureScore;
};