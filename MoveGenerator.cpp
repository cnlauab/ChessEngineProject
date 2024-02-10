#include "MoveGenerator.h"
//Get move from move list
unsigned short MoveGenerator::ExtractMove(char pieceType, short target, short file, short rank, bool white, char promotionType, std::vector<unsigned short>& moves, Position& position)
{
	std::vector<unsigned short> tmpMoves = ExtractMovesByPieceType(pieceType, white, moves, position);
	//for(unsigned short move :tmpMoves) std::cout << move.toString() << std::endl;
	if (tmpMoves.size() < 1) return 0;
	std::vector<unsigned short> tmpMoves1 = ExtractMovesByTargetSquare(target, tmpMoves);
	//for(unsigned short move :tmpMoves1) std::cout << move.toString() << std::endl;
	if (tmpMoves1.size() == 1) return tmpMoves1[0];
	if (tmpMoves1.size() < 1) return 0;
	std::vector<unsigned short> tmpMoves2 = ExtractMovesByAmbiguity(file, rank, tmpMoves1);
	//for(unsigned short move :tmpMoves2) std::cout << move.toString() << std::endl;
	if (tmpMoves2.size() == 1) return tmpMoves2[0];
	if (tmpMoves1.size() < 1) return 0;
	std::vector<unsigned short> tmpMoves3 = ExtractMovesByPromotionType(promotionType, tmpMoves2);
	//for(unsigned short move :tmpMoves3) std::cout << move.toString() << std::endl;
	if (tmpMoves3.size() == 1) return tmpMoves3[0];
	return 0;
}

std::vector<unsigned short> MoveGenerator::ExtractMovesByPieceType(char pieceType, bool white, std::vector<unsigned short>& moves, Position& position)
{
	//std::cout << "ExtractMovesByPieceType" << std::endl;
	std::vector<unsigned short> result;
	char finalType = white ? toupper(pieceType) : tolower(pieceType);
	for (int i = 0; i < moves.size(); ++i) {
		short starting = ChessUtil::GetFrom(moves[i]);
		int piece = position.bitboards.GetPieceTypeFromSquare(starting);
		char type = ' ';
		if(piece > -1){
			type = BitUtil::bitboardIndexPieceMapping[piece];
			if(position.bitboards.hasWhitePiece(starting)){
				type = toupper(type);
			}
		}
		if (type == finalType) result.push_back(moves[i]);
	}
	return result;
}

std::vector<unsigned short> MoveGenerator::ExtractMovesByTargetSquare(short target, std::vector<unsigned short>& moves)
{
	std::cout << "ExtractMovesByTargetSquare" << std::endl;
	std::vector<unsigned short> result;
	for (int i = 0; i < moves.size(); ++i) {
		short t = ChessUtil::GetTo(moves[i]);
		if (t == target) result.push_back(moves[i]);
	}
	return result;
}

std::vector<unsigned short> MoveGenerator::ExtractMovesByAmbiguity(short file, short rank, std::vector<unsigned short>& moves)
{
	std::cout << "ExtractMovesByAmbiguity" << std::endl;
	std::vector<unsigned short> result;
	for (int i = 0; i < moves.size(); ++i) {
		short starting = ChessUtil::GetFrom(moves[i]);
		short f = ChessUtil::GetFile(starting);
		short r = ChessUtil::GetRank(starting);
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

std::vector<unsigned short> MoveGenerator::ExtractMovesByPromotionType(char promotionType, std::vector<unsigned short>& moves)
{
	//std::cout << "ExtractMovesByPromotionType" << std::endl;
	std::vector<unsigned short> result;
	for (int i = 0; i < moves.size(); ++i) {
		char t = ChessUtil::GetPromotionType(moves[i]);
		if (t == promotionType) result.push_back(moves[i]);
	}
	return result;
}
//Generate Moves
std::vector<unsigned short> MoveGenerator::GenerateAllPossibleMoves(Position& position)
{
	std::vector<unsigned short> result;
	//ChessUtil::PrintMoveList(result);
	//std::cout << "GenerateAllPossibleMoves" << std::endl;
	KingMoves(result, position);
	//std::cout << "Double check: " << position.doubleCheck << std::endl;
	if(!position.doubleCheck){
		SlidingMoves(result, position);
		KnightMoves(result, position);
		PawnMoves(result, position);
	}
	if(result.size() == 0) {
		if(position.check){
			position.checkmate = true;
		}else{
			position.stalemate = true;
		}
	}
	//ChessUtil::PrintMoveList(result);
	return result;
}

//Util
void MoveGenerator::AddPawnMoves(Position& position, std::vector<unsigned short>& moves, short start, short target, bool capture){
	if(ChessUtil::GetRank(target) == 0 || ChessUtil::GetRank(target) == 7){
		unsigned short promoteQueen = ChessUtil::SimpleMove(start, target, capture, 'Q');
		unsigned short promoteKnight = ChessUtil::SimpleMove(start, target, capture, 'N');
		unsigned short promoteBishop = ChessUtil::SimpleMove(start, target, capture, 'B');
		unsigned short promoteRook = ChessUtil::SimpleMove(start, target, capture, 'R');
		LegalChecker::AddMoveToList(position,moves,promoteQueen);
		LegalChecker::AddMoveToList(position,moves,promoteKnight);
		LegalChecker::AddMoveToList(position,moves,promoteBishop);
		LegalChecker::AddMoveToList(position,moves,promoteRook);
	}else{
		unsigned short move = ChessUtil::SimpleMove(start, target, capture);
		bool ep = target == position.enPassantSquare;
		LegalChecker::AddMoveToList(position,moves,move,ep);
	}
}

void MoveGenerator::KingMoves(std::vector<unsigned short>& moves, Position& position){
	//std::cout << "############################" << std::endl;
	//King moves
	//ChessUtil::PrintMoveList(moves);
	short starting = position.bitboards.KingLocation(position.whiteTurn);
	unsigned long long friendlyBit = position.whiteTurn ? position.bitboards.allWhiteBitboard() : position.bitboards.allBlackBitboard();
	unsigned long long enemyBits = position.whiteTurn ? position.bitboards.allBlackBitboard() : position.bitboards.allWhiteBitboard();
	unsigned long long enemyControlBits = position.bitboards.controlledBits(!position.whiteTurn); 
	unsigned long long targetBits = ChessUtil::squareControlMap[starting].kingControlBitboard & ~(enemyControlBits | friendlyBit);
	//std::cout << "friendlyBit\n" << BitUtil::bitboardToString(friendlyBit) << std::endl;
	//std::cout << "enemyControlBits\n" << BitUtil::bitboardToString(enemyControlBits) << std::endl;
	//std::cout << "targetBits\n" << BitUtil::bitboardToString(targetBits) << std::endl;
	//Castling moves
	char kingColor = position.whiteTurn ? 'K' : 'k';
	char queenColor = position.whiteTurn ? 'Q' : 'q';
	if(position.GetCastlingQuota(kingColor)){
		//std::cout << "GetCastlingQuota: " << kingColor << std::endl;
		unsigned long long blockingBit = (enemyControlBits & BitUtil::castleBlockingBits[kingColor]) | (friendlyBit & BitUtil::friendlyCastleBlockingBits[kingColor]);
		short target = ChessUtil::castlingTargetMapping[kingColor];
		//std::cout << BitUtil::bitboardToString(blockingBit) << std::endl;
		if(blockingBit == 0ULL) {
			unsigned short&& move = ChessUtil::SimpleMove(starting, target);
			moves.push_back(move);
			//if(!position.whiteTurn) std::cout << ChessUtil::SimpleMoveToString(move) << std::endl;
		}
	}
	if(position.GetCastlingQuota(queenColor)){
		//std::cout << "GetCastlingQuota: " << queenColor << std::endl;
		unsigned long long blockingBit = (enemyControlBits & BitUtil::castleBlockingBits[queenColor]) | (friendlyBit & BitUtil::friendlyCastleBlockingBits[queenColor]);
		short target = ChessUtil::castlingTargetMapping[queenColor];
		//std::cout << BitUtil::bitboardToString(blockingBit) << std::endl;
		if(blockingBit == 0ULL) {
			unsigned short&& move = ChessUtil::SimpleMove(starting, target);
			moves.push_back(move);
			//if(!position.whiteTurn) std::cout << ChessUtil::SimpleMoveToString(move) << std::endl;
		}
	}

	std::vector<short> legalSquares = BitUtil::getBitPositions(targetBits);
	for(short target : legalSquares){
		//std::cout << "target: " << target << std::endl;
		bool capture = (enemyBits & (1ULL << target)) > 0ULL;
		unsigned short&& move = ChessUtil::SimpleMove(starting, target, capture);
		moves.push_back(move);
		//std::cout << "move: " << ChessUtil::SimpleMoveToString(move) << std::endl;
	}
	//ChessUtil::PrintMoveList(moves);
	//std::cout << "############################" << std::endl;
}

void MoveGenerator::KnightMoves(std::vector<unsigned short>& moves, Position& position){
	unsigned long long knightBits = position.whiteTurn ? position.bitboards.whiteBitboards[2] : position.bitboards.blackBitboards[2];
	unsigned long long enemyBits = position.whiteTurn ? position.bitboards.allBlackBitboard() : position.bitboards.allWhiteBitboard();
	unsigned long long emptyEnemyAndCheckedBy = (position.bitboards.allEmptySquareBitboard() | enemyBits) & position.bitboards.checkedBitboard;
	knightBits &= ~position.bitboards.pinnedBitboard;

	std::vector<short> knightSquare = BitUtil::getBitPositions(knightBits);
	for(short starting : knightSquare){
		unsigned long long targetBits = ChessUtil::squareControlMap[starting].knightControlBitboard;
		targetBits &= emptyEnemyAndCheckedBy;
		std::vector<short> targetSquare = BitUtil::getBitPositions(targetBits);
		for(short target :targetSquare){
			bool capture = (enemyBits & (1ULL << target)) > 0ULL;
			unsigned short&& move = ChessUtil::SimpleMove(starting, target, capture);
			moves.push_back(move);
			//std::cout << ChessUtil::SimpleMoveToString(move) << std::endl;
		}
	}
}

void MoveGenerator::SlidingMoves(std::vector<unsigned short>& moves, Position& position){
	unsigned long long targetBitsWhenChecked = position.check ? position.bitboards.checkedBitboard : ~0ULL;
	unsigned long long diagonalPieces = (position.whiteTurn) ? position.bitboards.whiteBitboards[1] | position.bitboards.whiteBitboards[3] : position.bitboards.blackBitboards[1] | position.bitboards.blackBitboards[3];
	unsigned long long nonDiagonalPieces = (position.whiteTurn) ? position.bitboards.whiteBitboards[1] | position.bitboards.whiteBitboards[4] : position.bitboards.blackBitboards[1] | position.bitboards.blackBitboards[4];
	unsigned long long enemyBits = (position.whiteTurn) ? position.bitboards.allBlackBitboard() : position.bitboards.allWhiteBitboard();
	std::vector<short> diagonalPiecesSquares = BitUtil::getBitPositions(diagonalPieces);
	std::vector<short> nonDiagonalPiecesSquares = BitUtil::getBitPositions(nonDiagonalPieces);

	for(short starting : diagonalPiecesSquares){
		bool pinned = ((1ULL << starting) & position.bitboards.pinnedBitboard) > 0ULL;
		unsigned long long movableBitsWhenPinned = pinned ? position.bitboards.pinnedRays[starting] : ~0ULL;
		unsigned long long targetBits = position.bitboards.slidingControlBits(position.whiteTurn, starting, 3);
		targetBits &= (movableBitsWhenPinned & targetBitsWhenChecked);
		std::vector<short> targetSquare = BitUtil::getBitPositions(targetBits);
		for(short target :targetSquare){
			bool capture = (enemyBits & (1ULL << target)) > 0ULL;
			unsigned short&& move = ChessUtil::SimpleMove(starting, target, capture);
			moves.push_back(move);
			//std::cout << ChessUtil::SimpleMoveToString(move) << std::endl;
		}
		//std::cout << BitUtil::bitboardToString(targetBits) << std::endl;
	}

	for(short starting : nonDiagonalPiecesSquares){
		bool pinned = ((1ULL << starting) & position.bitboards.pinnedBitboard) > 0ULL;
		unsigned long long movableBitsWhenPinned = pinned ? position.bitboards.pinnedRays[starting] : ~0ULL;
		unsigned long long targetBits = position.bitboards.slidingControlBits(position.whiteTurn, starting, 4);
		targetBits &= (movableBitsWhenPinned & targetBitsWhenChecked);
		std::vector<short> targetSquare = BitUtil::getBitPositions(targetBits);
		for(short target :targetSquare){
			bool capture = (enemyBits & (1ULL << target)) > 0ULL;
			unsigned short&& move = ChessUtil::SimpleMove(starting, target, capture);
			moves.push_back(move);
			//std::cout << ChessUtil::SimpleMoveToString(move) << std::endl;
		}
		//std::cout << BitUtil::bitboardToString(targetBits) << std::endl;
	}
}

void MoveGenerator::PawnMoves(std::vector<unsigned short>& moves, Position& position){
	bool white = position.whiteTurn;
	unsigned long long enPassantBit = 0ULL;
	unsigned long long pawnBits = white ? position.bitboards.whiteBitboards[0] : position.bitboards.blackBitboards[0];
	unsigned long long enemyBits = white ? position.bitboards.allBlackBitboard() : position.bitboards.allWhiteBitboard();
	unsigned long long friendlyBits = white ? position.bitboards.allWhiteBitboard() : position.bitboards.allBlackBitboard();
	std::vector<short> pawnSquares = BitUtil::getBitPositions(pawnBits);

	if(position.enPassantSquare != 99){
		enPassantBit |= 1ULL << position.enPassantSquare;
	}

	for(short starting : pawnSquares){
		unsigned long long targetBits = 0ULL;
		//Push
		unsigned long long pushOneBits = white ? ChessUtil::squareControlMap[starting].pawnShiftUpBitboard : ChessUtil::squareControlMap[starting].pawnShiftDownBitboard;
		pushOneBits &= ~(enemyBits | friendlyBits);
		if(pushOneBits > 0ULL){
			targetBits |= pushOneBits;
			unsigned long long pushTwoBits = white ? ChessUtil::squareControlMap[starting].pawnShiftTwoUpBitboard : ChessUtil::squareControlMap[starting].pawnShiftTwoDownBitboard;
			pushTwoBits &= ~(enemyBits | friendlyBits);
			if(pushTwoBits != 0ULL){
				targetBits |= pushTwoBits;
			}
		}
		//Capture
		unsigned long long captureBits = white ? ChessUtil::squareControlMap[starting].pawnControlUpBitboard : ChessUtil::squareControlMap[starting].pawnControlDownBitboard;
		captureBits &= (enemyBits | enPassantBit);
		targetBits |= captureBits;

		//Add Moves
		bool pinned = ((1ULL << starting) & position.bitboards.pinnedBitboard) > 0ULL;
		unsigned long long movableBitsWhenPinned = pinned ? position.bitboards.pinnedRays[starting] : ~0ULL;
		unsigned long long targetBitsWhenChecked = position.check ? position.bitboards.checkedBitboard : ~0ULL;
		if(position.enPassantSquare != 99) targetBitsWhenChecked |= 1ULL << position.enPassantSquare;
		targetBits &= (movableBitsWhenPinned & targetBitsWhenChecked);
		std::vector<short> targetSquares = BitUtil::getBitPositions(targetBits);
		for(short target : targetSquares){
			bool capture = (enemyBits & (1ULL << target)) > 0ULL || target == position.enPassantSquare;
			AddPawnMoves(position, moves, starting, target, capture);
		}
	}
}