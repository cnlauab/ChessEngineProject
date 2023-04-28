
#pragma once
#include <string>
#include <vector>

class Validator {
public:
	std::vector<int> GetMoveStringArray(std::string input);
	bool ValidMove(std::string input);
private:
	char pieceChar[5] = { 'N','B','R','Q','K' };
	char fileChar[8] = { 'a','b','c','d','e','f','g','h' };
	char rankChar[8] = { '1','2','3','4','5','6','7','8' };

	bool isPieceChar(char c);
	bool isFileChar(char c);
	bool isRankChar(char c);
	bool isTakeChar(char c);
	bool isCastleChar(char c);

	bool isCastlingMove(std::string input);
	bool isValidPawnMove(std::string input);
	bool isValidPieceMove(std::string input);

	bool NextTwoLetterIsSquare(std::string input, int nextLetterIndex);
	bool NextLetterIsEnding(std::string input, int nextLetterIndex);
	bool NextLetterIsPromotion(std::string input, int nextLetterIndex);
};