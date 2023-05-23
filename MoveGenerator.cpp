#include "MoveGenerator.h"

Move MoveGenerator::ExtractMove(char pieceType, int target, int file, int rank, bool white, std::vector<Move>& moves)
{
	std::vector<Move> tmpMoves = ExtractMovesByPieceType(pieceType, white, moves);
	if (tmpMoves.size() < 1) return Move();
	std::vector<Move> tmpMoves1 = ExtractMovesByTargetSquare(target, tmpMoves);
	if (tmpMoves1.size() == 1) return tmpMoves1[0];
	if (tmpMoves1.size() < 1) return Move();
	std::vector<Move> tmpMoves2 = ExtractMovesByAmbiguity(file, rank, tmpMoves1);
	if (tmpMoves2.size() == 1) return tmpMoves2[0];
	return Move();
}

std::vector<Move> MoveGenerator::ExtractMovesByPieceType(char pieceType, bool white, std::vector<Move>& moves)
{
	std::cout << "ExtractMovesByPieceType" << std::endl;
	std::vector<Move> result;
	char finalType = white ? tolower(pieceType) : toupper(pieceType);
	for (int i = 0; i < moves.size(); ++i) {
		int piece = moves[i].piece;
		char type = ChessUtil::pieceMapping[piece];
		if (type == finalType) result.push_back(moves[i]);
	}
	return result;
}

std::vector<Move> MoveGenerator::ExtractMovesByTargetSquare(int target, std::vector<Move>& moves)
{
	std::cout << "ExtractMovesByTargetSquare" << std::endl;
	std::vector<Move> result;
	for (int i = 0; i < moves.size(); ++i) {
		int t = moves[i].to;
		if (t == target) result.push_back(moves[i]);
	}
	return result;
}

std::vector<Move> MoveGenerator::ExtractMovesByAmbiguity(int file, int rank, std::vector<Move>& moves)
{
	std::cout << "ExtractMovesByAmbiguity" << std::endl;
	std::vector<Move> result;
	for (int i = 0; i < moves.size(); ++i) {
		int starting = moves[i].from;
		int f = ChessUtil::GetFile(starting);
		int r = ChessUtil::GetRank(starting);
		if (f == file && r == rank) {
			result.push_back(moves[i]);
		}
		else if (file == 99 && r == rank) {
			result.push_back(moves[i]);
		}
		else if (f == file && rank == 99) {
			result.push_back(moves[i]);
		}
	}
	return result;
}

std::vector<Move> MoveGenerator::GenerateAllPossibleMoves(Position& position)
{
	std::vector<Move> result;
	for (int i = 0; i < 64; ++i) {
		int piece = position.position[i];
		if(piece != 99 && PieceMatchTurn(piece, position)){
			std::vector<Move> pieceResult = GeneratePossibleMoves(piece,position);
			result.insert(result.end(), pieceResult.begin(), pieceResult.end());
		}
	}
	return result;
}

std::vector<Move> MoveGenerator::GeneratePossibleMoves(int& piece, Position& position)
{
	char pieceType = ChessUtil::GetPieceType(piece);
	if (pieceType == 'r' || pieceType == 'R' || pieceType == 'b' || pieceType == 'B' || pieceType == 'q' || pieceType == 'Q') {
		return GenerateSlidingMoves(piece, position);
	}
	else if (pieceType == 'n' || pieceType == 'N') {
		return GenerateKnightMoves(piece, position);
	}
	else if(pieceType == 'p' || pieceType == 'P'){
		return GeneratePawnMoves(piece,position);
	}
	else if (pieceType == 'k' || pieceType == 'K') {
		return GenerateKingMoves(piece, position);
	}
	else {
		return std::vector<Move>();
	}
}

std::vector<Move> MoveGenerator::GenerateSlidingMoves(int& piece, Position& position)
{
	std::vector<Move> result;
	char pieceType = ChessUtil::GetPieceType(piece);
	int starting = position.GetPieceLocation(piece);
	std::cout << "GenerateSlidingMoves for " << pieceType << ChessUtil::SquareToString(starting) << std::endl;
	int startingDirection = 0;
	int endingDirection = 7;
	if (pieceType == 'r' || pieceType == 'R') { startingDirection = 0; endingDirection = 3; }
	if (pieceType == 'b' || pieceType == 'B') { startingDirection = 4; endingDirection = 7; }
	if (pieceType == 'q' || pieceType == 'Q') { startingDirection = 0; endingDirection = 7; }
	for (int i = startingDirection; i <= endingDirection; ++i) {
		int offset = ChessUtil::offsets[i];
		int target = starting + offset;
		bool outOfBound = ChessUtil::SquareOutbound(starting, target, i);
		bool empty = position.TargetIsEmpty(target);
		bool oppositeColor = position.TargetIsOppositeColor(piece, target);
		//std::cout << "Target: " << target << " outOfBound: " << outOfBound << " empty: " << empty << " oppositeColor: " << oppositeColor << std::endl;
		while (!outOfBound && (empty || oppositeColor)) {

			Move move = Move(piece, starting, target);
			if(LegalChecker::IsLegal(position, move))result.push_back(move);

			if (oppositeColor) break;
			target += offset;
			outOfBound = ChessUtil::SquareOutbound(starting, target, i);
			empty = position.TargetIsEmpty(target);
			oppositeColor = position.TargetIsOppositeColor(piece, target);
			//std::cout << "Target: " << target << " outOfBound: " << outOfBound << " empty: " << empty << " oppositeColor: " << oppositeColor << std::endl;
		}
	}
	return result;
}

std::vector<Move> MoveGenerator::GenerateKnightMoves(int& piece, Position& position)
{
	std::vector<Move> result;
	int starting = position.GetPieceLocation(piece);
	int targets[8] = {starting - 10, starting - 17, starting -15, starting -6, starting + 6, starting + 15, starting + 17, starting + 10};
	std::cout << "GenerateKnightMoves for N" << ChessUtil::SquareToString(starting) << std::endl;
	for (int i = 0; i < 8; i++)
	{
		if (targets[i] > 63 || targets[i] < 0) continue;
		bool emptyOrOpposite = position.TargetIsEmpty(targets[i]) || position.TargetIsOppositeColor(piece, targets[i]);
		if (i == 0 || i == 1) {
			bool lefter = ChessUtil::GetFile(targets[i]) < ChessUtil::GetFile(starting);
			bool lower = ChessUtil::GetRank(targets[i]) < ChessUtil::GetRank(starting);
			if (lefter && lower && emptyOrOpposite) {
				Move move = Move(piece, starting, targets[i]);
				if(LegalChecker::IsLegal(position, move))result.push_back(move);
			}
		}
		else if (i == 2 || i == 3) {
			bool righter = ChessUtil::GetFile(targets[i]) > ChessUtil::GetFile(starting);
			bool lower = ChessUtil::GetRank(targets[i]) < ChessUtil::GetRank(starting);
			if (righter && lower && emptyOrOpposite) {
				Move move = Move(piece, starting, targets[i]);
				if(LegalChecker::IsLegal(position, move))result.push_back(move);
			}
		}
		else if (i == 4 || i == 5) {
			bool lefter = ChessUtil::GetFile(targets[i]) < ChessUtil::GetFile(starting);
			bool higher = ChessUtil::GetRank(targets[i]) > ChessUtil::GetRank(starting);
			if (lefter && higher && emptyOrOpposite) {
				Move move = Move(piece, starting, targets[i]);
				if(LegalChecker::IsLegal(position, move))result.push_back(move);
			}
		}
		else if (i == 6 || i == 7) {
			bool righter = ChessUtil::GetFile(targets[i]) > ChessUtil::GetFile(starting);
			bool higher = ChessUtil::GetRank(targets[i]) > ChessUtil::GetRank(starting);
			if (righter && higher && emptyOrOpposite) {
				Move move = Move(piece, starting, targets[i]);
				if(LegalChecker::IsLegal(position, move))result.push_back(move);
			}
		}
	}
	return result;
}

std::vector<Move> MoveGenerator::GeneratePawnMoves(int& piece, Position& position) {
	std::vector<Move> result;
	int starting = position.GetPieceLocation(piece);
	bool firstMove = ChessUtil::GetRank(starting) == (ChessUtil::IsWhite(piece) ? 1 : 6);
	int pushOneTarget = starting + (ChessUtil::IsWhite(piece) ? ChessUtil::offsets[3] : ChessUtil::offsets[2]);
	std::cout << "GeneratePawnMoves for " << ChessUtil::SquareToString(starting) << std::endl;
	//Push one square
	if (pushOneTarget >= 0 && pushOneTarget < 64 && position.TargetIsEmpty(pushOneTarget)) {
		Move move = Move(piece, starting, pushOneTarget);
		if(LegalChecker::IsLegal(position, move))result.push_back(move);
	}
	//Push two square
	if (position.TargetIsEmpty(pushOneTarget) && firstMove) {
		int pushTwoTarget = starting + (ChessUtil::IsWhite(piece) ? ChessUtil::offsets[3] * 2 : ChessUtil::offsets[2] * 2);
		if (position.TargetIsEmpty(pushTwoTarget)){
			Move move = Move(piece, starting, pushTwoTarget);
			if(LegalChecker::IsLegal(position, move))result.push_back(move);
		}
	}
	//Take and En passant
	if (ChessUtil::GetFile(starting) != 7) {
		int rightTarget = starting + (ChessUtil::IsWhite(piece) ? ChessUtil::offsets[7] : ChessUtil::offsets[5]);
		if (rightTarget >= 0 && rightTarget < 64 && position.TargetIsOppositeColor(piece, rightTarget)) {
			Move move = Move(piece, starting, rightTarget);
			if(LegalChecker::IsLegal(position, move))result.push_back(move);//Normal Take
		}
		else if (rightTarget == position.enPassantSquare && position.EnpassantSquareIsOppositeColor(piece)) {
			Move move = Move(piece, starting, rightTarget);
			if(LegalChecker::IsLegal(position, move))result.push_back(move);//En Passant
		}
	}
	if (ChessUtil::GetFile(starting) != 0) {
		int leftTarget = starting + (ChessUtil::IsWhite(piece) ? ChessUtil::offsets[6] : ChessUtil::offsets[4]);
		if (leftTarget >= 0 && leftTarget < 64 && position.TargetIsOppositeColor(piece, leftTarget)) {
			Move move = Move(piece, starting, leftTarget);
			if(LegalChecker::IsLegal(position, move))result.push_back(move);//Normal Take
		}
		else if (leftTarget == position.enPassantSquare && position.EnpassantSquareIsOppositeColor(piece)) {
			Move move = Move(piece, starting, leftTarget);
			if(LegalChecker::IsLegal(position, move))result.push_back(move);//En Passant
		}
	}
	//Promotion
	//TODO
	return result;
}

std::vector<Move> MoveGenerator::GenerateKingMoves(int& piece, Position& position)
{
	std::vector<Move> result;
	int starting = position.GetPieceLocation(piece);
	std::cout << "GenerateKingMoves for K" << ChessUtil::SquareToString(starting) << std::endl;
	//Normal move
	for (int i = 0; i < 8; i++)
	{
		int target = starting + ChessUtil::offsets[i];
		bool outOfBound = ChessUtil::SquareOutbound(starting, target, i);
		bool emptyOrOpposite = position.TargetIsEmpty(target) || position.TargetIsOppositeColor(piece, target);
		if (!outOfBound && emptyOrOpposite) {
			Move move = Move(piece, starting, target);
			if(LegalChecker::IsLegal(position, move))result.push_back(move);
		}
	}
	//TODO
	//Castling
	return result;
}

std::vector<Move> MoveGenerator::GenerateCastlingMoves(int& piece, Position& position)
{
	return std::vector<Move>();
}

std::vector<int> MoveGenerator::GenerateAllControlSquare(Position& position, bool white)
{
	std::vector<int> result;
	for (int i = 0; i < 64; ++i) {
		int piece = position.position[i];
		if(piece != 99 && ChessUtil::IsWhite(piece) == white){
			std::vector<int> pieceResult = GenerateControlSquare(piece,position);
			result.insert(result.end(), pieceResult.begin(), pieceResult.end());
		}
	}
	return result;
}

std::vector<int> MoveGenerator::GenerateControlSquare(int& piece, Position& position)
{
	char pieceType = ChessUtil::GetPieceType(piece);
	if (pieceType == 'r' || pieceType == 'R' || pieceType == 'b' || pieceType == 'B' || pieceType == 'q' || pieceType == 'Q') {
		return GenerateSlidingControlSquare(piece, position);
	}
	else if (pieceType == 'n' || pieceType == 'N') {
		return GenerateKnightControlSquare(piece, position);
	}
	else if(pieceType == 'p' || pieceType == 'P'){
		return GeneratePawnControlSquare(piece,position);
	}
	else if (pieceType == 'k' || pieceType == 'K') {
		return GenerateKingControlSquare(piece, position);
	}
	else {
		return std::vector<int>();
	}
}

std::vector<int> MoveGenerator::GenerateSlidingControlSquare(int& piece, Position& position)
{
	std::vector<int> result;
	char pieceType = ChessUtil::GetPieceType(piece);
	int starting = position.GetPieceLocation(piece);
	int startingDirection = 0;
	int endingDirection = 7;
	if (pieceType == 'r' || pieceType == 'R') { startingDirection = 0; endingDirection = 3; }
	if (pieceType == 'b' || pieceType == 'B') { startingDirection = 4; endingDirection = 7; }
	if (pieceType == 'q' || pieceType == 'Q') { startingDirection = 0; endingDirection = 7; }
	for (int i = startingDirection; i <= endingDirection; ++i) {
		int offset = ChessUtil::offsets[i];
		int target = starting + offset;
		bool outOfBound = ChessUtil::SquareOutbound(starting, target, i);
		bool empty = position.TargetIsEmpty(target);
		while (!outOfBound) {
			result.push_back(target);
			if (!empty) break;
			target += offset;
			outOfBound = ChessUtil::SquareOutbound(starting, target, i);
			empty = position.TargetIsEmpty(target);
		}
	}
	return result;
}

std::vector<int> MoveGenerator::GenerateKnightControlSquare(int& piece, Position& position)
{
	std::vector<int> result;
	int starting = position.GetPieceLocation(piece);
	int targets[8] = { starting - 10, starting - 17, starting - 15, starting - 6, starting + 6, starting + 15, starting + 17, starting + 10 };
	for (int i = 0; i < 8; i++)
	{
		if (targets[i] > 63 || targets[i] < 0) continue;
		if (i == 0 || i == 1) {
			bool lefter = ChessUtil::GetFile(targets[i]) < ChessUtil::GetFile(starting);
			bool lower = ChessUtil::GetRank(targets[i]) < ChessUtil::GetRank(starting);
			if (lefter && lower) result.push_back(targets[i]);
		}
		else if (i == 2 || i == 3) {
			bool righter = ChessUtil::GetFile(targets[i]) > ChessUtil::GetFile(starting);
			bool lower = ChessUtil::GetRank(targets[i]) < ChessUtil::GetRank(starting);
			if (righter && lower) result.push_back(targets[i]);
		}
		else if (i == 4 || i == 5) {
			bool lefter = ChessUtil::GetFile(targets[i]) < ChessUtil::GetFile(starting);
			bool higher = ChessUtil::GetRank(targets[i]) > ChessUtil::GetRank(starting);
			if (lefter && higher) result.push_back(targets[i]);
		}
		else if (i == 6 || i == 7) {
			bool righter = ChessUtil::GetFile(targets[i]) > ChessUtil::GetFile(starting);
			bool higher = ChessUtil::GetRank(targets[i]) > ChessUtil::GetRank(starting);
			if (righter && higher) result.push_back(targets[i]);
		}
	}
	return result;
}

std::vector<int> MoveGenerator::GeneratePawnControlSquare(int& piece, Position& position)
{
	std::vector<int> result;
	int starting = position.GetPieceLocation(piece);
	if (ChessUtil::GetFile(starting) != 7) {
		int rightTarget = starting + (ChessUtil::IsWhite(piece) ? ChessUtil::offsets[7] : ChessUtil::offsets[5]);
		if (rightTarget >= 0 && rightTarget < 64) {
			result.push_back(rightTarget);
		}
	}
	if (ChessUtil::GetFile(starting) != 0) {
		int leftTarget = starting + (ChessUtil::IsWhite(piece) ? ChessUtil::offsets[6] : ChessUtil::offsets[4]);
		if (leftTarget >= 0 && leftTarget < 64) {
			result.push_back(leftTarget);
		}
	}
	return result;
}

std::vector<int> MoveGenerator::GenerateKingControlSquare(int& piece, Position& position)
{
	std::vector<int> result;
	int starting = position.GetPieceLocation(piece);
	//Normal move
	for (int i = 0; i < 8; i++)
	{
		int target = starting + ChessUtil::offsets[i];
		bool outOfBound = ChessUtil::SquareOutbound(starting, target, i);
		if (!outOfBound) result.push_back(target);
	}
	return result;
}

bool MoveGenerator::PieceMatchTurn(int piece, Position& position)
{
	return ChessUtil::IsWhite(piece) == position.whiteTurn;
}