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

bool Validator::ValidMove(std::string input, char& pieceType, int& target, int& file, int& rank, char& promotionType, bool& isWhite)
{
	if (input.length() < 2) return false;
	if (input == "Resign" || input == "resign") return true;

	char first_letter = input[0];
	if (isPieceChar(first_letter)) {
		pieceType = first_letter;
		return isValidPieceMove(input, target, file, rank);
	}
	else if (isFileChar(first_letter)) {
		pieceType = 'p';
		file = ChessUtil::GetFileFromChar(first_letter);
		return isValidPawnMove(input, target, promotionType);
	}
	else if (isCastleChar(first_letter)) {
		pieceType = 'k';
		return isCastlingMove(input, target, isWhite);
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
bool Validator::isCastlingMove(std::string input, int& target, bool& isWhite)
{
	if (isWhite) {
		if (input == "O-O-O" || input == "o-o-o" || input == "0-0-0") target = 1;
		if (input == "O-O" || input == "o-o" || input == "0-0") target = 6;
	}
	else {
		if (input == "O-O-O" || input == "o-o-o" || input == "0-0-0") target = 57;
		if (input == "O-O" || input == "o-o" || input == "0-0") target = 62;
	}
	return input == "O-O-O" || input == "o-o-o" || input == "0-0-0" || input == "O-O" || input == "o-o" || input == "0-0";
}

bool Validator::isValidPawnMove(std::string input, int& target, char& promotionType)
{
	char second_letter = input[1];
	if (isRankChar(second_letter)) {
		if (NextLetterIsPromotion(input, 2) || NextLetterIsEnding(input, 2)) {
			target = ChessUtil::StringToSquare(std::string({ input[0] ,second_letter }));//eg:b8=Q
			if (NextLetterIsPromotion(input, 2)) promotionType = input[3];
			return true;
		}
		return false;
	}
	else if (isTakeChar(second_letter)) {
		if (NextTwoLetterIsSquare(input, 2)) {
			if (NextLetterIsPromotion(input, 4) || NextLetterIsEnding(input, 4)) {
				target = ChessUtil::StringToSquare(std::string({ input[2] ,input[3] }));//eg:bxc8=Q
				if (NextLetterIsPromotion(input, 4)) promotionType = input[5];
				return true;
			}
			return false;
		}
		return false;
	}
	return false;
}

bool Validator::isValidPieceMove(std::string input, int& target, int& file, int& rank)
{
	char second_letter = input[1];
	char third_letter = input[2];
	char forth_letter = input[3];
	if (isFileChar(second_letter)) {
		if (isTakeChar(third_letter)) {
			if (NextTwoLetterIsSquare(input, 3) && NextLetterIsEnding(input, 5)) {
				target = ChessUtil::StringToSquare(std::string({ forth_letter ,input[4] }));//eg:Nbxc2
				return true;
			}
			return false;
		}
		else if (isRankChar(third_letter)) {
			if (isTakeChar(forth_letter)) {
				if(NextTwoLetterIsSquare(input, 4) && NextLetterIsEnding(input, 6)) {
					target = ChessUtil::StringToSquare(std::string({ input[4] ,input[5] }));//eg:Nb1xc2
					return true;
				}
				return false;
			}
			else if (isFileChar(forth_letter)) {
				if(NextTwoLetterIsSquare(input, 3) && NextLetterIsEnding(input, 5)) {
					target = ChessUtil::StringToSquare(std::string({ forth_letter ,input[4] }));//eg:Nb1c2
					return true;
				}
				return false;
			}
			else {
				if(NextLetterIsEnding(input, 3)) {
					target = ChessUtil::StringToSquare(std::string({ second_letter ,third_letter }));//eg:Nc2
					return true;
				}
				return false;
			}
		}
		else {
			if (NextTwoLetterIsSquare(input, 2) && NextLetterIsEnding(input, 4)) {
				target = ChessUtil::StringToSquare(std::string({ third_letter ,forth_letter }));//eg:Nbc2
				return true;
			}
			return false;
		}
	}
	else if (isRankChar(second_letter)) {
		if (isTakeChar(third_letter)) {
			if (NextTwoLetterIsSquare(input, 3) && NextLetterIsEnding(input, 5)) {
				target = ChessUtil::StringToSquare(std::string({ forth_letter ,input[4] }));//eg:N1xc2
				return true;
			}
			return false;
		}
		else {
			if(NextTwoLetterIsSquare(input, 2) && NextLetterIsEnding(input, 4)) {
				target = ChessUtil::StringToSquare(std::string({ third_letter ,forth_letter }));//eg:N1c2
				return true;
			}
			return false;
		}
	}
	else if (isTakeChar(second_letter)) {
		if (NextTwoLetterIsSquare(input, 2) && NextLetterIsEnding(input, 4)) {
			target = ChessUtil::StringToSquare(std::string({ third_letter ,forth_letter }));//eg:Nxc2
			return true;
		}
		return false;
	}
	return false;
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
	if (input.length() > nextLetterIndex + 1 && nextLetter == '=' && isPieceChar(input[nextLetterIndex + 1]) && NextLetterIsEnding(input, nextLetterIndex + 1)) return true;
	return false;
}
