// ChessEngineProject.cpp : Defines the entry point for the application.
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
	
	if(IsEnded(currLegalMoves)) return;

	int randomNum = rand() % currLegalMoves.size();
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
	//currentPosition = Position("8/6P1/7k/4B3/4B2K/8/8/8 w - - 0 1");
	//currentPosition = Position("2b2rk1/2q2ppn/2p5/p1n1p1B1/p3P3/2P2QNP/Br3PP1/R3R1K1");
	//currentPosition = Position("rnbqkb1r/ppp2ppp/4pn2/3p4/8/5NP1/PPPPPPBP/RNBQK2R w KQkq - 0 4");
	//currentPosition = Position("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1");

	currentPosition = Position("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 0");
	//currentPosition = Position();
	int moveCounter = 0;

	Debug::ClearLog();

	while (!gameState.Ended() && moveCounter < 100) {
		PrintMoveMade();
		cout << BoardRenderer::positionToString(currentPosition) << endl;
		cout << currentPosition.PositionToFen() << endl;
		if(currentPosition.whiteTurn && whiteIsComp || !currentPosition.whiteTurn && !whiteIsComp){
			ComputerTurn();
		}else{
			ComputerTurn();
			//Turn();
		}
		Debug::GameLog(currentPosition);
		moveCounter++;
	}
	cout << gameState.EndMessage() << endl;
	return 0;
}
