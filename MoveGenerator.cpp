#include "MoveGenerator.h"

Move MoveGenerator::ExtractMove(char pieceType, short target, short file, short rank, bool white, char promotionType, std::vector<Move>& moves)
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
		short piece = moves[i].piece;
		char type = ChessUtil::pieceMapping[piece];
		if (type == finalType) result.push_back(moves[i]);
	}
	return result;
}

std::vector<Move> MoveGenerator::ExtractMovesByTargetSquare(short target, std::vector<Move>& moves)
{
	std::cout << "ExtractMovesByTargetSquare" << std::endl;
	std::vector<Move> result;
	for (int i = 0; i < moves.size(); ++i) {
		short t = moves[i].to;
		if (t == target) result.push_back(moves[i]);
	}
	return result;
}

std::vector<Move> MoveGenerator::ExtractMovesByAmbiguity(short file, short rank, std::vector<Move>& moves)
{
	std::cout << "ExtractMovesByAmbiguity" << std::endl;
	std::vector<Move> result;
	for (int i = 0; i < moves.size(); ++i) {
		short starting = moves[i].from;
		short f = ChessUtil::GetFile(starting);
		short r = ChessUtil::GetRank(starting);
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
	std::vector<short> pieceOnBoard = position.whiteTurn ? position.whitePieceOnBoard : position.blackPieceOnBoard;

	for(int i = 0; i < pieceOnBoard.size(); i++){
		short piece = pieceOnBoard[i];
		//std::cout << "Generating move for " << piece << std::endl;
		if(PieceMatchTurn(piece, position)){
			std::vector<Move> pieceResult = GeneratePossibleMoves(piece,position);
			result.insert(result.end(), pieceResult.begin(), pieceResult.end());
		}
	}
	return result;
}

std::vector<Move> MoveGenerator::GeneratePossibleMoves(short& piece, Position& position)
{
	char pieceType = ChessUtil::GetPieceType(piece);
	//std::cout << "Generating move for " << piece << std::endl;
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

std::vector<Move> MoveGenerator::GenerateSlidingMoves(short& piece, Position& position)
{
	std::vector<Move> result;
	char pieceType = ChessUtil::GetPieceType(piece);
	short starting = position.GetPieceLocation(piece);
	//std::cout << "GenerateSlidingMoves for " << pieceType << ChessUtil::SquareToString(starting) << std::endl;
	short startingDirection = 0;
	short endingDirection = 7;
	if (pieceType == 'r' || pieceType == 'R') { startingDirection = 0; endingDirection = 3; }
	if (pieceType == 'b' || pieceType == 'B') { startingDirection = 4; endingDirection = 7; }
	if (pieceType == 'q' || pieceType == 'Q') { startingDirection = 0; endingDirection = 7; }
	for (int i = startingDirection; i <= endingDirection; ++i) {
		std::vector<short> slidingSquare = ChessUtil::squareControlMap[starting].GetSlidingSquare(i);
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

std::vector<Move> MoveGenerator::GenerateKnightMoves(short& piece, Position& position)
{
	std::vector<Move> result;
	int starting = position.GetPieceLocation(piece);

	std::vector<short> knightSquare = ChessUtil::squareControlMap[starting].GetKnightSquare();
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

std::vector<Move> MoveGenerator::GeneratePawnMoves(short& piece, Position& position) {
	std::vector<Move> result;
	short starting = position.GetPieceLocation(piece);
	bool firstMove = ChessUtil::GetRank(starting) == (ChessUtil::IsWhite(piece) ? 1 : 6);
	short pushOneTarget = starting + (ChessUtil::IsWhite(piece) ? ChessUtil::offsets[3] : ChessUtil::offsets[2]);

	std::vector<short> pawnTakeSquare = ChessUtil::squareControlMap[starting].GetPawnSquare(ChessUtil::IsWhite(piece));
	std::vector<short> targetSquare;
	//std::cout << "GeneratePawnMoves for " << ChessUtil::SquareToString(starting) << std::endl;
	//Push one square
	if (pushOneTarget >= 0 && pushOneTarget < 64 && position.TargetIsEmpty(pushOneTarget)) {
		targetSquare.push_back(pushOneTarget);
	}
	//Push two square
	if (position.TargetIsEmpty(pushOneTarget) && firstMove) {
		short pushTwoTarget = starting + (ChessUtil::IsWhite(piece) ? ChessUtil::offsets[3] * 2 : ChessUtil::offsets[2] * 2);
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

std::vector<Move> MoveGenerator::GenerateKingMoves(short& piece, Position& position)
{
	std::vector<Move> result;
	short starting = position.GetPieceLocation(piece);

	std::vector<short> kingSquare = ChessUtil::squareControlMap[starting].GetKingSquare();

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
			bool pathNotChecked = !position.OpponentCanReach(4, true) && !position.OpponentCanReach(5, true) && !position.OpponentCanReach(6, true);
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
			bool pathNotChecked = !position.OpponentCanReach(60, false) && !position.OpponentCanReach(61, false) && !position.OpponentCanReach(62, false);
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
			bool pathNotChecked = !position.OpponentCanReach(2, true) && !position.OpponentCanReach(3, true) && !position.OpponentCanReach(4, true);
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
			bool pathNotChecked = !position.OpponentCanReach(58, false) && !position.OpponentCanReach(59, false) && !position.OpponentCanReach(60, false);
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

bool MoveGenerator::PieceMatchTurn(short piece, Position& position)
{
	return ChessUtil::IsWhite(piece) == position.whiteTurn;
}