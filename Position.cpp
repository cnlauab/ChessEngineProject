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
	//int rowCounter = 0;
	int spaceCounter = 0;
	for(int i = 0; i < 64; ++i){
		if(position[i] != 99){
			if(spaceCounter > 0){
				result += (48 + spaceCounter);
				spaceCounter = 0;
			}
			result += ChessUtil::pieceMapping[position[i]];
		}else{
			spaceCounter += 1;
		}
		if((i + 1) % 8 == 0){
			if(spaceCounter > 0){
				result += (48 + spaceCounter);
				spaceCounter = 0;
			}
			if(i != 63) result += '/';
		}
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

void Position::MovePiece(Move& move)
{
	//Update Perft
	ep = false;
	castle = false;
	promotion = false;
	capture = false;
	discoverCheck = false;
	check = false;
	doubleCheck = false;
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
		if(cb.size() == 1 && move.piece != cb[0]) discoverCheck = true;
		if(cb.size() > 1){
			discoverCheck = true;
			doubleCheck = true;
		}
	}
}
