
#pragma once
#include <string>
#include <vector>
#include "ChessUtil.h"
#include "BitUtil.h"
#include "Bitboards.h"
#include "Position.h"

class Score{
    public:
        short materialScore[2] = {0,0};
        short pawnStructureScore[2] = {0,0};
        short pieceCordinationScore[2] = {0,0};
        short pieceActivityScore[2] = {0,0};
        short kingSafetyScore[2] = {0,0};
        short kingActivityScore[2] = {0,0};
        short checkScore[2] = {0,0};

        Score(Position& position);
        Score(Score& whiteScore, Score& blackScore);

        void CalculateScore(Position& position);
        short FinalEvaluation();
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