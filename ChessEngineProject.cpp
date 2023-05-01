// ChessEngineProject.cpp : Defines the entry point for the application.
//

#include "ChessEngineProject.h"

using namespace std;

BoardRenderer renderer;
Validator validator;
Position currentPosition;
State gameState = State(currentPosition);
MoveGenerator moveGenerator;
std::vector<Move> moveMade;

void Turn() {
	std::string input;
	std::vector<Move> currPossibleMoves = moveGenerator.GenerateAllPossibleMoves(currentPosition);
	bool validMove = false;
	bool selectedMove = false;
	Move extractedMove;

	while (!validMove || !selectedMove) {
		cout << renderer.positionToString(currentPosition) << endl;
		cout << ((currentPosition.whiteTurn) ? "White" : "Black") << "'s next move: ";
		cin >> input;

		char pieceType;
		int target = 99;
		int file = 99;
		int rank = 99;
		char promotionType;

		validMove = validator.ValidMove(input, pieceType, target, file, rank, promotionType, currentPosition.whiteTurn);
		cout << "The move is valid? " << validMove << endl;
		if (validMove) {
			cout << "Piece Type: " << pieceType << endl;
			cout << "Target: " << target << endl;
			cout << "File: " << file << endl;
			cout << "Rank: " << rank << endl;
			cout << "Promotion Type: " << promotionType << endl;

			extractedMove = moveGenerator.ExtractMove(pieceType, target, file, rank, currentPosition.whiteTurn, currPossibleMoves);
			selectedMove = !extractedMove.isEmpty();
			cout << extractedMove.toString() << endl;
		}
		cout << endl;
	}
	if (validMove && selectedMove) {
		currentPosition.whiteTurn = !currentPosition.whiteTurn;
		currentPosition.MovePiece(extractedMove);
	}
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
