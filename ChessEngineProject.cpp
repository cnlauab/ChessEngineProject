// ChessEngineProject.cpp : Defines the entry point for the application.
//

#include "ChessEngineProject.h"

using namespace std;

BoardRenderer renderer;
Validator validator;
Position currentPosition;
State gameState = State(currentPosition);
MoveGenerator moveGenerator;

void Turn() {
	std::string input;
	int testInt;
	std::vector<Move> currPossibleMoves = moveGenerator.GenerateAllPossibleMoves(currentPosition);
	cout << renderer.positionToString(currentPosition) << endl;
	cout << ((currentPosition.whiteTurn) ? "White" : "Black") << "'s next move: ";
	cin >> input;
	bool validMove = validator.ValidMove(input);
	cout << "The move is valid? " << validMove << endl;
	cout << endl;
	if (validMove) currentPosition.whiteTurn = !currentPosition.whiteTurn;
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
