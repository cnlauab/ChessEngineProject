#include "Debug.h"

void Debug::GameLog(Position& position){
    std::ofstream outfile;
    outfile.open("game_log.txt", std::fstream::in | std::fstream::out | std::fstream::app);

    outfile << "Turn " << position.fullmove << std::endl;
    if(position.whiteTurn){
        outfile << "White to move" << std::endl;
    } else{
        outfile << "Black to move" << std::endl;
    }
    outfile << BoardRenderer::positionToString(position) << std::endl;
    outfile << position.PositionToFen() << std::endl;
    outfile << "Move made: " << position.prevMove.toString() << std::endl;
    outfile << "################" << std::endl;
    outfile.close();
}

void Debug::ClearLog(){
    std::ofstream outfile;
    outfile.open("game_log.txt", std::ofstream::out | std::ofstream::trunc);
    outfile.close();
}

void Debug::MoveMadeLog(std::vector<Move> moves){
    
}

void Debug::MoveSelectionLog(std::vector<Move> possibleMoves){
    std::ofstream outfile;
    outfile.open("game_log.txt", std::fstream::in | std::fstream::out | std::fstream::app);
    outfile << "Possible move in this position " << std::endl;
    for(auto move : possibleMoves){
        outfile << move.toSimpleString() << std::endl;
    }
    outfile.close();
}