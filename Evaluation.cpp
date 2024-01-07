#include "Evaluation.h"

unsigned short Evaluation::Evaluate(Position& position){
    int depth = position.IsEndgame()? 5 : 4;
    BestMoveSearch(position, depth, position.whiteTurn);
    return position.bestMove;
}

void Evaluation::PerftSearch(Position& currPosition, int level, std::vector<Perft>& perftData){
    std::vector<unsigned short> possibleMoves = MoveGenerator::GenerateAllPossibleMoves(currPosition);
    //std::vector<unsigned short> possibleMoves;
    //Old
    for(int i = 0; i < possibleMoves.size(); ++i){
        //if(currPosition.whiteTurn)std::cout << "White: " << ChessUtil::SimpleMoveToString(possibleMoves[i]) << std::endl;
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

    //New
    //for(int i = 0; i < possibleMoves.size(); ++i){
    //    currPosition.MovePiece(possibleMoves[i]);
    //    if(level > 1){
    //        PerftSearch(currPosition, level-1, perftData);
    //    }else if(level == 1 && currPosition.check){
    //        PerftSearch(currPosition, level-1, perftData);
    //    }
    //
    //    if(perftData.size() < level && level > 0){
    //        Perft perft = Perft(level);
    //        perftData.push_back(std::move(perft));
    //    }
    //    if(level > 0) perftData[level-1].Add(currPosition.capture, currPosition.ep, currPosition.castle, currPosition.promotion, currPosition.check, currPosition.discoverCheck, currPosition.doubleCheck, currPosition.checkmate);
    //    currPosition.UnmovePiece();
    //}
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
            //position.MovePiece(move);
            //short eval = BestMoveSearch(position, depth - 1, false);
            //position.UnmovePiece();
            if(eval > maxEval){
                maxEval = eval;
                position.bestMove = move;
            }
        }
        return maxEval;
    }else{
        short minEval = 27001;
        for(unsigned short move : possibleMoves){
            Position newPosition = Position(position, move);
            short eval = BestMoveSearch(newPosition, depth - 1, true);
            //position.MovePiece(move);
            //short eval = BestMoveSearch(position, depth - 1, true);
            //position.UnmovePiece();
            if(eval < minEval){
                minEval = eval;
                position.bestMove = move;
            }
        }
        return minEval;
    }
}