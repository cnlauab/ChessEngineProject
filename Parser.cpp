#include "Parser.h"

void Parser::FenToPosition(std::string fen, int position[]) {
	//int result[64];

	int fenIterator = 0;

	//Position
	std::unordered_map<char, int> pieceCount = { {'p',0},{'r',0} ,{'n',0} ,{'b',0} ,{'k',0} ,{'q',0} ,{'P',0} ,{'R',0} ,{'N',0} ,{'B',0} ,{'K',0} ,{'Q',0} };
	int reorderingIndex[64] = { 56,57,58,59,60,61,62,63,48,49,50,51,52,53,54,55,40,41,42,43,44,45,46,47,32,33,34,35,36,37,38,39,24,25,26,27,28,29,30,31,16,17,18,19,20,21,22,23,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7 };
	for (int i = 0; i < 64; ++i) {
		if (fenIterator >= fen.length()) break;
		if (fen[fenIterator] == '/') {
			--i;
		}
		else if( isdigit(fen[fenIterator]) ) {
			int emptyCounter = fen[fenIterator] - '0';
			while (emptyCounter > 0) {
				position[reorderingIndex[i]] = 99;
				--emptyCounter;
				++i;
			}
			--i;
		}
		else {
			int nextPieceOfSameType = pieceCount[fen[fenIterator]];
			switch (fen[fenIterator])
			{
			case 'p':
				position[reorderingIndex[i]] = blackPawns[nextPieceOfSameType];
				break;
			case 'P':
				position[reorderingIndex[i]] = whitePawns[nextPieceOfSameType];
				break;
			case 'r':
				position[reorderingIndex[i]] = blackRooks[nextPieceOfSameType];
				break;
			case 'R':
				position[reorderingIndex[i]] = whiteRooks[nextPieceOfSameType];
				break;
			case 'n':
				position[reorderingIndex[i]] = blackKnights[nextPieceOfSameType];
				break;
			case 'N':
				position[reorderingIndex[i]] = whiteKnights[nextPieceOfSameType];
				break;
			case 'b':
				position[reorderingIndex[i]] = blackBishops[nextPieceOfSameType];
				break;
			case 'B':
				position[reorderingIndex[i]] = whiteBishops[nextPieceOfSameType];
				break;
			case 'q':
				position[reorderingIndex[i]] = blackQueen[nextPieceOfSameType];
				break;
			case 'Q':
				position[reorderingIndex[i]] = whiteQueen[nextPieceOfSameType];
				break;
			case 'k':
				position[reorderingIndex[i]] = 60;
				break;
			case 'K':
				position[reorderingIndex[i]] = 4;
				break;
			default:
				break;
			}
			++pieceCount[fen[fenIterator]];
		}
		++fenIterator;
	}

}


