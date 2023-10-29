#include "Position.h"

Position::Position()
{
	Position("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 0");
}

Position::Position(std::string fen)
{
	std::cout << "Position created." << std::endl;
	std::vector<std::string> parameters;
	std::string delimiter = " ";

	size_t pos = 0;
	std::string token;
	while ((pos = fen.find(delimiter)) != std::string::npos) {
		token = fen.substr(0, pos);
		//std::cout << token << std::endl;
		parameters.emplace_back(token);
		fen.erase(0, pos + delimiter.length());
	}
	parameters.emplace_back(fen);

	Parser parser;
	parser.FenToPosition(parameters[0], position);
	for (int i = 0; i < 64; ++i) {
		int piece = position[i];
		if (piece != 99) {
			if(ChessUtil::IsWhite(piece)){
				whitePieceOnBoard.push_back(piece);
				if(piece == 4) whiteKingLocation = i;
			}else{
				blackPieceOnBoard.push_back(piece);
				if(piece == 60) blackKingLocation = i;
			}
		}
	}

	//Bitboards
	bitboards = Bitboards(parameters[0]);

	//Turn
	if(parameters[1] == "w"){
		whiteTurn = true;
	}else if(parameters[1] == "b"){
		whiteTurn = false;
	}

	//Castling
	for(char c : parameters[2]){
		//std::cout<<c<<std::endl;
		//castlingQuota[c] = true;
		SetCastlingQuota(c, true);
	}

	//Enpassant move
	if(parameters.size() >= 4 && parameters[3] != "-") enPassantSquare = ChessUtil::StringToSquare(parameters[3]);
	//Halfmove
	if(parameters.size() >= 5) halfmove = std::stoi(parameters[4]);
	//Fullmove
	if(parameters.size() >= 6) halfmove = std::stoi(parameters[5]);

	prevMove = 0;
}

Position::Position(Position& currPosition, unsigned short& move){
	whiteTurn = currPosition.whiteTurn;
	enPassantSquare = currPosition.enPassantSquare;
	halfmove = currPosition.halfmove;
	fullmove = currPosition.fullmove;
	for(int i = 0; i < 64; ++i){
		position[i] = currPosition.position[i];
	}
	castlingQuota = currPosition.castlingQuota;
	whitePieceOnBoard = currPosition.whitePieceOnBoard;
	blackPieceOnBoard = currPosition.blackPieceOnBoard;
	whiteKingLocation = currPosition.whiteKingLocation;
	blackKingLocation = currPosition.blackKingLocation;

	bitboards = Bitboards(currPosition.bitboards);

	MovePiece(move);

	prevMove = move;
}

Position::Position(Position& position, std::vector<unsigned short>& moveList){
	whiteTurn = position.whiteTurn;
	enPassantSquare = position.enPassantSquare;
	halfmove = position.halfmove;
	fullmove = position.fullmove;
	for(int i = 0; i < 64; ++i){
		Position::position[i] = position.position[i];
	}
	castlingQuota = position.castlingQuota;
	whitePieceOnBoard = position.whitePieceOnBoard;
	blackPieceOnBoard = position.blackPieceOnBoard;
	whiteKingLocation = position.whiteKingLocation;
	blackKingLocation = position.blackKingLocation;

	bitboards = Bitboards(position.bitboards);

	for(auto move : moveList){
		MovePiece(move);
		prevMove = move;
	}
}

short Position::ReadPosition(short location)
{
	return position[location];
}

short Position::GetPieceLocation(short piece)
{
	int n = sizeof(position)/sizeof(position[0]);
 
    auto itr = std::find(position, position + n, piece);
 
    if (itr != std::end(position))
    {
		int index = std::distance(position, itr);
        //cout << "Element " << piece << " is present at index " << index << " in the given array";
		return index;
    }
    else {
    	return 99;
    }
}

bool Position::GetCastlingQuota(short piece, bool kingSide) 
{
	int k = 0;
	if(ChessUtil::IsWhite(piece)){
		if(kingSide){
			k = 0;
		}else{
			k = 1;
		}
		//return (kingSide) ? castlingQuota['K'] : castlingQuota['Q'];
	}else{
		if(kingSide){
			k = 2;
		}else{
			k = 3;
		}
		//return (kingSide) ? castlingQuota['k'] : castlingQuota['q'];
	}
	//return false;
	return (castlingQuota & (1 << k)) > 0;
}

bool Position::GetCastlingQuota(char type) 
{
	int k = 0;
	switch(type){
		case 'K':
			k = 0;
			break;
		case 'Q':
			k = 1;
			break;
		case 'k':
			k = 2;
			break;
		case 'q':
			k = 3;
			break;
	}
	return (castlingQuota & (1 << k)) > 0;
}

bool Position::TargetIsEmpty(short target) const
{
	return position[target] == 99;
}

bool Position::TargetIsOppositeColor(short piece, short target) const
{
	if (position[target] == 99) return false;
	return ChessUtil::IsWhite(position[target]) != ChessUtil::IsWhite(piece);
}

bool Position::EnpassantSquareIsOppositeColor(short piece) const
{
	if (enPassantSquare == 99) return false;
	bool enPassantSquareIsWhite = enPassantSquare < 32;
	return enPassantSquareIsWhite != ChessUtil::IsWhite(piece);
}

std::string Position::PositionToFen()
{
	std::string result = "";
	std::string temp = "";
	std::vector<std::string> ranks;
	//int rowCounter = 0;
	int spaceCounter = 0;
	for(int i = 0; i < 64; ++i){
		if(position[i] != 99){
			if(spaceCounter > 0){
				temp += (48 + spaceCounter);
				spaceCounter = 0;
			}
			temp += ChessUtil::pieceMapping[position[i]];
		}else{
			spaceCounter += 1;
		}
		if((i + 1) % 8 == 0){
			if(spaceCounter > 0){
				temp += (48 + spaceCounter);
				spaceCounter = 0;
			}
			//if(i != 63) result += '/';
			ranks.push_back(temp);
			temp = "";
		}
	}
	for(int i = ranks.size() - 1; i >= 0; i--){
		result += ranks[i];
		if(i!=0)result += '/';
	}
	result += ' ';
	//Turn
	if(whiteTurn){
		result += 'w';
	}else{
		result += 'b';
	}
	result += ' ';
	//Castling
	bool noQuota = true;
	if(GetCastlingQuota('K')){
		result += 'K';
		noQuota = false;
	}
	if(GetCastlingQuota('Q')){
		result += 'Q';
		noQuota = false;
	}
	if(GetCastlingQuota('k')){
		result += 'k';
		noQuota = false;
	}
	if(GetCastlingQuota('q')){
		result += 'q';
		noQuota = false;
	}
	if (noQuota){
		result += '-';
	}
	result += ' ';
	//En Passant
	if(enPassantSquare != 99){
		result += ChessUtil::SquareToString(enPassantSquare);
	}else{
		result += '-';
	}
	result += ' ';
	//Halfmove fullmove
	result += std::to_string(halfmove);
	result += ' ';
	result += std::to_string(fullmove);
	return result;
}

bool Position::OpponentCanReach(short target, bool white){//white is defending
    //std::vector<short> result = GetOpponentCanReach(target, white);
    //return result.size() > 0;

    unsigned long long targetBit = 1ULL << target;
	unsigned long long knightBits = white ? bitboards.blackBitboards[2] : bitboards.whiteBitboards[2];
	if((targetBit & BitUtil::knightControlBits(knightBits)) > 0ULL) return true;
	unsigned long long pawnBits = white ? bitboards.blackBitboards[0] : bitboards.whiteBitboards[0];
	if((targetBit & BitUtil::pawnControlBits(pawnBits, !white)) > 0ULL) return true;

	unsigned long long queenBits = white ? bitboards.blackBitboards[1] : bitboards.whiteBitboards[1];
	unsigned long long bishopBits = white ? bitboards.blackBitboards[3] : bitboards.whiteBitboards[3];
	unsigned long long targetDiagonalBit = ChessUtil::squareControlMap[target].bishopControlBitboard;
	if((targetDiagonalBit & (queenBits | bishopBits)) > 0ULL){
		for(int i = 4; i <= 7; ++i){
			std::vector<short> slidingSquare = ChessUtil::squareControlMap[target].GetSlidingSquare(i);
			for(short square : slidingSquare){
				short piece = ReadPosition(square);
				if(!ChessUtil::IsEmpty(piece)) {
					if((ChessUtil::IsWhite(piece) != white) && (ChessUtil::IsQueen(piece) || ChessUtil::IsBishop(piece))){
						return true;
					}else{
						break;
					}
				}
			}
		}
	}
	unsigned long long rookBits = white ? bitboards.blackBitboards[4] : bitboards.whiteBitboards[4];
	unsigned long long targetNonDiagonalBit = ChessUtil::squareControlMap[target].rookControlBitboard;
	if((targetNonDiagonalBit & (queenBits | rookBits)) > 0ULL){
		for(int i = 0; i <= 3; ++i){
			std::vector<short> slidingSquare = ChessUtil::squareControlMap[target].GetSlidingSquare(i);
			for(short square : slidingSquare){
				short piece = ReadPosition(square);
				if(!ChessUtil::IsEmpty(piece)) {
					if((ChessUtil::IsWhite(piece) != white) && (ChessUtil::IsQueen(piece) || ChessUtil::IsRook(piece))){
						return true;
					}else{
						break;
					}
				}
			}
		}
	}
	return false;
}

std::vector<short> Position::GetFriendlyCanReach(short target, bool attacking){
	std::vector<short> result;
    //Knight squares
    std::vector<short> knightSquare = ChessUtil::squareControlMap[target].GetKnightSquare();
    for(int i = 0; i < knightSquare.size(); i++){
        short piece = ReadPosition(knightSquare[i]);
        bool friendlyColor = whiteTurn == ChessUtil::IsWhite(piece);
        bool isKnight = ChessUtil::IsKnight(piece);
        if(isKnight && friendlyColor){
            //std::cout << "Knight Check " << targets[i] << std::endl;
            result.push_back(piece);
        }
    }

    //Sliding squares
    for(int i = 0; i < 8; ++i){
        std::vector<short> slidingSquare = ChessUtil::squareControlMap[target].GetSlidingSquare(i);
        if(slidingSquare.size() == 0) continue;
        if(!TargetIsEmpty(slidingSquare[0]) && ChessUtil::IsKing(ReadPosition(slidingSquare[0])) && whiteTurn == ChessUtil::IsWhite(ReadPosition(slidingSquare[0]))) {
            //std::cout << "King at " << target << " King Check " << square << std::endl;
            result.push_back(ReadPosition(slidingSquare[0]));
        }
        for(int j = 0; j < slidingSquare.size(); j++){
            short piece = ReadPosition(slidingSquare[j]);
            bool occupied = !TargetIsEmpty(slidingSquare[j]);
            bool friendlyColor = whiteTurn == ChessUtil::IsWhite(piece);
            if(occupied && !friendlyColor) break;
            if(occupied && friendlyColor){
                if(i>=0 && i<=3){
                    if((ChessUtil::IsRook(piece) || ChessUtil::IsQueen(piece))) {
                        //std::cout << "Rook or Queen Check " << square << std::endl;
                        result.push_back(piece);
                    }
                    break;
                }else{
                    if((ChessUtil::IsBishop(piece) || ChessUtil::IsQueen(piece))) {
                        //std::cout << "Bishop or Queen Check " << square << std::endl;
                        result.push_back(piece);
                    }
                    break;
                }
            }
        }
    }

    //Pawn squares
	if(!attacking){
		if(whiteTurn){
			if(target > 23 && target < 36) {
				short piece = ReadPosition(target - 16);
				bool friendlyColor = whiteTurn == ChessUtil::IsWhite(piece);
				bool isPawn = ChessUtil::IsPawn(piece);
				bool pathEmpty = TargetIsEmpty(target - 8);
				if(friendlyColor && isPawn && pathEmpty){
					result.push_back(piece);
				}
			}
			if(target > 15){
				short piece = ReadPosition(target - 8);
				bool friendlyColor = whiteTurn == ChessUtil::IsWhite(piece);
				bool isPawn = ChessUtil::IsPawn(piece);
				if(friendlyColor && isPawn){
					result.push_back(piece);
				}
			}
		}else{
			if(target > 31 && target < 40) {
				short piece = ReadPosition(target + 16);
				bool friendlyColor = whiteTurn == ChessUtil::IsWhite(piece);
				bool isPawn = ChessUtil::IsPawn(piece);
				bool pathEmpty = TargetIsEmpty(target + 8);
				if(friendlyColor && isPawn && pathEmpty){
					result.push_back(piece);
				}
			}
			if(target < 48){
				short piece = ReadPosition(target + 8);
				bool friendlyColor = whiteTurn == ChessUtil::IsWhite(piece);
				bool isPawn = ChessUtil::IsPawn(piece);
				if(friendlyColor && isPawn){
					result.push_back(piece);
				}
			}
		}
	}else{
    	std::vector<short> pawnSquare = ChessUtil::squareControlMap[target].GetPawnSquare(!whiteTurn);
    	for(int i = 0; i < pawnSquare.size(); i++){
    	    short piece = ReadPosition(pawnSquare[i]);
    	    bool friendlyColor = whiteTurn == ChessUtil::IsWhite(piece);
    	    bool isPawn = ChessUtil::IsPawn(piece);
    	    if(friendlyColor && isPawn){
    	        //std::cout << "Pawn Check " << square1 << std::endl;
    	        result.push_back(piece);
    	    }
    	}
	}

    return result;
	//return GetOpponentCanReach(target, !whiteTurn);
}

std::vector<short> Position::GetCheckedByAndUpdatePin(bool white){
    short target = white ? whiteKingLocation : blackKingLocation;
	std::vector<short> result;
	unsigned long long targetBit = 1ULL << target;

	//Clear pinned piece map
	pinnedPiece.clear();

    //Knight squares
	unsigned long long knightBits = white ? bitboards.blackBitboards[2] : bitboards.whiteBitboards[2];
	if((targetBit & BitUtil::knightControlBits(knightBits)) > 0ULL){
		std::vector<short> knightSquare = ChessUtil::squareControlMap[target].GetKnightSquare();
		for(int i = 0; i < knightSquare.size(); i++){
			short piece = ReadPosition(knightSquare[i]);
			bool oppositeColor = white != ChessUtil::IsWhite(piece);
			bool isKnight = ChessUtil::IsKnight(piece);
			if(isKnight && oppositeColor){
				//std::cout << "Knight Check " << targets[i] << std::endl;
				result.push_back(piece);
			}
		}
	}

    //Pawn squares
	unsigned long long pawnBits = white ? bitboards.blackBitboards[0] : bitboards.whiteBitboards[0];
	if((targetBit & BitUtil::pawnControlBits(pawnBits, !white)) > 0ULL){
		std::vector<short> pawnSquare = ChessUtil::squareControlMap[target].GetPawnSquare(white);
		for(int i = 0; i < pawnSquare.size(); i++){
			short piece = ReadPosition(pawnSquare[i]);
			bool oppositeColor = white != ChessUtil::IsWhite(piece);
			bool isPawn = ChessUtil::IsPawn(piece);
			if(oppositeColor && isPawn){
				//std::cout << "Pawn Check " << square1 << std::endl;
				result.push_back(piece);
			}
		}
	}

    //Sliding squares
	unsigned long long queenBits = white ? bitboards.blackBitboards[1] : bitboards.whiteBitboards[1];
	unsigned long long bishopBits = white ? bitboards.blackBitboards[3] : bitboards.whiteBitboards[3];
	unsigned long long targetDiagonalBit = ChessUtil::squareControlMap[target].bishopControlBitboard;
	if((targetDiagonalBit & (queenBits | bishopBits)) > 0ULL){
		for(int i = 4; i <= 7; ++i){
			std::vector<short> slidingSquare = ChessUtil::squareControlMap[target].GetSlidingSquare(i);
			short pin = 99;
			for(int j = 0; j < slidingSquare.size(); j++){
				short piece = ReadPosition(slidingSquare[j]);
				if(!ChessUtil::IsEmpty(piece)) {
					if((ChessUtil::IsWhite(piece) != white) && (ChessUtil::IsQueen(piece) || ChessUtil::IsBishop(piece))){
						if(pin == 99){
							result.push_back(piece);
						}
						break;
					}else if(ChessUtil::IsWhite(piece) == white){
						if(pin == 99){
							pin = piece;
						}else{
							pin = 99;
							break;
						}
					}else{
						pin = 99;
						break;
					}
				}
				if(j == slidingSquare.size()-1) pin = 99;
			}
			if(pin != 99) pinnedPiece.insert({pin, (short)i});
		}
	}
	unsigned long long rookBits = white ? bitboards.blackBitboards[4] : bitboards.whiteBitboards[4];
	unsigned long long targetNonDiagonalBit = ChessUtil::squareControlMap[target].rookControlBitboard;
	if((targetNonDiagonalBit & (queenBits | rookBits)) > 0ULL){
		for(int i = 0; i <= 3; ++i){
			std::vector<short> slidingSquare = ChessUtil::squareControlMap[target].GetSlidingSquare(i);
			short pin = 99;
			for(int j = 0; j < slidingSquare.size(); j++){
				short piece = ReadPosition(slidingSquare[j]);
				if(!ChessUtil::IsEmpty(piece)) {
					if((ChessUtil::IsWhite(piece) != white) && (ChessUtil::IsQueen(piece) || ChessUtil::IsRook(piece))){
						if(pin == 99){
							result.push_back(piece);
						}
						break;
					}else if(ChessUtil::IsWhite(piece) == white){
						if(pin == 99){
							pin = piece;
						}else{
							pin = 99;
							break;
						}
					}else{
						pin = 99;
						break;
					}
				}
				if(j == slidingSquare.size()-1) pin = 99;
			}
			if(pin != 99) pinnedPiece.insert({pin, (short)i});
		}
	}
	/*
    for(int i = 0; i < 8; ++i){
        std::vector<short> slidingSquare = ChessUtil::squareControlMap[target].GetSlidingSquare(i);
        if(slidingSquare.size() == 0) continue;
        if(!TargetIsEmpty(slidingSquare[0]) && ChessUtil::IsKing(ReadPosition(slidingSquare[0])) && white != ChessUtil::IsWhite(ReadPosition(slidingSquare[0]))) {
            //std::cout << "King at " << target << " King Check " << square << std::endl;
            result.push_back(ReadPosition(slidingSquare[0]));
        }
        for(int j = 0; j < slidingSquare.size(); j++){
            short piece = ReadPosition(slidingSquare[j]);
            bool occupied = !TargetIsEmpty(slidingSquare[j]);
            bool oppositeColor = white != ChessUtil::IsWhite(piece);
            if(occupied && !oppositeColor) break;
            if(occupied && oppositeColor){
                if(i>=0 && i<=3){
                    if((ChessUtil::IsRook(piece) || ChessUtil::IsQueen(piece))) {
                        //std::cout << "Rook or Queen Check " << square << std::endl;
                        result.push_back(piece);
                    }
                    break;
                }else{
                    if((ChessUtil::IsBishop(piece) || ChessUtil::IsQueen(piece))) {
                        //std::cout << "Bishop or Queen Check " << square << std::endl;
                        result.push_back(piece);
                    }
                    break;
                }
            }
        }
    }
	*/
    return result;
}

bool Position::IsChecked(bool white){
    //return GetCheckedBy(white).size() > 0;
    short kingsLocation = white ? whiteKingLocation : blackKingLocation;
	return OpponentCanReach(kingsLocation, white);
}

bool Position::IsEndgame(){
	short score = 0;
	for(short piece : whitePieceOnBoard){
		score+=ChessUtil::pieceScoreMapping[piece];
	}
	for(short piece : blackPieceOnBoard){
		score+=ChessUtil::pieceScoreMapping[piece];
	}
	return score < 250;
}

bool Position::IsDraw(){
	return halfmove == 100 || stalemate || !SufficientMaterial();
}

bool Position::SufficientMaterial(){
	bool hasLightBishop = false;
	bool hasDarkBishop = false;
	bool hasKnight = false;
	for(short piece : whitePieceOnBoard){
		if(ChessUtil::IsPawn(piece) || ChessUtil::IsRook(piece) || ChessUtil::IsQueen(piece)) return true;
		if(ChessUtil::IsKnight(piece)){
			if(hasKnight || hasDarkBishop || hasLightBishop) return true;
			hasKnight = true;
		}
		if(ChessUtil::IsBishop(piece)){
			if(hasKnight) return true;
			if(ChessUtil::IsLightSquare(GetPieceLocation(piece))) {
				hasLightBishop = true;
			}else{
				hasDarkBishop = true;
			}
			if(hasLightBishop && hasDarkBishop) return true;
		}
	}
	hasLightBishop = false;
	hasDarkBishop = false;
	hasKnight = false;
	for(short piece : blackPieceOnBoard){
		if(ChessUtil::IsPawn(piece) || ChessUtil::IsRook(piece) || ChessUtil::IsQueen(piece)) return true;
		if(ChessUtil::IsKnight(piece)){
			if(hasKnight || hasDarkBishop || hasLightBishop) return true;
			hasKnight = true;
		}
		if(ChessUtil::IsBishop(piece)){
			if(hasKnight) return true;
			if(ChessUtil::IsLightSquare(GetPieceLocation(piece))) {
				hasLightBishop = true;
			}else{
				hasDarkBishop = true;
			}
			if(hasLightBishop && hasDarkBishop) return true;
		}
	}
	return false;
}

std::string Position::MoveToUCIString(unsigned short move){
	short to = ChessUtil::GetTo(move);
	short from = ChessUtil::GetFrom(move);
	short piece = position[from];
	if(ChessUtil::IsPawn(piece) && (ChessUtil::GetRank(to) == 0 || ChessUtil::GetRank(to) == 7)){
		return ChessUtil::SquareToString(from) + ChessUtil::SquareToString(to) + (char)tolower(ChessUtil::GetPromotionType(move));
	}else{
		return ChessUtil::SquareToString(from) + ChessUtil::SquareToString(to);
	}
}

void Position::SetCastlingQuota(char type, bool on){
	int k = 0;
	switch(type){
		case 'K':
			k = 0;
			break;
		case 'Q':
			k = 1;
			break;
		case 'k':
			k = 2;
			break;
		case 'q':
			k = 3;
			break;
	}
	if(on){
		castlingQuota |= (1 << k);
	}else{
		castlingQuota &= ~(1 << k);
	}
}

void Position::MovePiece(unsigned short& move)
{
	//short takenPiece = position[move.to];
	//short movingPiece = position[move.from];
	//char promotionType = move.promotionType;

	short to = ChessUtil::GetTo(move);
	short from = ChessUtil::GetFrom(move);
	char promotionType = ChessUtil::GetPromotionType(move);
	short takenPiece = position[to];
	short movingPiece = position[from];
	//Update Perft
	ep = false;
	castle = false;
	promotion = false;
	capture = false;
	discoverCheck = false;
	check = false;
	doubleCheck = false;
	checkmate = false;
	stalemate = false;
	//Update Clock
	halfmove++;
	if(!whiteTurn)fullmove++;
	//Update Board
	position[to] = position[from];
	position[from] = 99;
	if(takenPiece != 99) {
		if(whiteTurn){
			remove(blackPieceOnBoard.begin(),blackPieceOnBoard.end(),takenPiece);
			blackPieceOnBoard.pop_back();
		}else{
			remove(whitePieceOnBoard.begin(),whitePieceOnBoard.end(),takenPiece);
			whitePieceOnBoard.pop_back();
		}
		halfmove = 0;
		capture = true;
	}
	//Update Bitboard
	bitboards.MoveBit(from, to, whiteTurn);
	//Piece Specific Update
	if (ChessUtil::IsPawn(movingPiece)) {
		halfmove = 0;
		if(to == enPassantSquare){
			bitboards.EnpassantMoveBit(to, whiteTurn);
		}
		if (whiteTurn) {
			if (to == enPassantSquare) {
				remove(blackPieceOnBoard.begin(),blackPieceOnBoard.end(),position[to - 8]);
				blackPieceOnBoard.pop_back();
				position[to - 8] = 99;
				ep = true;
				capture = true;
			}
			enPassantSquare = 99;
			if (to - from == 16) {
				enPassantSquare = from + 8;
			}
		}
		else {
			if (to == enPassantSquare) {
				remove(whitePieceOnBoard.begin(),whitePieceOnBoard.end(),position[to + 8]);
				whitePieceOnBoard.pop_back();
				position[to + 8] = 99;
				ep = true;
				capture = true;
			}
			enPassantSquare = 99;
			if (to - from == -16) {
				enPassantSquare = from - 8;
			}
		}
		//std::cout << "Pawn " << position[move.to] << " promote to ";
		if(ChessUtil::GetRank(to) == 0 || ChessUtil::GetRank(to) == 7){
			promotion = true;
			bitboards.PromotionMoveBit(to, BitUtil::pieceBitboardIndexMapping[tolower(promotionType)], whiteTurn);
			if(whiteTurn){
				remove(whitePieceOnBoard.begin(),whitePieceOnBoard.end(),position[to]);
				whitePieceOnBoard.pop_back();
			}else{
				remove(blackPieceOnBoard.begin(),blackPieceOnBoard.end(),position[to]);
				blackPieceOnBoard.pop_back();
			}
			if(promotionType == 'Q'){//Promotion
				position[to] +=  (whiteTurn) ? -16 : 16;
				if(whiteTurn){
					whitePieceOnBoard.push_back(position[to]);
				}else{
					blackPieceOnBoard.push_back(position[to]);
				}
			}else if(promotionType == 'B'){
				position[to] +=  (whiteTurn) ? -24 : 24;
				if(whiteTurn){
					whitePieceOnBoard.push_back(position[to]);
				}else{
					blackPieceOnBoard.push_back(position[to]);
				}
			}else if(promotionType == 'R'){
				position[to] +=  (whiteTurn) ? -32 : 32;
				if(whiteTurn){
					whitePieceOnBoard.push_back(position[to]);
				}else{
					blackPieceOnBoard.push_back(position[to]);
				}
			}else if(promotionType == 'N'){
				position[to] +=  (whiteTurn) ? -40 : 40;
				if(whiteTurn){
					whitePieceOnBoard.push_back(position[to]);
				}else{
					blackPieceOnBoard.push_back(position[to]);
				}
			}
			if(enPassantSquare != 99) enPassantSquare = 99;
		}
		//std::cout << position[move.to] << std::endl;
	}else{
		if(enPassantSquare != 99) enPassantSquare = 99;
	}
	if (ChessUtil::IsKing(movingPiece)) {
		//Update King loaction
		if(whiteTurn){
			whiteKingLocation = to;
		}else{
			blackKingLocation = to;
		}
		//Update castling quota
		if (whiteTurn && GetCastlingQuota('K')) {
			SetCastlingQuota('K', false);
			//castlingQuota['K'] = false;
		}
		else if(!whiteTurn && GetCastlingQuota('k')) {
			SetCastlingQuota('k', false);
			//castlingQuota['k'] = false;
		}
		if (whiteTurn && GetCastlingQuota('Q')) {
			SetCastlingQuota('Q', false);
			//castlingQuota['Q'] = false;
		}
		else if(!whiteTurn && GetCastlingQuota('q')) {
			SetCastlingQuota('q', false);
			//castlingQuota['q'] = false;
		}
		//Move rook if castling
		if(to == 2 || to == 6 || to == 58 || to == 62){
			bitboards.CastlingMoveBit(to);
		}
		if (to - from == 2) {
			castle = true;
			if(whiteTurn){
				position[5] = 7;
				position[7] = 99;
			}else{
				position[61] = 63;
				position[63] = 99;
			}
		}
		else if (to - from == -2){
			castle = true;
			if(whiteTurn){
				position[3] = 0;
				position[0] = 99;
			}else{
				position[59] = 56;
				position[56] = 99;
			}
		}
	}
	if (ChessUtil::IsRook(movingPiece)) {
		//Update castling quota
		if(movingPiece == 0 && GetCastlingQuota('Q')){
			SetCastlingQuota('Q', false);
			//castlingQuota['Q'] = false;
		}else if(movingPiece == 7 && GetCastlingQuota('K')){
			SetCastlingQuota('K', false);
			//castlingQuota['K'] = false;
		}else if(movingPiece == 56 && GetCastlingQuota('q')){
			SetCastlingQuota('q', false);
			//castlingQuota['q'] = false;
		}else if(movingPiece == 63 && GetCastlingQuota('k')){
			SetCastlingQuota('k', false);
			//castlingQuota['k'] = false;
		}
	}
	//Update Opposite Turn
	whiteTurn = !whiteTurn;
	prevMove = move;
	//Update Checked
	std::vector<short> cb = GetCheckedByAndUpdatePin(whiteTurn);
	for(int i = 0; i < 2; i++){
		if(cb.size()< i+1) {
			checkedBy[i] = 99;
		}else{
			checkedBy[i] = cb[i];
		}
	}
	if(cb.size() > 0) {
		check = true;
		if(cb.size() == 1 && movingPiece != cb[0] && !promotion) {
			discoverCheck = true;
		}
		if(cb.size() > 1){
			doubleCheck = true;
		}
	}
}

short Position::CalculateScore(){
	short whiteScore = 0;
	short blackScore = 0;
	short finalScore = 0;
	//CheckMate
	if(checkmate && whiteTurn){
		return -4000;
	}else if(checkmate && !whiteTurn){
		return 4000;
	}
	//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
	for(short piece : whitePieceOnBoard){
		short square = GetPieceLocation(piece);
		//std::cout << ChessUtil::pieceMapping[piece] << ChessUtil::SquareToString(square) << std::endl;;
		if(ChessUtil::IsPawn(piece)){
			whiteScore += 3 * ChessUtil::pieceScoreMapping[piece];
			//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
			std::vector<short> controlSquare = ChessUtil::squareControlMap[(int)square].GetPawnSquare(true);
			for(short s : controlSquare){
				if(TargetIsEmpty(s)){
					whiteScore += ChessUtil::midGameScoreMap[(int)s];
					if(fullmove < 2) whiteScore += 10 * ChessUtil::midGameScoreMap[(int)s];
					//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
				}else if(!ChessUtil::IsWhite(ReadPosition(s)) && ChessUtil::IsKing(ReadPosition(s))){
					whiteScore += ChessUtil::checkScore;
					//std::cout << "King: " << ChessUtil::SquareToString(s) << " Checked by " << ReadPosition(s) << std::endl;
					//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
				}else{
					short targetPiece = ReadPosition(s);
					whiteScore += ChessUtil::pieceScoreMapping[ReadPosition(s)];
					if(ChessUtil::IsPawn(targetPiece)){
						if(ChessUtil::IsWhite(targetPiece)) whiteScore += 2*ChessUtil::pieceScoreMapping[ReadPosition(s)];
					}
					//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
				}
			}
		}else if(ChessUtil::IsBishop(piece)){
			whiteScore += 3 * ChessUtil::pieceScoreMapping[piece];
			//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
			for(int i = 4; i < 8; i++){
				std::vector<short> controlSquare = ChessUtil::squareControlMap[(int)square].GetSlidingSquare(i);
				for(short s : controlSquare){
					if(TargetIsEmpty(s)){
						whiteScore += 2 * ChessUtil::midGameScoreMap[(int)s];
						//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
					}else if(!ChessUtil::IsWhite(ReadPosition(s)) && ChessUtil::IsKing(ReadPosition(s))){
						whiteScore += ChessUtil::checkScore;
						//std::cout << "King: " << ChessUtil::SquareToString(s) << " Checked by " << ReadPosition(s) << std::endl;
						//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
						break;
					}else{
						whiteScore += 0.5*ChessUtil::pieceScoreMapping[ReadPosition(s)];
						//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
						break;
					}
				}
			}
		}else if(ChessUtil::IsKnight(piece)){
			whiteScore += 3 * ChessUtil::pieceScoreMapping[piece];
			//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
			std::vector<short> controlSquare = ChessUtil::squareControlMap[(int)square].GetKnightSquare();
			for(short s : controlSquare){
				if(TargetIsEmpty(s)){
					whiteScore += 2 * ChessUtil::midGameScoreMap[(int)s];
					//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
				}else if(!ChessUtil::IsWhite(ReadPosition(s)) && ChessUtil::IsKing(ReadPosition(s))){
					whiteScore += ChessUtil::checkScore;
					//std::cout << "King: " << ChessUtil::SquareToString(s) << " Checked by " << ReadPosition(s) << std::endl;
					//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
				}else{
					whiteScore += 0.5*ChessUtil::pieceScoreMapping[ReadPosition(s)];
					//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
				}
			}
		}else if(ChessUtil::IsRook(piece)){
			whiteScore += 3 * ChessUtil::pieceScoreMapping[piece];
			//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
			for(int i = 0; i < 4; i++){
				std::vector<short> controlSquare = ChessUtil::squareControlMap[(int)square].GetSlidingSquare(i);
				for(short s : controlSquare){
					if(TargetIsEmpty(s)){
						whiteScore += 2 * ChessUtil::midGameScoreMap[(int)s];
						//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
					}else if(!ChessUtil::IsWhite(ReadPosition(s)) && ChessUtil::IsKing(ReadPosition(s))){
						whiteScore += ChessUtil::checkScore;
						//std::cout << "King: " << ChessUtil::SquareToString(s) << " Checked by " << ReadPosition(s) << std::endl;
						//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
						break;
					}else{
						whiteScore += 0.5*ChessUtil::pieceScoreMapping[ReadPosition(s)];
						//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
						break;
					}
				}
			}
		}else if(ChessUtil::IsQueen(piece)){
			whiteScore += 3 * ChessUtil::pieceScoreMapping[piece];
			//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
			for(int i = 0; i < 8; i++){
				std::vector<short> controlSquare = ChessUtil::squareControlMap[(int)square].GetSlidingSquare(i);
				for(short s : controlSquare){
					if(TargetIsEmpty(s)){
						whiteScore += ChessUtil::midGameScoreMap[(int)s];
						//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
					}else if(!ChessUtil::IsWhite(ReadPosition(s)) && ChessUtil::IsKing(ReadPosition(s))){
						whiteScore += ChessUtil::checkScore;
						//std::cout << "King: " << ChessUtil::SquareToString(s) << " Checked by " << ReadPosition(s) << std::endl;
						//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
						break;
					}else{
						whiteScore += 0.5*ChessUtil::pieceScoreMapping[ReadPosition(s)];
						//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
						break;
					}
				}
			}
		}else if(ChessUtil::IsKing(piece)){
			whiteScore += 80;
			for(int i = 0; i < 8; i++){
				std::vector<short> controlSquare = ChessUtil::squareControlMap[(int)square].GetSlidingSquare(i);
				for(short s : controlSquare){
					if(!TargetIsEmpty(s)){
						whiteScore += 60;
						break;
						//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
					}else{
						whiteScore -= 10;
					}
				}
			}
		}
	}
	for(short piece : blackPieceOnBoard){
		short square = GetPieceLocation(piece);
		//std::cout << ChessUtil::pieceMapping[piece] << ChessUtil::SquareToString(square) << std::endl;
		if(ChessUtil::IsPawn(piece)){
			blackScore += 3 * ChessUtil::pieceScoreMapping[piece];
			//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
			std::vector<short> controlSquare = ChessUtil::squareControlMap[(int)square].GetPawnSquare(false);
			for(short s : controlSquare){
				if(TargetIsEmpty(s)){
					blackScore += ChessUtil::midGameScoreMap[(int)s];
					if(fullmove < 2) blackScore += 10 * ChessUtil::midGameScoreMap[(int)s];
					//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
				}else if(ChessUtil::IsWhite(ReadPosition(s)) && ChessUtil::IsKing(ReadPosition(s))){
					blackScore += ChessUtil::checkScore;
					//std::cout << "King: " << ChessUtil::SquareToString(s) << " Checked by " << ReadPosition(s) << std::endl;
					//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
				}else{
					short targetPiece = ReadPosition(s);
					blackScore += ChessUtil::pieceScoreMapping[ReadPosition(s)];
					if(ChessUtil::IsPawn(targetPiece)){
						if(!ChessUtil::IsWhite(targetPiece)) blackScore += 2*ChessUtil::pieceScoreMapping[ReadPosition(s)];
					}
					//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
				}
			}
		}else if(ChessUtil::IsBishop(piece)){
			blackScore += 3 * ChessUtil::pieceScoreMapping[piece];
			//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
			for(int i = 4; i < 8; i++){
				std::vector<short> controlSquare = ChessUtil::squareControlMap[(int)square].GetSlidingSquare(i);
				for(short s : controlSquare){
					if(TargetIsEmpty(s)){
						blackScore += 2 * ChessUtil::midGameScoreMap[(int)s];
						//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
					}else if(ChessUtil::IsWhite(ReadPosition(s)) && ChessUtil::IsKing(ReadPosition(s))){
						blackScore += ChessUtil::checkScore;
						//std::cout << "King: " << ChessUtil::SquareToString(s) << " Checked by " << ReadPosition(s) << std::endl;
						//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
						break;
					}else{
						blackScore += 0.5*ChessUtil::pieceScoreMapping[ReadPosition(s)];
						//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
						break;
					}
				}
			}
		}else if(ChessUtil::IsKnight(piece)){
			blackScore += 3 * ChessUtil::pieceScoreMapping[piece];
			//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
			std::vector<short> controlSquare = ChessUtil::squareControlMap[(int)square].GetKnightSquare();
			for(short s : controlSquare){
				if(TargetIsEmpty(s)){
					blackScore += 2 * ChessUtil::midGameScoreMap[(int)s];
					//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
				}else if(ChessUtil::IsWhite(ReadPosition(s)) && ChessUtil::IsKing(ReadPosition(s))){
					blackScore += ChessUtil::checkScore;
					//std::cout << "King: " << ChessUtil::SquareToString(s) << " Checked by " << ReadPosition(s) << std::endl;
					//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
					break;
				}else{
					blackScore += 0.5*ChessUtil::pieceScoreMapping[ReadPosition(s)];
					//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
					break;
				}
			}
		}else if(ChessUtil::IsRook(piece)){
			blackScore += 3 * ChessUtil::pieceScoreMapping[piece];
			//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
			for(int i = 0; i < 4; i++){
				std::vector<short> controlSquare = ChessUtil::squareControlMap[(int)square].GetSlidingSquare(i);
				for(short s : controlSquare){
					if(TargetIsEmpty(s)){
						blackScore += 2 * ChessUtil::midGameScoreMap[(int)s];
						//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
					}else if(ChessUtil::IsWhite(ReadPosition(s)) && ChessUtil::IsKing(ReadPosition(s))){
						blackScore += ChessUtil::checkScore;
						//std::cout << "King: " << ChessUtil::SquareToString(s) << " Checked by " << ReadPosition(s) << std::endl;
						//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
						break;
					}else{
						blackScore += 0.5*ChessUtil::pieceScoreMapping[ReadPosition(s)];
						//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
						break;
					}
				}
			}
		}else if(ChessUtil::IsQueen(piece)){
			blackScore += 3 * ChessUtil::pieceScoreMapping[piece];
			//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
			for(int i = 0; i < 8; i++){
				std::vector<short> controlSquare = ChessUtil::squareControlMap[(int)square].GetSlidingSquare(i);
				for(short s : controlSquare){
					if(TargetIsEmpty(s)){
						blackScore += ChessUtil::midGameScoreMap[(int)s];
						//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
					}else if(ChessUtil::IsWhite(ReadPosition(s)) && ChessUtil::IsKing(ReadPosition(s))){
						blackScore += ChessUtil::checkScore;
						//std::cout << "King: " << ChessUtil::SquareToString(s) << " Checked by " << ReadPosition(s) << std::endl;
						//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
						break;
					}else{
						blackScore += 0.5*ChessUtil::pieceScoreMapping[ReadPosition(s)];
						//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
						break;
					}
				}
			}
		}else if(ChessUtil::IsKing(piece)){
			blackScore += 80;
			for(int i = 0; i < 8; i++){
				std::vector<short> controlSquare = ChessUtil::squareControlMap[(int)square].GetSlidingSquare(i);
				for(short s : controlSquare){
					if(!TargetIsEmpty(s)){
						blackScore += 60;
						break;
						//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
					}else{
						blackScore -= 10;
					}
				}
			}
		}
	}
	finalScore = whiteScore - blackScore;
	//Draw
	if(finalScore > 100 && !whiteTurn && IsDraw()){
		finalScore = -2000;
	}else if(finalScore < 100 && whiteTurn && IsDraw()){
		finalScore = 2000;
	}
	//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
	return finalScore;
}