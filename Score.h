
#pragma once
#include <string>
#include <vector>
#include "ChessUtil.h"
#include "BitUtil.h"
#include "Bitboards.h"
#include "Position.h"

class Score{
    public:
        int materialScore[2];
        int pawnStructureScore[2];
        int pieceCordinationScore[2];
        int pieceActivityScore[2];
        int kingSafetyScore[2];
        int kingActivityScore[2];
        int futureScore[2];

        Score(Position& position);
        Score(Score& whiteScore, Score& blackScore);

        int FinalEvaluation();
    private:
        void calculateMaterialScore(Position& position, bool white);
        void calculatePawnStructureScore(Position& position, bool white);
        void calculatePieceCoordinationScore(Position& position, bool white);
        void calculatePieceActivityScore(Position& position, bool white);
        void calculateKingSafetyScore(Position& position, bool white);
        void calculateKingActivityScore(Position& position, bool white);
};