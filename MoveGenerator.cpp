#include "MoveGenerator.h"

Move MoveGenerator::ExtractMove(char pieceType, int target, int file, int rank, bool white, char promotionType, std::vector<Move>& moves)
{
	std::vector<Move> tmpMoves = ExtractMovesByPieceType(pieceType, white, moves);
	if (tmpMoves.size() < 1) return Move();
	std::vector<Move> tmpMoves1 = ExtractMovesByTargetSquare(target, tmpMoves);
	if (tmpMoves1.size() == 1) return tmpMoves1[0];
	if (tmpMoves1.size() < 1) return Move();
	std::vector<Move> tmpMoves2 = ExtractMovesByAmbiguity(file, rank, tmpMoves1);
	//std::cout << "tmpMoves2: " << tmpMoves2.size() << std::endl;
	if (tmpMoves2.size() == 1) return tmpMoves2[0];
	if (tmpMoves1.size() < 1) return Move();
	std::vector<Move> tmpMoves3 = ExtractMovesByPromotionType(promotionType, tmpMoves2);
	if (tmpMoves3.size() == 1) return tmpMoves3[0];
	return Move();
}

std::vector<Move> MoveGenerator::ExtractMovesByPieceType(char pieceType, bool white, std::vector<Move>& moves)
{
	std::cout << "ExtractMovesByPieceType" << std::endl;
	std::vector<Move> result;
	char finalType = white ? toupper(pieceType) : tolower(pieceType);
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
			moves[i].UpdateAmbiguity(true, true);
		}
		else if (file == 99 && r == rank) {
			result.push_back(moves[i]);
			moves[i].UpdateAmbiguity(true, false);
		}
		else if (f == file && rank == 99) {
			result.push_back(moves[i]);
			moves[i].UpdateAmbiguity(false, true);
		}
	}
	return result;
}

std::vector<Move> MoveGenerator::ExtractMovesByPromotionType(char promotionType, std::vector<Move>& moves)
{
	std::cout << "ExtractMovesByPromotionType" << std::endl;
	std::vector<Move> result;
	for (int i = 0; i < moves.size(); ++i) {
		char t = moves[i].promotionType;
		if (t == promotionType) result.push_back(moves[i]);
	}
	return result;
}

std::vector<Move> MoveGenerator::GenerateAllPossibleMoves(Position& position)
{
	std::vector<Move> result;
	for(int i = 0; i < position.pieceOnBoard.size(); i++){
		int piece = position.pieceOnBoard[i];
		if(PieceMatchTurn(piece, position)){
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
	//std::cout << "GenerateSlidingMoves for " << pieceType << ChessUtil::SquareToString(starting) << std::endl;
	int startingDirection = 0;
	int endingDirection = 7;
	if (pieceType == 'r' || pieceType == 'R') { startingDirection = 0; endingDirection = 3; }
	if (pieceType == 'b' || pieceType == 'B') { startingDirection = 4; endingDirection = 7; }
	if (pieceType == 'q' || pieceType == 'Q') { startingDirection = 0; endingDirection = 7; }
	for (int i = startingDirection; i <= endingDirection; ++i) {
		std::vector<int> slidingSquare = ChessUtil::squareControlMap[starting].GetSlidingSquare(i);
		for(int j = 0; j < slidingSquare.size(); j++){
			bool empty = position.TargetIsEmpty(slidingSquare[j]);
			bool oppositeColor = position.TargetIsOppositeColor(piece, slidingSquare[j]);
			if(!empty && !oppositeColor) break;
			if((!empty && oppositeColor) || empty){
				Move move = Move(piece, starting, slidingSquare[j]);
				if(LegalChecker::IsLegal(position, move)){
					//std::cout << move.toSimpleString() << " is legal" << std::endl;
					result.push_back(move);
				}else{
					//std::cout << move.toSimpleString() << " is illegal" << std::endl;
				}
				if(!empty) break;
			}
		}
	}
	return result;
}

std::vector<Move> MoveGenerator::GenerateKnightMoves(int& piece, Position& position)
{
	std::vector<Move> result;
	int starting = position.GetPieceLocation(piece);

	std::vector<int> knightSquare = ChessUtil::squareControlMap[starting].GetKnightSquare();
	//std::cout << "Knight from " << ChessUtil::SquareToString(starting) << " has possible landing square: " << knightSquare.size() << std::endl;
    for(int i = 0; i < knightSquare.size(); i++){
        bool emptyOrOpposite = position.TargetIsEmpty(knightSquare[i]) || position.TargetIsOppositeColor(piece, knightSquare[i]);
        if(emptyOrOpposite){
			Move move = Move(piece, starting, knightSquare[i]);
			if(LegalChecker::IsLegal(position, move)){
				//std::cout << move.toSimpleString() << " is legal" << std::endl;
				result.push_back(move);
			}else{
				//std::cout << move.toSimpleString() << " is illegal" << std::endl;
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

	std::vector<int> pawnTakeSquare = ChessUtil::squareControlMap[starting].GetPawnSquare(ChessUtil::IsWhite(piece));
	std::vector<int> targetSquare;
	//std::cout << "GeneratePawnMoves for " << ChessUtil::SquareToString(starting) << std::endl;
	//Push one square
	if (pushOneTarget >= 0 && pushOneTarget < 64 && position.TargetIsEmpty(pushOneTarget)) {
		targetSquare.push_back(pushOneTarget);
	}
	//Push two square
	if (position.TargetIsEmpty(pushOneTarget) && firstMove) {
		int pushTwoTarget = starting + (ChessUtil::IsWhite(piece) ? ChessUtil::offsets[3] * 2 : ChessUtil::offsets[2] * 2);
		if (position.TargetIsEmpty(pushTwoTarget)){
			targetSquare.push_back(pushTwoTarget);
		}
	}
	//Take and En passant
	for(int i = 0; i < pawnTakeSquare.size(); i++){
		bool opposite = position.TargetIsOppositeColor(piece, pawnTakeSquare[i]);
		bool enSquare = pawnTakeSquare[i] == position.enPassantSquare;
		bool enOpposite = position.EnpassantSquareIsOppositeColor(piece);
		if(opposite || (enSquare && enOpposite)){
			targetSquare.push_back(pawnTakeSquare[i]);
		}
	}
	//Promotion
	for(int i = 0; i < targetSquare.size(); i++){
		if(ChessUtil::GetRank(targetSquare[i]) == 0 || ChessUtil::GetRank(targetSquare[i]) == 7){
			Move promoteQueen = Move(piece, starting, targetSquare[i], 'Q');
			Move promoteKnight = Move(piece, starting, targetSquare[i], 'N');
			Move promoteBishop = Move(piece, starting, targetSquare[i], 'B');
			Move promoteRook = Move(piece, starting, targetSquare[i], 'R');
			if(LegalChecker::IsLegal(position, promoteQueen)){
				//std::cout << promoteQueen.toSimpleString() << " is legal" << std::endl;
				result.push_back(promoteQueen);
				result.push_back(promoteKnight);
				result.push_back(promoteBishop);
				result.push_back(promoteRook);
			}else{
				//std::cout << promoteQueen.toSimpleString() << " is illegal" << std::endl;
			}
		}else{
			Move move = Move(piece, starting, targetSquare[i]);
			if(LegalChecker::IsLegal(position, move)){
				//std::cout << move.toSimpleString() << " is legal" << std::endl;
				result.push_back(move);
			}else{
				//std::cout << move.toSimpleString() << " is illegal" << std::endl;
			}
		}
	}
	return result;
}

std::vector<Move> MoveGenerator::GenerateKingMoves(int& piece, Position& position)
{
	std::vector<Move> result;
	int starting = position.GetPieceLocation(piece);

	std::vector<int> kingSquare = ChessUtil::squareControlMap[starting].GetKingSquare();

	//std::cout << "GenerateKingMoves for K" << ChessUtil::SquareToString(starting) << std::endl;
	//Normal move
	for (int i = 0; i < kingSquare.size(); i++)
	{
		bool emptyOrOpposite = position.TargetIsEmpty(kingSquare[i]) || position.TargetIsOppositeColor(piece, kingSquare[i]);
		if (emptyOrOpposite) {
			Move move = Move(piece, starting, kingSquare[i]);
			if(LegalChecker::IsLegal(position, move)){
				//std::cout << move.toSimpleString() << " is legal" << std::endl;
				result.push_back(move);
			}else{
				//std::cout << move.toSimpleString() << " is illegal" << std::endl;
			}
		}
	}
	//Castling
	if(position.GetCastlingQuota(piece,true)){//King side
		if(ChessUtil::IsWhite(piece)){
			//king did not move
			bool kingNotMoved = position.GetPieceLocation(4) == 4;
			//rook 7 exist
			bool rookExists = position.GetPieceLocation(7) == 7;
			//5,6 is empty
			bool emptyPath = position.TargetIsEmpty(5) && position.TargetIsEmpty(6);
			//4,5,6 is not checked
			bool pathNotChecked = !LegalChecker::IsCheckedAt(4, position, true) && !LegalChecker::IsCheckedAt(5, position, true) && !LegalChecker::IsCheckedAt(6, position, true);
			if(kingNotMoved&&rookExists&&emptyPath&&pathNotChecked) {
				//std::cout << "White Castling King side is legal" << std::endl;
				result.push_back(Move(piece, 4, 6));
			}else{
				//std::cout << "White Castling King side is illegal" << std::endl;
			}
			//std::cout << "rookExists: " << rookExists << " ,emptyPath: " <<emptyPath << " ,pathNotChecked: " << pathNotChecked << std::endl;
		}else{
			//king did not move
			bool kingNotMoved = position.GetPieceLocation(60) == 60;
			//rook 63 exist
			bool rookExists = position.GetPieceLocation(63) == 63;
			//62,61 is empty
			bool emptyPath = position.TargetIsEmpty(61) && position.TargetIsEmpty(62);
			//60,61,62 is not checked
			bool pathNotChecked = !LegalChecker::IsCheckedAt(60, position, false) && !LegalChecker::IsCheckedAt(61, position, false) && !LegalChecker::IsCheckedAt(62, position, false);
			if(kingNotMoved&&rookExists&&emptyPath&&pathNotChecked) {
				//std::cout << "Black Castling King side is legal" << std::endl;
				result.push_back(Move(piece, 60, 62));
			}else{
				//std::cout << "Black Castling King side is illegal" << std::endl;
			}
			//std::cout << "rookExists: " << rookExists << " ,emptyPath: " <<emptyPath << " ,pathNotChecked: " << pathNotChecked << std::endl;
		}
	}
	if(position.GetCastlingQuota(piece,false)){//Queen side
		if(ChessUtil::IsWhite(piece)){
			//king did not move
			bool kingNotMoved = position.GetPieceLocation(4) == 4;
			//rook 0 exist
			bool rookExists = position.GetPieceLocation(0) == 0;
			//1,2,3 is empty
			bool emptyPath = position.TargetIsEmpty(1) && position.TargetIsEmpty(2) && position.TargetIsEmpty(3);
			//2,3,4 is not checked
			bool pathNotChecked = !LegalChecker::IsCheckedAt(2, position, true) && !LegalChecker::IsCheckedAt(3, position, true) && !LegalChecker::IsCheckedAt(4, position, true);
			if(kingNotMoved&&rookExists&&emptyPath&&pathNotChecked) {
				//std::cout << "White Castling Queen side is legal" << std::endl;
				result.push_back(Move(piece, 4, 2));
			}else{
				//std::cout << "White Castling Queen side is illegal" << std::endl;
			}
			//std::cout << "rookExists: " << rookExists << " ,emptyPath: " <<emptyPath << " ,pathNotChecked: " << pathNotChecked << std::endl;
		}else{
			//king did not move
			bool kingNotMoved = position.GetPieceLocation(60) == 60;
			//rook 56 exist
			bool rookExists = position.GetPieceLocation(56) == 56;
			//57,58,59 is empty
			bool emptyPath = position.TargetIsEmpty(57) && position.TargetIsEmpty(58) && position.TargetIsEmpty(59);
			//58,59,60 is not checked
			bool pathNotChecked = !LegalChecker::IsCheckedAt(58, position, false) && !LegalChecker::IsCheckedAt(59, position, false) && !LegalChecker::IsCheckedAt(60, position, false);
			if(kingNotMoved&&rookExists&&emptyPath&&pathNotChecked) {
				//std::cout << "Black Castling Queen side is legal" << std::endl;
				result.push_back(Move(piece, 60, 58));
			}else{
				//std::cout << "Black Castling Queen side is illegal" << std::endl;
			}
			//std::cout << "rookExists: " << rookExists << " ,emptyPath: " <<emptyPath << " ,pathNotChecked: " << pathNotChecked << std::endl;
		}
	}
	return result;
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