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

	//Turn
	if(parameters[1] == "w"){
		whiteTurn = true;
	}else if(parameters[1] == "b"){
		whiteTurn = false;
	}

	//Castling
	for(char c : parameters[2]){
		//std::cout<<c<<std::endl;
		castlingQuota[c] = true;
	}

	//Enpassant move
	if(parameters.size() >= 4 && parameters[3] != "-") enPassantSquare = ChessUtil::StringToSquare(parameters[3]);
	//Halfmove
	if(parameters.size() >= 5) halfmove = std::stoi(parameters[4]);
	//Fullmove
	if(parameters.size() >= 6) halfmove = std::stoi(parameters[5]);

	prevMove = Move();
}

Position::Position(Position& currPosition, Move& move){
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

	MovePiece(move);

	prevMove = move;
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
	if(ChessUtil::IsWhite(piece)){
		return (kingSide) ? castlingQuota['K'] : castlingQuota['Q'];
	}else{
		return (kingSide) ? castlingQuota['k'] : castlingQuota['q'];
	}
	return false;
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
	if(castlingQuota['K']){
		result += 'K';
		noQuota = false;
	}
	if(castlingQuota['Q']){
		result += 'Q';
		noQuota = false;
	}
	if(castlingQuota['k']){
		result += 'k';
		noQuota = false;
	}
	if(castlingQuota['q']){
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
    std::vector<short> result = GetOpponentCanReach(target, white);
    return result.size() > 0;
}

std::vector<short> Position::GetOpponentCanReach(short target, bool white){//white is defending
    std::vector<short> result;
    //Knight squares
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

    //Sliding squares
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

    //Pawn squares
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

    return result;
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

std::vector<short> Position::GetCheckedBy(bool white){
	//int king = position.whiteTurn ? 4: 60;
	//int kingsLocation = position.GetPieceLocation(king);
    short kingsLocation = white ? whiteKingLocation : blackKingLocation;
    return GetOpponentCanReach(kingsLocation, white);
}

bool Position::IsChecked(bool white){
	//int king = white ? 4: 60;
	//int kingsLocation = position.GetPieceLocation(king);
    short kingsLocation = white ? whiteKingLocation : blackKingLocation;
    return GetCheckedBy(white).size() > 0;
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

void Position::MovePiece(Move& move)
{
	move.piece = position[move.from];
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
	move.takenPiece = position[move.to];
	position[move.to] = position[move.from];
	position[move.from] = 99;
	if(move.takenPiece != 99) {
		if(whiteTurn){
			remove(blackPieceOnBoard.begin(),blackPieceOnBoard.end(),move.takenPiece);
			blackPieceOnBoard.pop_back();
		}else{
			remove(whitePieceOnBoard.begin(),whitePieceOnBoard.end(),move.takenPiece);
			whitePieceOnBoard.pop_back();
		}
		halfmove = 0;
		capture = true;
	}
	//Piece Specific Update
	if (ChessUtil::IsPawn(move.piece)) {
		//std::cout << "Is Pawn " << move.piece << std::endl;
		halfmove = 0;
		if (whiteTurn) {
			if (move.to == enPassantSquare) {
				move.takenPiece = position[move.to - 8];
				remove(blackPieceOnBoard.begin(),blackPieceOnBoard.end(),position[move.to - 8]);
				blackPieceOnBoard.pop_back();
				position[move.to - 8] = 99;
				ep = true;
				capture = true;
			}
			enPassantSquare = 99;
			if (move.to - move.from == 16) {
				enPassantSquare = move.from + 8;
			}
		}
		else {
			if (move.to == enPassantSquare) {
				move.takenPiece = position[move.to + 8];
				remove(whitePieceOnBoard.begin(),whitePieceOnBoard.end(),position[move.to + 8]);
				whitePieceOnBoard.pop_back();
				position[move.to + 8] = 99;
				ep = true;
				capture = true;
			}
			enPassantSquare = 99;
			if (move.to - move.from == -16) {
				enPassantSquare = move.from - 8;
			}
		}
		//std::cout << "Pawn " << position[move.to] << " promote to ";
		if(move.promotionType != ' '){
			promotion = true;
			if(whiteTurn){
				remove(whitePieceOnBoard.begin(),whitePieceOnBoard.end(),position[move.to]);
				whitePieceOnBoard.pop_back();
			}else{
				remove(blackPieceOnBoard.begin(),blackPieceOnBoard.end(),position[move.to]);
				blackPieceOnBoard.pop_back();
			}
			if(move.promotionType == 'Q'){//Promotion
				position[move.to] +=  (whiteTurn) ? -16 : 16;
				if(whiteTurn){
					whitePieceOnBoard.push_back(position[move.to]);
				}else{
					blackPieceOnBoard.push_back(position[move.to]);
				}
			}else if(move.promotionType == 'B'){
				position[move.to] +=  (whiteTurn) ? -24 : 24;
				if(whiteTurn){
					whitePieceOnBoard.push_back(position[move.to]);
				}else{
					blackPieceOnBoard.push_back(position[move.to]);
				}
			}else if(move.promotionType == 'R'){
				position[move.to] +=  (whiteTurn) ? -32 : 32;
				if(whiteTurn){
					whitePieceOnBoard.push_back(position[move.to]);
				}else{
					blackPieceOnBoard.push_back(position[move.to]);
				}
			}else if(move.promotionType == 'N'){
				position[move.to] +=  (whiteTurn) ? -40 : 40;
				if(whiteTurn){
					whitePieceOnBoard.push_back(position[move.to]);
				}else{
					blackPieceOnBoard.push_back(position[move.to]);
				}
			}
			if(enPassantSquare != 99) enPassantSquare = 99;
		}
		//std::cout << position[move.to] << std::endl;
	}else{
		if(enPassantSquare != 99) enPassantSquare = 99;
	}
	if (ChessUtil::IsKing(move.piece)) {
		//Update King loaction
		if(whiteTurn){
			whiteKingLocation = move.to;
		}else{
			blackKingLocation = move.to;
		}
		//Update castling quota
		if (whiteTurn && castlingQuota['K']) {
			castlingQuota['K'] = false;
		}
		else if(!whiteTurn && castlingQuota['k']) {
			castlingQuota['k'] = false;
		}
		if (whiteTurn && castlingQuota['Q']) {
			castlingQuota['Q'] = false;
		}
		else if(!whiteTurn && castlingQuota['q']) {
			castlingQuota['q'] = false;
		}
		//Move rook if castling
		if (move.to - move.from == 2) {
			castle = true;
			if(whiteTurn){
				position[5] = 7;
				position[7] = 99;
			}else{
				position[61] = 63;
				position[63] = 99;
			}
		}
		else if (move.to - move.from == -2){
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
	if (ChessUtil::IsRook(move.piece)) {
		//Update castling quota
		if(move.piece == 0 && castlingQuota['Q']){
			castlingQuota['Q'] = false;
		}else if(move.piece == 7 && castlingQuota['K']){
			castlingQuota['K'] = false;
		}else if(move.piece == 56 && castlingQuota['q']){
			castlingQuota['q'] = false;
		}else if(move.piece == 63 && castlingQuota['k']){
			castlingQuota['k'] = false;
		}
	}
	//Update Opposite Turn
	whiteTurn = !whiteTurn;
	prevMove = move;
	//Update Checked
	std::vector<short> cb = GetCheckedBy(whiteTurn);
	for(int i = 0; i < 2; i++){
		if(cb.size()< i+1) {
			checkedBy[i] = 99;
		}else{
			checkedBy[i] = cb[i];
		}
	}
	if(cb.size() > 0) {
		check = true;
		if(cb.size() == 1 && move.piece != cb[0] && !promotion) {
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
	//Castle
	/*
	if(castlingQuota['k']){
		blackScore += 30;
	}
	if(castlingQuota['q']){
		blackScore += 30;
	}
	if(castlingQuota['Q']){
		whiteScore += 30;
	}
	if(castlingQuota['K']){
		whiteScore += 30;
	}
	*/
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