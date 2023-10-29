#include "UCI.h"

void UCI::SelfPlay(){
    Debug::UCILog("Starting SelfPlay()", true);
    int moves = 0;
    std::string positionCommand = "position startpos";
    Debug::UCILog(positionCommand, true);
    Position currPosition = ParsePosition(positionCommand);
    positionCommand += " moves";
    Debug::UCILog("\n" + BoardRenderer::positionToString(currPosition), true);
    Debug::UCILog(currPosition.PositionToFen(), true);
    while(!currPosition.checkmate || moves > 200){
        unsigned short bestMove = Evaluation::Evaluate(currPosition);
        Debug::UCILog("bestmove " + currPosition.MoveToUCIString(bestMove), false);
        if(bestMove == 0) break;
        positionCommand += " " + currPosition.MoveToUCIString(bestMove);
        currPosition = Position(currPosition, bestMove);
        Debug::UCILog(positionCommand, true);
        Debug::UCILog("\n" + BoardRenderer::positionToString(currPosition), true);
        Debug::UCILog(currPosition.PositionToFen(), true);
        moves++;
    }
    Debug::UCILog("SelfPlay() Ended", true);
}

void UCI::UCILoop(){
    string Line; //to read the command given by the GUI
    Position currPosition;

	cout.setf (ios::unitbuf);// Make sure that the outputs are sent straight away to the GUI
    
	while( getline( cin, Line ) ) {
        Debug::UCILog(Line, true);
		if ( Line == "uci" ) {
			cout << "id name HoneyB" << endl;
            Debug::UCILog("id name HoneyB", false);
			cout << "id author Francis Lau" << endl;
            Debug::UCILog("id author Francis Lau", false);
			cout << "uciok" << endl;
            Debug::UCILog("uciok", false);

		} else if ( Line == "quit" ) {
			cout << "Bye Bye" << endl;
            Debug::UCILog("Bye Bye", false);
			break;

		} else if ( Line == "isready" ) {
			cout << "readyok" << endl;
            Debug::UCILog("readyok", false);

		} else if ( Line == "ucinewgame" ) {
			; // nothing to do
		}

		if ( Line.substr(0,8) == "position" ) {
            currPosition = ParsePosition(Line);
            Debug::UCILog("\n" + BoardRenderer::positionToString(currPosition), true);
            Debug::UCILog(currPosition.PositionToFen(), true);

		} else if ( Line == "stop" ) {
			; // nothing to do

		} else if ( Line.substr( 0, 3 ) == "go " ) {
            unsigned short bestMove = Evaluation::Evaluate(currPosition);
            cout << "bestmove " << currPosition.MoveToUCIString(bestMove) << endl;
            Debug::UCILog("bestmove " + currPosition.MoveToUCIString(bestMove), false);

            currPosition.MovePiece(bestMove);
            Debug::UCILog("\n" + BoardRenderer::positionToString(currPosition), true);
            Debug::UCILog(currPosition.PositionToFen(), true);
		}
	}
}

Position UCI::ParsePosition(std::string line){
    if(line.find("position") == std::string::npos) return Position("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 0");
    if(line.find("startpos") != std::string::npos){
        Position position = Position("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 0");
        size_t charptr = line.find("moves");
        if(charptr != std::string::npos){
            std::vector<unsigned short> moveList;
            charptr += 6;
            while(charptr != std::string::npos && charptr < line.length()){
                std::string moveStr = line.substr(charptr, 5);
                if(moveStr.length() >= 4) moveList.push_back(ChessUtil::UCIToMove(moveStr));
                if(moveStr[4] == ' ') {
                    charptr += 5;
                }else{
                    charptr += 6;
                }
            }
            return Position(position, moveList);
        }else{
            return position;
        }
    }else if(line.find("fen") != std::string::npos){
        size_t charptr = line.find("fen") + 4;
        std::string fen;
        if(line.find("moves") != std::string::npos){
            fen = line.substr(charptr, line.find("moves") - charptr - 1);
            Position position = Position(fen);
            charptr = line.find("moves");
            if(charptr != std::string::npos){
                std::vector<unsigned short> moveList;
                charptr += 6;
                while(charptr != std::string::npos && charptr < line.length()){
                    std::string moveStr = line.substr(charptr, 5);
                    if(moveStr.length() >= 4) moveList.push_back(ChessUtil::UCIToMove(moveStr));
                    if(moveStr[4] == ' ') {
                        charptr += 5;
                    }else{
                        charptr += 6;
                    }
                }
                return Position(position, moveList);
            }
        }else{
            fen = line.substr(charptr);
            return Position(fen);
        }
    }
    return Position("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 0");
}