#include "Evaluation.h"

unsigned short Evaluation::Evaluate(Position& position){
    int depth = position.IsEndgame()? 4 : 3;
    BestMoveSearch(position, depth, position.whiteTurn);
    return position.bestMove;
}

void Evaluation::PerftSearch(Position& currPosition, int level, std::vector<Perft>& perftData){
    std::vector<unsigned short> possibleMoves = MoveGenerator::GenerateAllPossibleMoves(currPosition);
    for(int i = 0; i < possibleMoves.size(); ++i){
        Position newPosition = Position(currPosition, possibleMoves[i]);
        if(level > 1){
            PerftSearch(newPosition, level-1, perftData);
        }else if(level == 1 && newPosition.check){
            PerftSearch(newPosition, level-1, perftData);
        }

        if(perftData.size() < level && level > 0){
            Perft perft = Perft(level);
            perftData.push_back(std::move(perft));
        }
        if(level > 0) perftData[level-1].Add(newPosition.capture, newPosition.ep, newPosition.castle, newPosition.promotion, newPosition.check, newPosition.discoverCheck, newPosition.doubleCheck, newPosition.checkmate);
    }
}

short Evaluation::BestMoveSearch(Position& position, int depth, bool maxingPlayer){
    if(depth < 0) return position.CalculateScore();
    if(depth == 0 && !position.check) return position.CalculateScore();
    std::vector<unsigned short> possibleMoves = MoveGenerator::GenerateAllPossibleMoves(position);
    if(possibleMoves.size() == 0) return position.CalculateScore();
    
    if(maxingPlayer){
        short maxEval = -27001;
        for(unsigned short move : possibleMoves){
            Position newPosition = Position(position, move);
            short eval = BestMoveSearch(newPosition, depth - 1, false);
            if(eval > maxEval){
                maxEval = eval;
                position.bestMove = newPosition.prevMove;
            }
        }
        return maxEval;
    }else{
        short minEval = 27001;
        for(unsigned short move : possibleMoves){
            Position newPosition = Position(position, move);
            short eval = BestMoveSearch(newPosition, depth - 1, true);
            if(eval < minEval){
                minEval = eval;
                position.bestMove = newPosition.prevMove;
            }
        }
        return minEval;
    }
}