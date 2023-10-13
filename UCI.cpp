#include "UCI.h"

void UCI::UCILoop(){
    string Line; //to read the command given by the GUI
	int flag =1; //to change the value of chess squares from 'a' to 'h'

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

		if ( Line.substr(0,23) == "position startpos moves " ) {
			//cout << "bestmove d2d4" << endl;
            //Debug::UCILog("bestmove d2d4", false);

		} else if ( Line == "stop" ) {
			; // nothing to do

		} else if ( Line.substr( 0, 3 ) == "go " ) {
			// Received a command like: "go wtime 300000 btime 300000 winc 0 binc 0"
			cout << "bestmove " << char(105-flag) << "2" << char(105-flag) << "4" << endl;
			//Output like: "bestmove h7h5"
			flag++; //increase flag to move other pawn on next turn
		}
	}
}

Position UCI::ParsePosition(std::string line){
    std::size_t fenPos = line.find("fen");
    std::size_t startposPos = line.find("startpos");
    std::size_t movesPos = line.find("moves");

    if(fenPos == std::string::npos && startposPos == std::string::npos) return Position();
    if(startposPos) {
        if(movesPos == std::string::npos) {
            return Position("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 0");
        }else{
            //TODO with moves
        }
    }else if(fenPos){
        std::string fen;
        if(movesPos == std::string::npos) {
            fen = line.substr(fenPos + 4, line.length() - 13);
            return Position(fen);
        }else{
            //TODO with moves
        }
    }
    return Position("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 0");
}