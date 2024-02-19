
#pragma once
#include <string>
#include <vector>
#include "ChessUtil.h"
#include "BitUtil.h"
#include "Bitboards.h"
#include "Position.h"

class Score{
    public:
        int materialScore[2] = {0,0};
        int pawnStructureScore[2] = {0,0};
        int pieceCordinationScore[2] = {0,0};
        int pieceActivityScore[2] = {0,0};
        int kingSafetyScore[2] = {0,0};
        int kingActivityScore[2] = {0,0};
        int checkScore[2] = {0,0};

        Score(Position& position);
        Score(Score& whiteScore, Score& blackScore);

        void CalculateScore(Position& position);
        int FinalEvaluation();
        std::string ScoreToString();
    private:
        void calculateMaterialScore(Position& position);
        void calculatePawnStructureScore(Position& position);
        void calculatePieceCoordinationScore(Position& position);
        void calculatePieceActivityScore(Position& position);
        void calculateKingSafetyScore(Position& position);
        void calculateKingActivityScore(Position& position);
        void calculateCheckScore(Position& position);
};