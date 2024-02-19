#include "Evaluation.h"

unsigned short Evaluation::Evaluate(Position& position){
    int depth = position.IsEndgame()? 5 : 4;
    BestMoveSearch(position, depth, position.whiteTurn);
    return position.bestMove;
}

void Evaluation::PerftSearch(Position& currPosition, int level, std::vector<Perft>& perftData, int initialDepth, std::vector<std::string> trackMoves){
    std::vector<unsigned short> possibleMoves = MoveGenerator::GenerateAllPossibleMoves(currPosition);
    //std::vector<unsigned short> possibleMoves;
    //Old
    for(int i = 0; i < possibleMoves.size(); ++i){
        //std::cout << "Move: " << ChessUtil::SimpleMoveToString(possibleMoves[i]) << std::endl;
        Position newPosition = Position(currPosition, possibleMoves[i]);

        //Track Moves
        std::vector<std::string> nextTrackMoves = trackMoves;
        int trackingIndex = initialDepth - level;
        if(trackMoves.size() > 0 && trackMoves.size() > trackingIndex){
            if(trackMoves[trackingIndex] == ChessUtil::SimpleMoveToString(possibleMoves[i])){
                if(trackingIndex == 0 || trackMoves[trackingIndex - 1] == ChessUtil::SimpleMoveToString(currPosition.stateStack.top().prevMove)){
                    std::cout << "After Move " << trackingIndex << " " << trackMoves[trackingIndex] << "," << ChessUtil::SimpleMoveToString(possibleMoves[i]) <<  ": " << std::endl;
                    std::cout << newPosition.PositionToFullReport() << std::endl;
                    std::vector<unsigned short> testPossibleMoves = MoveGenerator::GenerateAllPossibleMoves(newPosition);
                    std::cout << "Legal moves:" << std::endl;
                    for(unsigned short move : testPossibleMoves){
                        std::cout << ChessUtil::SimpleMoveToString(move) << std::endl;
                    }
                    std::cout << "#########################" << std::endl;
                }
            }else{
                nextTrackMoves = {};
            }
        }

        if(level > 1){
            PerftSearch(newPosition, level-1, perftData, initialDepth, nextTrackMoves);
        }else if(level == 1 && newPosition.check){
            PerftSearch(newPosition, level-1, perftData, initialDepth, nextTrackMoves);
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

void Evaluation::PerftSearch2(Position& currPosition, int level, int initialDepth, std::vector<std::string> trackMoves){
    std::vector<unsigned short> possibleMoves = MoveGenerator::GenerateAllPossibleMoves(currPosition);
    int nodes = 0;
    std::cout << possibleMoves.size() << std::endl;
    //std::vector<unsigned short> possibleMoves;
    //Old
    for(int i = 0; i < possibleMoves.size(); ++i){
        //std::cout << "Move: " << ChessUtil::SimpleMoveToString(possibleMoves[i]) << std::endl;
        Position newPosition = Position(currPosition, possibleMoves[i]);
        std::vector<Perft> perftData = {};

        //Track Moves
        std::vector<std::string> nextTrackMoves = trackMoves;
        int trackingIndex = initialDepth - level;
        if(trackMoves.size() > 0 && trackMoves.size() > trackingIndex){
            if(trackMoves[trackingIndex] == ChessUtil::SimpleMoveToString(possibleMoves[i])){
                if(trackingIndex == 0 || trackMoves[trackingIndex - 1] == ChessUtil::SimpleMoveToString(currPosition.stateStack.top().prevMove)){
                    std::cout << "After Move " << trackingIndex << " " << trackMoves[trackingIndex] << "," << ChessUtil::SimpleMoveToString(possibleMoves[i]) <<  ": " << std::endl;
                    std::cout << newPosition.PositionToFullReport() << std::endl;
                    std::vector<unsigned short> testPossibleMoves = MoveGenerator::GenerateAllPossibleMoves(newPosition);
                    std::cout << "Legal moves:" << std::endl;
                    for(unsigned short move : testPossibleMoves){
                        std::cout << ChessUtil::SimpleMoveToString(move) << std::endl;
                    }
                    std::cout << "#########################" << std::endl;
                }
            }else{
                nextTrackMoves = {};
            }
        }

        if(level > 1){
            PerftSearch(newPosition, level-1, perftData, initialDepth, nextTrackMoves);
        }else if(level == 1 && newPosition.check && initialDepth != 1){
            PerftSearch(newPosition, level-1, perftData, initialDepth, nextTrackMoves);
        }
    
        //if(perftData.size() < level && level > 0){
        //    Perft perft = Perft(level);
        //    perftData.push_back(std::move(perft));
        //}
        //if(level > 0) perftData[level-1].Add(newPosition.capture, newPosition.ep, newPosition.castle, newPosition.promotion, newPosition.check, newPosition.discoverCheck, newPosition.doubleCheck, newPosition.checkmate);
        
        //for(Perft perft : perftData){
        //    nodes += perft.nodes;
        //}
        if(perftData.size() > 0){
            nodes += perftData.front().nodes;
            std::cout << ChessUtil::SimpleMoveToString(possibleMoves[i]) << ": " << perftData.front().nodes << std::endl;
        }else{
            std::cout << ChessUtil::SimpleMoveToString(possibleMoves[i]) << ": 0" << std::endl;
        }
    }
    std::cout << "Nodes searched: " << nodes << std::endl;
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