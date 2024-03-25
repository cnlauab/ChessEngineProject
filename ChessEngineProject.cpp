// ChessEngineProject.cpp : Defines the entry point for the application.
// On Lichess : https://lichess.org/@/honeybbot

#include "ChessEngineProject.h"

using namespace std;

Validator validator;
State gameState;
std::vector<unsigned short> moveMade;
bool whiteIsComp = false;

bool IsEnded(int noOfLegalMoves, Position& currentPosition){
	if(noOfLegalMoves == 0) {//Checkmate or Stalemate
		bool isChecked = currentPosition.IsChecked(currentPosition.whiteTurn);
		if(isChecked){
			if(currentPosition.whiteTurn){
				gameState.blackWon = true;
			}else{
				gameState.whiteWon = true;
			}
		}else{
			gameState.stalemate = true;
		}
		return true; 
	}
	return false;
}

void ComputerTurn(Position& currentPosition){

	unsigned short extractedMove = Evaluation::Evaluate(currentPosition);

	if(IsEnded(extractedMove,currentPosition)) return;
	cout << "Move made: " << currentPosition.MoveToPNGString(extractedMove) << endl;
	currentPosition.MovePiece(extractedMove);
	moveMade.emplace_back(extractedMove);

	bool isChecked = currentPosition.IsChecked(currentPosition.whiteTurn);
	cout << "#################" << endl;

}

void Turn(Position& currentPosition) {
	std::string input;
	std::vector<unsigned short> currLegalMoves = MoveGenerator::GenerateAllPossibleMoves(currentPosition);
	cout << "No. of Legal Moves: " << currLegalMoves.size() << endl;
	//for(Move move : currLegalMoves) cout << move.toString() << endl;
	
	if(IsEnded(currLegalMoves.size(),currentPosition)) return;

	bool validMoveInput = false;
	bool selectedMove = false;
	unsigned short extractedMove;

	while (!validMoveInput || !selectedMove) {
		cout << ((currentPosition.whiteTurn) ? "White" : "Black") << "'s next move: ";
		cin >> input;

		char pieceType;
		short target = 99;
		short file = 99;
		short rank = 99;
		char promotionType;

		validMoveInput = validator.ValidMove(input, pieceType, target, file, rank, promotionType, currentPosition.whiteTurn);
		cout << "######## " << endl;
		cout << "The move input is valid? " << validMoveInput << endl;
		if (validMoveInput) {
			cout << "Piece Type: " << pieceType << endl;
			cout << "Target: " << target << endl;
			cout << "File: " << file << endl;
			cout << "Rank: " << rank << endl;
			cout << "Promotion Type: " << promotionType << endl;

			//cout << "No. of possible moves: " << currLegalMoves.size() << endl;
			extractedMove = MoveGenerator::ExtractMove(pieceType, target, file, rank, currentPosition.whiteTurn, promotionType, currLegalMoves, currentPosition);
			selectedMove = extractedMove != 0;
			cout << "Selected Move: " << currentPosition.MoveToPNGString(extractedMove) << endl;
		}
		cout << "######## " << endl;
	}
	if (validMoveInput && selectedMove) {
		currentPosition.MovePiece(extractedMove);
		moveMade.emplace_back(extractedMove);

		bool isChecked = currentPosition.IsChecked(currentPosition.whiteTurn);
	}
	cout << "######## " << endl;
	cout << endl;
}

//Testing
void TestBitboard(){
	//Testing bitboard
	Bitboards bitboards = Bitboards("r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1");
	cout << "All" << endl;
	cout << bitboards.BitboardsToString() << endl;

}

void TestUCI(){
	//Testing uci
	Position currentPosition = UCI::ParsePosition("position startpos moves d2d4 e7e5");
	//currentPosition = UCI::ParsePosition("position fen 8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - moves b4b1");
	cout << currentPosition.PositionToString() << endl;
	cout << currentPosition.PositionToFen() << endl;

	UCI::SelfPlay();
}

void TestPerft(){
	//--Illegal ep move #1
	//std::string fen = "3k4/3p4/8/K1P4r/8/8/8/8 b - - 0 1"; int depth = 6; //perft 6 = 1134888
	//--Illegal ep move #2
	//std::string fen = "8/8/4k3/8/2p5/8/B2P2K1/8 w - - 0 1"; int depth = 6; //perft 6 = 1015133
	//--EP Capture Checks Opponent
	//std::string fen = "8/8/1k6/2b5/2pP4/8/5K2/8 b - d3 0 1"; int depth = 6; //perft 6 = 1440467
	//--Short Castling Gives Check
	//std::string fen = "5k2/8/8/8/8/8/8/4K2R w K - 0 1"; int depth = 6; //perft 6 = 661072
	//--Long Castling Gives Check
	//std::string fen = "3k4/8/8/8/8/8/8/R3K3 w Q - 0 1"; int depth = 6; //perft 6 = 803711
	//--Castle Rights
	//std::string fen = "r3k2r/1b4bq/8/8/8/8/7B/R3K2R w KQkq - 0 1"; int depth = 4; //perft 4 = 1274206
	//--Castling Prevented
	//std::string fen = "r3k2r/8/3Q4/8/8/5q2/8/R3K2R b KQkq - 0 1"; int depth = 4; //perft 4 = 1720476
	//--Promote out of Check
	//std::string fen = "2K2r2/4P3/8/8/8/8/8/3k4 w - - 0 1"; int depth = 6; //perft 6 = 3821001
	//--Discovered Check
	//std::string fen = "8/8/1P2K3/8/2n5/1q6/8/5k2 b - - 0 1"; int depth = 5; //perft 5 = 1004658
	//--Promote to give check
	//std::string fen = "4k3/1P6/8/8/8/8/K7/8 w - - 0 1"; int depth = 6; //perft 6 = 217342
	//--Under Promote to give check
	//std::string fen = "8/P1k5/K7/8/8/8/8/8 w - - 0 1"; int depth = 6; //perft 6 = 92683
	//--Self Stalemate
	//std::string fen = "K1k5/8/P7/8/8/8/8/8 w - - 0 1"; int depth = 6; //perft 6 = 2217
	//--Stalemate & Checkmate
	//std::string fen = "8/k1P5/8/1K6/8/8/8/8 w - - 0 1"; int depth = 7; //perft 7 = 567584
	//--Stalemate & Checkmate
	std::string fen = "8/8/2k5/5q2/5n2/8/5K2/8 b - - 0 1"; int depth = 4; //perft 4 = 23527
	//int depth = 6;

	Position initialPosition = Position(fen);
	//Position initialPosition = UCI::ParsePosition("position startpos");
	//Position initialPosition = UCI::ParsePosition("position startpos moves d2d4 a7a6 a2a3");
	//Position initialPosition = UCI::ParsePosition("position fen 8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - moves a5a6");

	//std::cout << initialPosition.PositionToFullReport() << std::endl;

	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	//Perft1
	//std::vector<Perft> perftData = {};
	//Evaluation::PerftSearch(initialPosition, depth, perftData, depth);
	//for(Perft perft : perftData){
	//	std::cout << perft.toString() << std::endl;
	//}

	//Perft2
	//std::cout << initialPosition.PositionToFullReport() << std::endl;
	//Evaluation::PerftSearch2(initialPosition, depth, depth, {"c7c5"});
	//Evaluation::PerftSearch2(initialPosition, depth, depth, {"e1d1", "b7h1", "d1c1"});
	Evaluation::PerftSearch2(initialPosition, depth, depth);

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	auto timeElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
	std::cout << "Time elapsed = " << timeElapsed << "[Milliseconds] that's " << timeElapsed / 60000  << "[Minutes]" << timeElapsed % 60000 / 1000 << "[Seconds]" << std::endl;

}

void TestEvaluation(){
	//Testing Evaluation
	Position currentPosition = Position("r4rk1/p1p1ppbp/1p1p1nb1/6N1/q2PPB1Q/5P2/PPPN2P1/1K1R1B2 b - - 2 15");
	cout << currentPosition.PositionToString() << endl;
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	
	unsigned short chosenMove = Evaluation::Evaluate(currentPosition);
	cout << "Move chosen: " << currentPosition.MoveToUCIString(chosenMove) << endl;
	
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	auto timeElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
	std::cout << "Time elapsed = " << timeElapsed << "[Milliseconds] that's " << timeElapsed / 60000  << "[Minutes]" << timeElapsed % 60000 / 1000 << "[Seconds]" << std::endl;

	Score score = Score(currentPosition);
	std::cout << "\nScore: \n" << score.ScoreToString() << std::endl;
}

void TestMagic(){
	MagicBits magicBits;
	std::string fen = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq -";
	Position initialPosition = Position(fen);
	unsigned long long allPieces = ~initialPosition.bitboards.allEmptySquareBitboard();
	unsigned long long friendlyPieces = initialPosition.bitboards.allWhiteBitboard();
	short queenSquare = BitUtil::getBitPositions(initialPosition.bitboards.whiteBitboards[1])[0];
	short bishopSquare = BitUtil::getBitPositions(initialPosition.bitboards.whiteBitboards[3])[0];
	short rookSquare = BitUtil::getBitPositions(initialPosition.bitboards.whiteBitboards[4])[0];

	unsigned long long bishopKey = BitUtil::GetMagicKey(allPieces, bishopSquare, true);
	unsigned long long rookKey = BitUtil::GetMagicKey(allPieces, rookSquare, false);

	unsigned long long queenMoves = magicBits.GetQueenMagic(queenSquare, BitUtil::GetMagicKey(allPieces, queenSquare, false), BitUtil::GetMagicKey(allPieces, queenSquare, true)) & ~friendlyPieces;
	unsigned long long bishopMoves = magicBits.GetBishopMagic(bishopSquare, bishopKey) & ~friendlyPieces;
	unsigned long long rookMoves = magicBits.GetRookMagic(rookSquare, rookKey) & ~friendlyPieces;

	cout << initialPosition.PositionToString() << endl;
	cout << "Queen moves at " << ChessUtil::SquareToString(queenSquare) << endl;
	cout << BitUtil::bitboardToString(queenMoves) << endl;
	cout << "Bishop moves at " << ChessUtil::SquareToString(bishopSquare) << endl;
	cout << BitUtil::bitboardToString(bishopMoves) << endl;
	cout << "Rook moves at " << ChessUtil::SquareToString(rookSquare) << endl;
	cout << BitUtil::bitboardToString(rookMoves) << endl;
}

//Mode
void ConsoleMode(){
	//Example
	//Position currentPosition = Position("8/6P1/7k/4B3/4B2K/8/8/8 w - - 0 1");
	//Position currentPosition = Position("2b2rk1/2q2ppn/2p5/p1n1p1B1/p3P3/2P2QNP/Br3PP1/R3R1K1");
	//Position currentPosition = Position("rnbqkb1r/ppp2ppp/4pn2/3p4/8/5NP1/PPPPPPBP/RNBQK2R w KQkq - 0 4");
	//Position currentPosition = Position("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1");

	//Perft
	//Position currentPosition = Position("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq -");
	//Position currentPosition = Position("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - -");
	//Position currentPosition = Position("r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1"); //position 4 - 1
	//Position currentPosition = Position("r2q1rk1/pP1p2pp/Q4n2/bbp1p3/Np6/1B3NBn/pPPP1PPP/R3K2R b KQ - 0 1"); //position 4 - 2
	//Position currentPosition = Position("rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8"); //position 5
	//Position currentPosition = Position("r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10");//position 6

	//Original
	Position currentPosition = Position("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 0");
	int moveCounter = 0;
	cout << "Starting Position: " + currentPosition.PositionToFen() << endl;
	
	//Game
	while (!gameState.Ended() && moveCounter < 500) {
		cout << currentPosition.PositionToString() << endl;
		cout << currentPosition.PositionToFen() << endl;
		cout << currentPosition.bitboards.BitboardsToString() << endl;

		if(currentPosition.whiteTurn && whiteIsComp || !currentPosition.whiteTurn && !whiteIsComp){
			ComputerTurn(currentPosition);
			//Turn();
		}else{
			//ComputerTurn();
			Turn(currentPosition);
		}
		Debug::GameLog(currentPosition);
		moveCounter++;
	}
	//End
	cout << gameState.EndMessage() << endl;
}

void UCIMode(){
    Debug::UCILog("Starting Main()", true);
	UCI::UCILoop();
}

//Main
int main()
{	
	Debug::ClearLog();
	Debug::UCILog("############ HoneyB Program Started ############", true);

	//int k = __builtin_clzll(1ULL);
	//cout << k << endl;

	//Play in console
	//ConsoleMode();
	//Play in UCI
	//UCIMode();

	//Test UCI
	//TestUCI();
	//Test Bitboard
	//TestBitboard();
	//Test Perft
	TestPerft();
	//Test Magic Bitboard
	//TestMagic();
	//Test Evaluation
	//TestEvaluation();


	return 0;
}
