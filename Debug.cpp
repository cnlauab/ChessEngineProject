#include "Debug.h"

void Debug::UCILog(std::string message, bool receiving){
    std::string label = receiving ? "IN" : "OUT";
    time_t now = time(0);

    std::ofstream outfile;
    outfile.open("uci_log.txt", std::fstream::in | std::fstream::out | std::fstream::app);

    outfile << std::put_time(localtime(&now), "%T") << " [" << label << "] " << message << "\n";
    outfile.close();
}

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
    outfile << "################" << std::endl;
    outfile.close();
}

void Debug::ClearLog(){
    std::ofstream outfile;
    outfile.open("game_log.txt", std::ofstream::out | std::ofstream::trunc);
    outfile.close();
}
