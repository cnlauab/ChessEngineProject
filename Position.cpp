#include "Position.h"

Position::Position()
{
	for (int i = 0; i < 64; i++) {
		if (i < 16 || i >47) {
			position[i] = i;
		}
		else {
			position[i] = 99;
		}
	}
}

Position::Position(std::string fen)
{
	std::vector<std::string> parameters;
	std::string delimiter = " ";

	size_t pos = 0;
	std::string token;
	while ((pos = fen.find(delimiter)) != std::string::npos) {
		token = fen.substr(0, pos);
		std::cout << token << std::endl;
		parameters.emplace_back(token);
		fen.erase(0, pos + delimiter.length());
	}
	parameters.emplace_back(fen);

	Parser parser;
	parser.FenToPosition(parameters[0], position);
	for (int i = 0; i < 64; ++i) {
		int piece = position[i];
		if (piece != 99) {
			pieceLocation[piece] = i;
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
}

Position::Position(Position& currPosition, Move& move){
	whiteTurn = currPosition.whiteTurn;
	enPassantSquare = currPosition.enPassantSquare;
	halfmove = currPosition.halfmove;
	fullmove = currPosition.fullmove;
	for(int i = 0; i < 64; ++i){
		position[i] = currPosition.position[i];
	}
	pieceLocation = currPosition.pieceLocation;
	castlingQuota = currPosition.castlingQuota;

	MovePiece(move);
}

int Position::ReadPosition(int location)
{
	return position[location];
}

int Position::GetPieceLocation(int piece)
{
	return pieceLocation[piece];
}

bool Position::GetCastlingQuota(int piece, bool kingSide) 
{
	if(ChessUtil::IsWhite(piece)){
		return (kingSide) ? castlingQuota['K'] : castlingQuota['Q'];
	}else{
		return (kingSide) ? castlingQuota['k'] : castlingQuota['q'];
	}
	return false;
}

bool Position::TargetIsEmpty(int target) const
{
	return position[target] == 99;
}

bool Position::TargetIsOppositeColor(int piece, int target) const
{
	if (position[target] == 99) return false;
	return ChessUtil::IsWhite(position[target]) != ChessUtil::IsWhite(piece);
}

bool Position::EnpassantSquareIsOppositeColor(int piece) const
{
	if (enPassantSquare == 99) return false;
	bool enPassantSquareIsWhite = enPassantSquare < 32;
	return enPassantSquareIsWhite != ChessUtil::IsWhite(piece);
}

std::string Position::PositionToFen()
{
	return std::string();
}

void Position::MovePiece(Move& move)
{
	//Update Clock
	halfmove++;
	if(!whiteTurn)fullmove++;
	//Update Board
	move.takenPiece = position[move.to];
	position[move.to] = position[move.from];
	position[move.from] = 99;
	if(move.takenPiece != 99) {
		pieceLocation[move.takenPiece] = 99;
		halfmove = 0;
	}
	pieceLocation[position[move.to]] = move.to;
	//Piece Specific Update
	if (ChessUtil::IsPawn(move.piece)) {
		halfmove = 0;
		if (whiteTurn) {
			if (move.to == enPassantSquare) {
				pieceLocation[position[move.to - 8]] = 99;
				position[move.to - 8] = 99;
			}
			if (move.to - move.from == 16) {
				enPassantSquare = move.from + 8;
			}
		}
		else {
			if (move.to == enPassantSquare) {
				pieceLocation[position[move.to + 8]] = 99;
				position[move.to + 8] = 99;
			}
			if (move.to - move.from == -16) {
				enPassantSquare = move.from - 8;
			}
		}
		if(move.promotionType == 'Q'){//Promotion
			position[move.to] +=  (whiteTurn) ? -16 : 16;
		}else if(move.promotionType == 'B'){
			position[move.to] +=  (whiteTurn) ? -24 : 24;
		}else if(move.promotionType == 'R'){
			position[move.to] +=  (whiteTurn) ? -32 : 32;
		}else if(move.promotionType == 'N'){
			position[move.to] +=  (whiteTurn) ? -40 : 40;
		}
	}else{
		if(enPassantSquare != 99) enPassantSquare = 99;
	}
	if (ChessUtil::IsKing(move.piece)) {
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
			if(whiteTurn){
				position[5] = 7;
				position[7] = 99;
				pieceLocation[7] = 5;
			}else{
				position[61] = 63;
				position[63] = 99;
				pieceLocation[63] = 61;
			}
		}
		else if (move.to - move.from == -3){
			if(whiteTurn){
				position[3] = 0;
				position[0] = 99;
				pieceLocation[0] = 3;
			}else{
				position[59] = 56;
				position[56] = 99;
				pieceLocation[56] = 59;
			}
		}
	}
	if (ChessUtil::IsRook(move.piece)) {
		//Update castling quota
		if(move.piece == 0 && castlingQuota['Q']){
			castlingQuota['Q'] = false;
		}else if(move.piece == 7 && castlingQuota['K']){
			castlingQuota['K'] = true;
		}else if(move.piece == 56 && castlingQuota['q']){
			castlingQuota['q'] = true;
		}else if(move.piece == 63 && castlingQuota['k']){
			castlingQuota['k'] = true;
		}
	}
	//Update Opposite Turn
	whiteTurn = !whiteTurn;
}
