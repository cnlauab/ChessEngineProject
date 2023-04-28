#include "BoardRenderer.h"

std::string BoardRenderer::positionToString(const Position& position)
{
	std::string result;
	std::string row;
	int rowCounter = 1;
	for (int i = 0; i < 64; ++i) {
		char piece = ChessUtil::GetPieceType(position.position[i]);
		if (i % 8 == 7) {
			row.push_back('['); 
			row.push_back(piece);
			row.push_back(']');
			result = row + " " + std::to_string(rowCounter) + "\n" + result;
			row = "";
			rowCounter++;
		}
		else {
			row.push_back('[');
			row.push_back(piece);
			row.push_back(']');
		}
	}
	result += " a  b  c  d  e  f  g  h\n";
	return result;
}
