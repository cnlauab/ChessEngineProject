#include "Validator.h"

std::vector<int> Validator::GetMoveStringArray(std::string input)
{//TODO
	std::vector<int> result;
	if (input.length() < 2) return result;

	char first_letter = input[0];
	if (isPieceChar(first_letter)) {
		result.push_back((int)first_letter);
	}
	else if (isFileChar(first_letter)) {
		result.push_back((int)'p');
	}
	else if (isCastleChar(first_letter)) {
		result.push_back((int)'K');
	}

	return result;
}

bool Validator::ValidMove(std::string input)
{
	if (input.length() < 2) return false;
	if (input == "Resign" || input == "resign") return true;

	char first_letter = input[0];
	if (isPieceChar(first_letter)) {
		return isValidPieceMove(input);
	}
	else if (isFileChar(first_letter)) {
		return isValidPawnMove(input);
	}
	else if (isCastleChar(first_letter)) {
		return isCastlingMove(input);
	}
	else {
		return false;
	}
}
//Char Checker
bool Validator::isPieceChar(char c)
{
	return std::find(std::begin(pieceChar), std::end(pieceChar), c) != std::end(pieceChar);
}

bool Validator::isFileChar(char c)
{
	return std::find(std::begin(fileChar), std::end(fileChar), c) != std::end(fileChar);
}

bool Validator::isRankChar(char c)
{
	return std::find(std::begin(rankChar), std::end(rankChar), c) != std::end(rankChar);
}

bool Validator::isTakeChar(char c)
{
	return c == 'x' || c == 'X';
}

bool Validator::isCastleChar(char c)
{
	return c == 'o' || c == 'O' || c == '0';
}

//Move Checker
bool Validator::isCastlingMove(std::string input)
{
	return input == "O-O-O" || input == "o-o-o" || input == "O-O" || input == "o-o" || input == "0-0" || input == "0-0-0";
}

bool Validator::isValidPawnMove(std::string input)
{
	char second_letter = input[1];
	if (isRankChar(second_letter)) {
		return NextLetterIsPromotion(input, 2) || NextLetterIsEnding(input, 2);
	}
	else if (isTakeChar(second_letter)) {
		if (NextTwoLetterIsSquare(input, 2)) {
			return NextLetterIsPromotion(input, 4) || NextLetterIsEnding(input, 4);
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

bool Validator::isValidPieceMove(std::string input)
{
	char second_letter = input[1];
	char third_letter = input[2];
	char forth_letter = input[3];
	if (isFileChar(second_letter)) {
		if (isTakeChar(third_letter)) {
			return NextTwoLetterIsSquare(input, 3) && NextLetterIsEnding(input, 5);
		}
		else if (isRankChar(third_letter)) {
			if (isTakeChar(forth_letter)) {
				return NextTwoLetterIsSquare(input, 4) && NextLetterIsEnding(input, 6);
			}
			else if (isFileChar(forth_letter)) {
				return NextTwoLetterIsSquare(input, 3) && NextLetterIsEnding(input, 5);
			}
			else {
				return NextLetterIsEnding(input, 3);
			}
		}
		else {
			return NextTwoLetterIsSquare(input, 2) && NextLetterIsEnding(input, 4);
		}
	}
	else if (isRankChar(second_letter)) {
		if (isTakeChar(third_letter)) {
			return NextTwoLetterIsSquare(input, 3) && NextLetterIsEnding(input, 5);
		}
		else {
			return NextTwoLetterIsSquare(input, 2) && NextLetterIsEnding(input, 4);
		}
	}
	else if (isTakeChar(second_letter)) {
		return NextTwoLetterIsSquare(input, 2) && NextLetterIsEnding(input, 4);
	}
	else {
		return false;
	}
}

//Next Letter Checker
bool Validator::NextTwoLetterIsSquare(std::string input, int nextLetterIndex)
{
	if (input.length() <= nextLetterIndex + 1) return false;
	return isFileChar(input[nextLetterIndex]) && isRankChar(input[nextLetterIndex + 1]);
}

bool Validator::NextLetterIsEnding(std::string input, int nextLetterIndex)
{
	if (input.length() == nextLetterIndex) return true;
	if ((input[nextLetterIndex] == '+' || input[nextLetterIndex] == '#') && input.length() == nextLetterIndex + 1) return true;
	return false;
}

bool Validator::NextLetterIsPromotion(std::string input, int nextLetterIndex)
{
	char nextLetter = input[nextLetterIndex];
	if (isPieceChar(nextLetter) && NextLetterIsEnding(input, nextLetterIndex + 1)) return true;
	if (input.length() > nextLetterIndex + 1 && nextLetter == '=' && isPieceChar(input[nextLetterIndex + 1]) && NextLetterIsEnding(input, nextLetterIndex + 1)) return true;
	return false;
}
