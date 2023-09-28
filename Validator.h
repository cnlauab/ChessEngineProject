
#pragma once
#include <string>
#include <vector>

#include "ChessUtil.h"
//Input Validator
class Validator {
public:
	std::vector<short> GetMoveStringArray(std::string input);
	bool ValidMove(std::string input, char& pieceType, short& target, short& file, short& rank, char& promotionType , bool& isWhite);
private:
	char pieceChar[5] = { 'N','B','R','Q','K' };
	char fileChar[8] = { 'a','b','c','d','e','f','g','h' };
	char rankChar[8] = { '1','2','3','4','5','6','7','8' };

	bool isPieceChar(char c);
	bool isFileChar(char c);
	bool isRankChar(char c);
	bool isTakeChar(char c);
	bool isCastleChar(char c);

	bool isCastlingMove(std::string input, short& target, bool& isWhite);
	bool isValidPawnMove(std::string input, short& target, char& promotionType);
	bool isValidPieceMove(std::string input, short& target, short& file, short& rank);

	bool NextTwoLetterIsSquare(std::string input, short nextLetterIndex);
	bool NextLetterIsEnding(std::string input, short nextLetterIndex);
	bool NextLetterIsPromotion(std::string input, short nextLetterIndex);
};