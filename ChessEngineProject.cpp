// ChessEngineProject.cpp : Defines the entry point for the application.
//

#include "ChessEngineProject.h"

using namespace std;

BoardRenderer renderer;
Validator validator;
Position currentPosition;
State gameState = State(currentPosition);
std::vector<Move> moveMade;

void Turn() {
	std::string input;
	std::vector<Move> currPossibleMoves = MoveGenerator::GenerateAllPossibleMoves(currentPosition);
	std::vector<Move> currLegalMoves = LegalChecker::EliminateIllegalMoves(currentPosition, currPossibleMoves);
	
	if(currLegalMoves.size() == 0) return; //Checkmate or Stalemate
	
	bool validMoveInput = false;
	bool selectedMove = false;
	Move extractedMove;

	while (!validMoveInput || !selectedMove) {
		cout << renderer.positionToString(currentPosition) << endl;
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

			extractedMove = MoveGenerator::ExtractMove(pieceType, target, file, rank, currentPosition.whiteTurn, currLegalMoves);
			selectedMove = !extractedMove.isEmpty();
			cout << "Selected Move: " << extractedMove.toString() << endl;
		}
		cout << "######## " << endl;
	}
	if (validMoveInput && selectedMove) {
		currentPosition.MovePiece(extractedMove);
		moveMade.emplace_back(extractedMove);
		if(LegalChecker::IsChecked(currentPosition)){
			cout << "Checked" << endl;
		}else{
			cout <<  "Not Checked" << endl;
		}
	}
	cout << "######## " << endl;
	cout << endl;
}

int main()
{
	currentPosition = Position("2b2rk1/2q2ppn/2p5/p1n1p1B1/p3P3/2P2QNP/Br3PP1/R3R1K1");
	//currentPosition = Position();
	while (!gameState.Ended()) {
		Turn();
	}
	return 0;
}
