﻿// ChessEngineProject.cpp : Defines the entry point for the application.
//

#include "ChessEngineProject.h"

using namespace std;

Validator validator;
Position currentPosition;
State gameState = State(currentPosition);
std::vector<Move> moveMade;
bool whiteIsComp = false;

void PrintMoveMade(){
	if(moveMade.size() == 0) return;
	int counter = 1;
	for(int i = 0; i < moveMade.size(); i++){
		if(i % 2 == 0){
			cout << counter << ". " << moveMade[i].toSimpleString() << " ";
		}else{
			cout << moveMade[i].toSimpleString() << endl;
			counter += 1;
		}
	}
	cout << endl;
}

bool IsEnded(std::vector<Move> currLegalMoves){
	if(currLegalMoves.size() == 0) {//Checkmate or Stalemate
		if(LegalChecker::IsChecked(currentPosition)){
			if(currentPosition.whiteTurn){
				gameState.blackWon = true;
			}else{
				gameState.whiteWon = true;
			}
			moveMade.back().UpdateCheck(false,true);
		}else{
			gameState.stalemate = true;
		}
		return true; 
	}
	return false;
}

void ComputerTurn(){
	std::vector<Move> currLegalMoves = MoveGenerator::GenerateAllPossibleMoves(currentPosition);
	cout << "No. of Legal Moves: " << currLegalMoves.size() << endl;
	for(Move move : currLegalMoves){
		cout << move.toSimpleString() << endl;
	}
	
	Debug::MoveSelectionLog(currLegalMoves);

	if(IsEnded(currLegalMoves)) return;

	int randomNum = rand() % currLegalMoves.size();
	cout << "Random number: " << randomNum << endl;
	Move extractedMove = currLegalMoves[randomNum];

	currentPosition.MovePiece(extractedMove);
	moveMade.emplace_back(extractedMove);
	if(LegalChecker::IsChecked(currentPosition)){
		extractedMove.UpdateCheck(true,false);
	}
	cout << "Move made: " << extractedMove.toString() << endl;
	cout << "#################" << endl;

}

void Turn() {
	std::string input;
	std::vector<Move> currLegalMoves = MoveGenerator::GenerateAllPossibleMoves(currentPosition);
	cout << "No. of Legal Moves: " << currLegalMoves.size() << endl;
	
	if(IsEnded(currLegalMoves)) return;

	bool validMoveInput = false;
	bool selectedMove = false;
	Move extractedMove;

	while (!validMoveInput || !selectedMove) {
		cout << ((currentPosition.whiteTurn) ? "White" : "Black") << "'s next move: ";
		cin >> input;

		char pieceType;
		int target = 99;
		int file = 99;
		int rank = 99;
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
			extractedMove = MoveGenerator::ExtractMove(pieceType, target, file, rank, currentPosition.whiteTurn, promotionType, currLegalMoves);
			selectedMove = !extractedMove.isEmpty();
			cout << "Selected Move: " << extractedMove.toString() << endl;
		}
		cout << "######## " << endl;
	}
	if (validMoveInput && selectedMove) {
		currentPosition.MovePiece(extractedMove);
		moveMade.emplace_back(extractedMove);
		if(LegalChecker::IsChecked(currentPosition)){
			extractedMove.UpdateCheck(true,false);
		}
		cout << "Move made: " << extractedMove.toString() << endl;
	}
	cout << "######## " << endl;
	cout << endl;
}

int main()
{	
   // Seed
   unsigned seed = time(0);
   srand(seed);

	//currentPosition = Position("8/6P1/7k/4B3/4B2K/8/8/8 w - - 0 1");
	//currentPosition = Position("2b2rk1/2q2ppn/2p5/p1n1p1B1/p3P3/2P2QNP/Br3PP1/R3R1K1");
	//currentPosition = Position("rnbqkb1r/ppp2ppp/4pn2/3p4/8/5NP1/PPPPPPBP/RNBQK2R w KQkq - 0 4");
	//currentPosition = Position("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1");

	//Perft
	//currentPosition = Position("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq -");
	//currentPosition = Position("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - -");
	//currentPosition = Position("rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8"); //position 5
	currentPosition = Position("r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10");//position 6

	//Original
	//currentPosition = Position("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 0");
	//currentPosition = Position();
	int moveCounter = 0;

	//Game
	//Debug::ClearLog();
	//while (!gameState.Ended() && moveCounter < 2) {
	//	PrintMoveMade();
	//	cout << BoardRenderer::positionToString(currentPosition) << endl;
	//	cout << currentPosition.PositionToFen() << endl;
	//	if(currentPosition.whiteTurn && whiteIsComp || !currentPosition.whiteTurn && !whiteIsComp){
	//		ComputerTurn();
	//		//Turn();
	//	}else{
	//		ComputerTurn();
	//		//Turn();
	//	}
	//	Debug::GameLog(currentPosition);
	//	cout << "No of piece on board: " << currentPosition.pieceOnBoard.size() << endl;
	//	moveCounter++;
	//}

	//Evaluation 
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	
	Node* root = new Node(&currentPosition);
	Evaluation::ConstructTree(root, 4);
	Evaluation::BFS(root);
	
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::cout << "Time elapsed = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[Milliseconds]" << std::endl;
    
	//End
	cout << gameState.EndMessage() << endl;
	return 0;
}
