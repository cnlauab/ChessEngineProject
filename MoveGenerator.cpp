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
	std::cout << "ExtractMovesByPieceType" << std::endl;
	std::vector<unsigned short> result;
	char finalType = white ? toupper(pieceType) : tolower(pieceType);
	for (int i = 0; i < moves.size(); ++i) {
		short starting = ChessUtil::GetFrom(moves[i]);
		short piece = position.ReadPosition(starting);
		char type = ChessUtil::pieceMapping[piece];
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
	std::cout << "ExtractMovesByPromotionType" << std::endl;
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
	//std::vector<unsigned short> result;
	//short king = position.whiteTurn ? 4 : 60;
	//std::vector<unsigned short> kingResult = GenerateKingMoves(king,position);
	//result.insert(result.end(), kingResult.begin(), kingResult.end());
	//if(!position.doubleCheck){
	//	std::vector<short> pieceOnBoard = position.whiteTurn ? position.whitePieceOnBoard : position.blackPieceOnBoard;
	//	for(int i = 0; i < pieceOnBoard.size(); i++){
	//		short piece = pieceOnBoard[i];
	//		char pieceType = tolower(ChessUtil::GetPieceType(piece));
	//		short typeIndex = BitUtil::pieceBitboardIndexMapping[pieceType];
	//		std::vector<unsigned short> pieceResult = MoveGenerationByType[typeIndex](piece, position);
	//		result.insert(result.end(), pieceResult.begin(), pieceResult.end());
	//	}
	//}
	//return result;
	std::vector<unsigned short> result;

	if(!position.check){
		std::vector<short> pieceOnBoard = position.whiteTurn ? position.whitePieceOnBoard : position.blackPieceOnBoard;
		for(int i = 0; i < pieceOnBoard.size(); i++){
			short piece = pieceOnBoard[i];
			std::vector<unsigned short> pieceResult = GeneratePossibleMoves(piece,position);
			result.insert(result.end(), pieceResult.begin(), pieceResult.end());
		}
		KingMoves(result, position);
		KnightMoves(result, position);
		return result;
	}else{
		result = GenerateMovesWhenChecked(position);
		KingMoves(result, position);
		KnightMoves(result, position);
		return result;
	}
}

std::vector<unsigned short> MoveGenerator::GeneratePossibleMoves(short& piece, Position& position)
{
	//std::cout << "Generating " << ChessUtil::SquareToString(position.GetPieceLocation(piece)) << std::endl;
	char pieceType = tolower(ChessUtil::GetPieceType(piece));
	if(pieceType == 'n' || pieceType == 'k') return std::vector<unsigned short>();
	short typeIndex = BitUtil::pieceBitboardIndexMapping[pieceType];
	if (position.pinnedPiece.find(piece) == position.pinnedPiece.end()){
        return MoveGenerationByType[typeIndex](piece, position);
	}else{
		return GenerateMovesWhenPinned(piece, position.pinnedPiece[piece], position);
	}
}

std::vector<unsigned short> MoveGenerator::GenerateSlidingMoves(short& piece, Position& position)
{
	std::vector<unsigned short> result;
	char pieceType = ChessUtil::GetPieceType(piece);
	short starting = position.GetPieceLocation(piece);
	//std::cout << "GenerateSlidingMoves for " << pieceType << ChessUtil::SquareToString(starting) << std::endl;
	short startingDirection = 0;
	short endingDirection = 7;
	if (pieceType == 'r' || pieceType == 'R') { startingDirection = 0; endingDirection = 3; }
	if (pieceType == 'b' || pieceType == 'B') { startingDirection = 4; endingDirection = 7; }
	for (int i = startingDirection; i <= endingDirection; ++i) {
		std::vector<short> slidingSquare = ChessUtil::squareControlMap[starting].GetSlidingSquare(i);
		for(int j = 0; j < slidingSquare.size(); j++){
			bool empty = position.TargetIsEmpty(slidingSquare[j]);
			bool oppositeColor = position.TargetIsOppositeColor(piece, slidingSquare[j]);
			if(!empty && !oppositeColor) break;
			if((!empty && oppositeColor) || empty){
				//Move move = Move(starting, slidingSquare[j]);
				unsigned short move = ChessUtil::SimpleMove(starting, slidingSquare[j], !empty);
				LegalChecker::AddMoveToList(position,result,move);
				if(!empty) break;
			}
		}
	}
	return result;
}

std::vector<unsigned short> MoveGenerator::GenerateKnightMoves(short& piece, Position& position)
{
	std::vector<unsigned short> result;
	int starting = position.GetPieceLocation(piece);

	if (position.pinnedPiece.find(piece) != position.pinnedPiece.end()){
		return result;
	}else{
		std::vector<short> knightSquare = ChessUtil::squareControlMap[starting].GetKnightSquare();
		//std::cout << "Knight from " << ChessUtil::SquareToString(starting) << " has possible landing square: " << knightSquare.size() << std::endl;
		for(int i = 0; i < knightSquare.size(); i++){
			bool empty = position.TargetIsEmpty(knightSquare[i]);
			bool emptyOrOpposite = empty || position.TargetIsOppositeColor(piece, knightSquare[i]);
			if(emptyOrOpposite){
				unsigned short move = ChessUtil::SimpleMove(starting, knightSquare[i], !empty);
				LegalChecker::AddMoveToList(position,result,move);
			}
		}
		return result;
	}
}

std::vector<unsigned short> MoveGenerator::GeneratePawnMoves(short& piece, Position& position) {
	if (position.pinnedPiece.find(piece) != position.pinnedPiece.end()){
		return GeneratePinnedPawnMoves(piece, position.pinnedPiece[piece], position);
	}else{
		std::vector<unsigned short> result;
		short starting = position.GetPieceLocation(piece);
		bool firstMove = ChessUtil::GetRank(starting) == (ChessUtil::IsWhite(piece) ? 1 : 6);
		short pushOneTarget = starting + (ChessUtil::IsWhite(piece) ? ChessUtil::offsets[3] : ChessUtil::offsets[2]);

		std::vector<short> pawnTakeSquare = ChessUtil::squareControlMap[starting].GetPawnSquare(ChessUtil::IsWhite(piece));
		std::vector<short> targetSquare;
		//std::cout << "GeneratePawnMoves for " << ChessUtil::SquareToString(starting) << std::endl;
		//Push one square
		if (pushOneTarget >= 0 && pushOneTarget < 64 && position.TargetIsEmpty(pushOneTarget)) {
			AddPawnMoves(position, result, starting, pushOneTarget, false);
		}
		//Push two square
		if (position.TargetIsEmpty(pushOneTarget) && firstMove) {
			short pushTwoTarget = starting + (ChessUtil::IsWhite(piece) ? ChessUtil::offsets[3] * 2 : ChessUtil::offsets[2] * 2);
			if (position.TargetIsEmpty(pushTwoTarget)){
				AddPawnMoves(position, result, starting, pushTwoTarget, false);
			}
		}
		//Take and En passant
		for(int i = 0; i < pawnTakeSquare.size(); i++){
			bool opposite = position.TargetIsOppositeColor(piece, pawnTakeSquare[i]);
			bool enSquare = pawnTakeSquare[i] == position.enPassantSquare;
			bool enOpposite = position.EnpassantSquareIsOppositeColor(piece);
			if(opposite || (enSquare && enOpposite)){
				AddPawnMoves(position, result, starting, pawnTakeSquare[i], true);
			}
		}
		return result;
	}
}

std::vector<unsigned short> MoveGenerator::GenerateKingMoves(short& piece, Position& position)
{
	std::vector<unsigned short> result;
	short starting = position.GetPieceLocation(piece);

	std::vector<short> kingSquare = ChessUtil::squareControlMap[starting].GetKingSquare();

	//std::cout << "GenerateKingMoves for K" << ChessUtil::SquareToString(starting) << std::endl;
	//Normal move
	for (int i = 0; i < kingSquare.size(); i++)
	{
		bool empty = position.TargetIsEmpty(kingSquare[i]);
		bool emptyOrOpposite = empty || position.TargetIsOppositeColor(piece, kingSquare[i]);
		if (emptyOrOpposite) {
			//Move move = Move(starting, kingSquare[i]);
			unsigned short move = ChessUtil::SimpleMove(starting, kingSquare[i], !empty);
				LegalChecker::AddMoveToList(position,result,move, true);
			//result.push_back(move);
		}
	}
	if(position.check) return result;
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
				//Move move = Move(4, 6);
				unsigned short move = ChessUtil::SimpleMove(4, 6);
				LegalChecker::AddMoveToList(position,result,move);
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
				//Move move = Move(60, 62);
				unsigned short move = ChessUtil::SimpleMove(60, 62);
				LegalChecker::AddMoveToList(position,result,move);
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
				//Move move = Move(4, 2);
				unsigned short move = ChessUtil::SimpleMove(4, 2);
				LegalChecker::AddMoveToList(position,result,move);
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
				//Move move = Move(60, 58);
				unsigned short move = ChessUtil::SimpleMove(60, 58);
				LegalChecker::AddMoveToList(position,result,move);
			}
			//std::cout << "rookExists: " << rookExists << " ,emptyPath: " <<emptyPath << " ,pathNotChecked: " << pathNotChecked << std::endl;
		}
	}
	return result;
}
//Generate moves when Checked
std::vector<unsigned short> MoveGenerator::GenerateMovesWhenChecked(Position& position){
	std::vector<unsigned short> result;
	if(position.doubleCheck){
		result = GenerateMovesByEvading(position);
	}else{
		if(ChessUtil::IsKnight(position.checkedBy[0]) || ChessUtil::IsPawn(position.checkedBy[0])){
			std::vector<unsigned short> result1 = GenerateMovesByCapturing(position);
			//std::vector<unsigned short> result2 = GenerateMovesByEvading(position);
			result.insert(result.end(), result1.begin(), result1.end());
			//result.insert(result.end(), result2.begin(), result2.end());
			//std::cout << "Check evasion move by " << ChessUtil::SquareToString(position.GetPieceLocation(position.checkedBy[0])) << ": ";
			//for(Move move : result1) std::cout << move.toString() << ", ";
			//std::cout << std::endl;
		}else{
			std::vector<unsigned short> result1 = GenerateMovesByCapturing(position);
			//std::vector<unsigned short> result2 = GenerateMovesByEvading(position);
			std::vector<unsigned short> result3 = GenerateMovesByBlocking(position);
			result.insert(result.end(), result1.begin(), result1.end());
			//result.insert(result.end(), result2.begin(), result2.end());
			result.insert(result.end(), result3.begin(), result3.end());
			//if(result1.size() == 0 && result2.size() == 0 && result3.size() != 0){
			//	std::cout << position.PositionToFen();
			//	std::cout << "Check evasion move by " << ChessUtil::SquareToString(position.GetPieceLocation(position.checkedBy[0])) << ": ";
			//	for(Move move : result) std::cout << move.toString() << ", ";
			//	std::cout << std::endl;
			//}
		}
	}
	if(result.size() == 0) {
		if(position.check){
			position.checkmate = true;
		}else{
			position.stalemate = true;
		}
	}
	return result;
}

std::vector<unsigned short> MoveGenerator::GenerateMovesByEvading(Position& position){
	short piece = position.whiteTurn ? 4 : 60;
	return GenerateKingMoves(piece, position);
}

std::vector<unsigned short> MoveGenerator::GenerateMovesByCapturing(Position& position){
	short target = position.GetPieceLocation(position.checkedBy[0]);
	//if(target == 63 && ChessUtil::IsQueen(position.checkedBy[0])){std::cout << "Generating check capturing for Qxh8" << std::endl;}
	std::vector<short> pieces = position.GetFriendlyCanReach(target, true);
	std::vector<unsigned short> result;
	for(short piece : pieces){
		if(ChessUtil::IsKing(piece) || ChessUtil::IsKnight(piece)) continue;
		if(position.pinnedPiece.find(piece) != position.pinnedPiece.end()) continue;
		unsigned short move = ChessUtil::SimpleMove(position.GetPieceLocation(piece), target, true);
		
		LegalChecker::AddMoveToList(position,result,move);
	}
	if(position.ep){
		std::vector<short> pawnSquares = ChessUtil::squareControlMap[(int)position.enPassantSquare].GetPawnSquare(!position.whiteTurn);
		for(short starting : pawnSquares){
			short piece = position.ReadPosition(starting);
			if(position.pinnedPiece.find(piece) != position.pinnedPiece.end()) continue; //Pinned pawn can never enpassant
			if(ChessUtil::IsPawn(piece) && ChessUtil::IsWhite(piece) == position.whiteTurn){
				unsigned short move = ChessUtil::SimpleMove(starting, position.enPassantSquare, true);
				
				LegalChecker::AddMoveToList(position,result,move);
			}
		}
	}
	return result;
}

std::vector<unsigned short> MoveGenerator::GenerateMovesByBlocking(Position& position){ 
	short kingSquare = position.whiteTurn ? position.whiteKingLocation : position.blackKingLocation;
	short attackerSquare = position.GetPieceLocation(position.checkedBy[0]);
	//if(attackerSquare == 63 && ChessUtil::IsQueen(position.checkedBy[0])){std::cout << "Generating check blocking for Qxh8" << std::endl;}
	std::vector<short> targetSquare;
	std::vector<unsigned short> result;
	short x0 = ChessUtil::GetFile(kingSquare);
	short y0 = ChessUtil::GetRank(kingSquare);
	short x1 = ChessUtil::GetFile(attackerSquare);
	short y1 = ChessUtil::GetRank(attackerSquare);
	short a = x0;
	short b = y0;
	//GetTargetSquares
	//if(x0 == x1 || y0 == y1) std::cout << "{ " << x0 << " , " << y0 << " } and { " << x1 << " , " << y1 << " }" << std::endl;
	while(a != x1 || b != y1){
		if(x0 != x1){
			if(x0 < x1){
				a+=1;
			}else{
				a-=1;
			}
		}
		if(y0 != y1){
			if(y0 < y1){
				b+=1;
			}else{
				b-=1;
			}
		}
		if(a == x1 && b == y1){
			break;
		}else{
			//if(attackerSquare == 63 && ChessUtil::IsQueen(position.checkedBy[0])){std::cout << "{" << a << "," << b << "}" << std::endl;}
			targetSquare.push_back(ChessUtil::GetSquareFromFileRank(a,b));
		}
	}
	//GenerateMoves
	for(short target : targetSquare){
		std::vector<short> pieces = position.GetFriendlyCanReach(target, false);
		for(short piece : pieces){
			if(ChessUtil::IsKnight(piece)) continue;
			if(position.pinnedPiece.find(piece) != position.pinnedPiece.end()) continue;
			unsigned short move = ChessUtil::SimpleMove(position.GetPieceLocation(piece), target);
			
			LegalChecker::AddMoveToList(position,result,move);
		}
	}
	//if(result.size() == 0 && targetSquare.size() != 0) {
	//if(x0 == x1 || y0 == y1) {
	//if(result.size() != 0 && targetSquare.size() != 0 && (x0 == x1 || y0 == y1) && position.fullmove == 2) {
	//	std::cout << "Blocking: " << position.PositionToFen() << " ";
	//	for(short target : targetSquare) std::cout << ChessUtil::SquareToString(target) << " King at " << ChessUtil::SquareToString(kingSquare) << " checked by " << ChessUtil::SquareToString(attackerSquare) << " || ";
	//	for(Move move : result) std::cout << move.toString() << ", ";
	//	std::cout << std::endl;
	//}
	return result;
}
//Generate moves when Pinned
std::vector<unsigned short> MoveGenerator::GenerateMovesWhenPinned(short& piece, short& direction, Position& position){
	//std::cout << "Pinned piece: " << ChessUtil::SquareToString(position.GetPieceLocation(piece)) << " Direction: " << direction << std::endl;
	char pieceType = tolower(ChessUtil::GetPieceType(piece));
	if(pieceType == 'n') return std::vector<unsigned short>();
	if(pieceType == 'b' && direction < 4) return std::vector<unsigned short>();
	if(pieceType == 'r' && direction >= 4) return std::vector<unsigned short>();
	if(pieceType == 'p'){
		return GeneratePinnedPawnMoves(piece, direction, position);
	}
	if(direction == 0 || direction == 1){
		std::vector<unsigned short> moves0 = GenerateSlidingMoves(piece, 0, position);
		std::vector<unsigned short> moves1 = GenerateSlidingMoves(piece, 1, position);
		moves0.insert(moves0.end(), moves1.begin(), moves1.end());
		return moves0;
	}else if(direction == 2 || direction == 3){
		std::vector<unsigned short> moves2 = GenerateSlidingMoves(piece, 2, position);
		std::vector<unsigned short> moves3 = GenerateSlidingMoves(piece, 3, position);
		moves2.insert(moves2.end(), moves3.begin(), moves3.end());
		return moves2;
	}else if(direction == 4 || direction == 7){
		std::vector<unsigned short> moves4 = GenerateSlidingMoves(piece, 4, position);
		std::vector<unsigned short> moves7 = GenerateSlidingMoves(piece, 7, position);
		moves4.insert(moves4.end(), moves7.begin(), moves7.end());
		return moves4;
	}else if(direction == 5 || direction == 6){
		std::vector<unsigned short> moves5 = GenerateSlidingMoves(piece, 5, position);
		std::vector<unsigned short> moves6 = GenerateSlidingMoves(piece, 6, position);
		moves5.insert(moves5.end(), moves6.begin(), moves6.end());
		return moves5;
	}
	return std::vector<unsigned short>();
}

std::vector<unsigned short> MoveGenerator::GeneratePinnedPawnMoves(short& piece, short& direction, Position& position){

	std::vector<unsigned short> result;
	std::vector<short> targets;
	bool white = ChessUtil::IsWhite(piece);
	short starting = position.GetPieceLocation(piece);
	//std::cout << "Pinned pawn " << ChessUtil::SquareToString(starting) << "," << direction << " " << std::endl;

	if(direction < 2) return result;
	
	if(direction == 2 || direction == 3){
		short pushOneTarget = white ? starting + 8 : starting - 8;
		if(!ChessUtil::IsEmpty(position.ReadPosition(pushOneTarget))) {
			return result;
		}else{
			AddPawnMoves(position, result, starting, pushOneTarget, false);
			if(ChessUtil::GetRank(starting) == 1){
				short pushTwotarget = white ? starting + 16 : starting - 16;
				if(ChessUtil::IsEmpty(position.ReadPosition(pushTwotarget))){
					AddPawnMoves(position, result, starting, pushTwotarget, false);
				}
			}
		}
	}else{
		short captureTargetSquare = starting;
		if(direction == 4 || direction == 7){
			captureTargetSquare = white ? starting + 9 : starting - 9;
		}else if(direction == 5 || direction == 6){
			captureTargetSquare = white ? starting + 7 : starting - 7;
		}
		short target = position.ReadPosition(captureTargetSquare);
		if((!ChessUtil::IsEmpty(target) && ChessUtil::IsWhite(target) != white) || captureTargetSquare == position.enPassantSquare){
			AddPawnMoves(position, result, starting, captureTargetSquare, true);
		}
	}
	return result;
}

std::vector<unsigned short> MoveGenerator::GenerateSlidingMoves(short& piece, short&& direction, Position& position)
{
	std::vector<unsigned short> result;
	short starting = position.GetPieceLocation(piece);
	std::vector<short> slidingSquare = ChessUtil::squareControlMap[starting].GetSlidingSquare(direction);
	for(int j = 0; j < slidingSquare.size(); j++){
		bool empty = position.TargetIsEmpty(slidingSquare[j]);
		bool oppositeColor = position.TargetIsOppositeColor(piece, slidingSquare[j]);
		if(!empty && !oppositeColor) break;
		if((!empty && oppositeColor) || empty){
			//Move move = Move(starting, slidingSquare[j]);
			unsigned short move = ChessUtil::SimpleMove(starting, slidingSquare[j], !empty);
			
			LegalChecker::AddMoveToList(position,result,move);
			if(!empty) break;
		}
	}
	return result;
}


//Util
bool MoveGenerator::PieceMatchTurn(short piece, Position& position)
{
	return ChessUtil::IsWhite(piece) == position.whiteTurn;
}

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

std::vector<unsigned short> (*MoveGenerator::MoveGenerationByType[6]) (short&, Position&) = {GeneratePawnMoves, GenerateSlidingMoves, GenerateKnightMoves, GenerateSlidingMoves, GenerateSlidingMoves, GenerateKingMoves};

void MoveGenerator::KingMoves(std::vector<unsigned short>& moves, Position& position){
	//King moves
	short starting = position.whiteTurn ? position.whiteKingLocation : position.blackKingLocation;
	unsigned long long friendlyBit = position.whiteTurn ? position.bitboards.allWhiteBitboard() : position.bitboards.allBlackBitboard();
	unsigned long long enemyBits = position.whiteTurn ? position.bitboards.allBlackBitboard() : position.bitboards.allWhiteBitboard();
	unsigned long long enemyControlBits = position.bitboards.controlledBits(!position.whiteTurn); 
	unsigned long long targetBits = ChessUtil::squareControlMap[starting].kingControlBitboard & ~(enemyControlBits | friendlyBit);
	//Castling moves
	char kingColor = position.whiteTurn ? 'K' : 'k';
	char queenColor = position.whiteTurn ? 'Q' : 'q';
	unsigned long long kingSideBlockingBits = BitUtil::castleBlockingBits[kingColor];
	unsigned long long queenSideBlockingBits = BitUtil::castleBlockingBits[queenColor];
	std::cout << position.PositionToString() << std::endl;
	std::cout << BitUtil::bitboardToString(enemyControlBits) << std::endl;
	if(position.GetCastlingQuota(kingColor)){
		unsigned long long blockingBit = enemyControlBits & kingSideBlockingBits;
		short target = ChessUtil::castlingTargetMapping[kingColor];
		if(blockingBit == 0ULL) {
			unsigned short&& move = ChessUtil::SimpleMove(starting, target);
			moves.push_back(move);
		}
	}
	if(position.GetCastlingQuota(queenColor)){
		unsigned long long blockingBit = enemyControlBits & queenSideBlockingBits;
		short target = ChessUtil::castlingTargetMapping[queenColor];
		if(blockingBit == 0ULL) {
			unsigned short&& move = ChessUtil::SimpleMove(starting, target);
			moves.push_back(move);
		}
	}

	std::vector<short> legalSquares = BitUtil::getBitPositions(targetBits);
	for(short target : legalSquares){
		bool capture = (enemyBits & (1ULL << target)) > 0ULL;
		unsigned short&& move = ChessUtil::SimpleMove(starting, target, capture);
		moves.push_back(move);
	}
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