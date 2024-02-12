#include "Position.h"

Position::Position()
{
	//Position("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 0");
	//std::cout << "Position Default Constructor" << std::endl;
}

Position::Position(std::string fen)
{
	//std::cout << "Position created: "  << fen << std::endl;
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
		//std::cout << c << std::endl;
		SetCastlingQuota(c, true);
	}

	//Enpassant move
	if(parameters.size() >= 4 && parameters[3] != "-") enPassantSquare = ChessUtil::StringToSquare(parameters[3]);
	//Halfmove
	if(parameters.size() >= 5) halfmove = std::stoi(parameters[4]);
	//Fullmove
	if(parameters.size() >= 6) halfmove = std::stoi(parameters[5]);

	//Update Checked by
	UpdateCheck(99);
}

Position::Position(Position& currPosition, unsigned short& move){
	//std::cout << "Position created... " << currPosition.MoveToUCIString(move) << std::endl;
	whiteTurn = currPosition.whiteTurn;
	enPassantSquare = currPosition.enPassantSquare;
	halfmove = currPosition.halfmove;
	fullmove = currPosition.fullmove;
	castlingQuota = currPosition.castlingQuota;

	bitboards = Bitboards(currPosition.bitboards);

	MovePiece(move);
}

Position::Position(Position& position, std::vector<unsigned short>& moveList){
	whiteTurn = position.whiteTurn;
	enPassantSquare = position.enPassantSquare;
	halfmove = position.halfmove;
	fullmove = position.fullmove;
	castlingQuota = position.castlingQuota;

	bitboards = Bitboards(position.bitboards);

	for(auto move : moveList){
		MovePiece(move);
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
	bool result = (castlingQuota & (1 << k)) > 0;
	return result;
}

std::string Position::PositionToFen()
{
	std::string result = bitboards.ToFen();
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

std::string Position::PositionToString(){
	std::string result;
	std::string row;
	int rowCounter = 1;
	for (int i = 0; i < 64; ++i) {
		auto pieceIdx = bitboards.GetPieceTypeFromSquare(i);
        char piece = ' ';
		if(pieceIdx != -1) piece = bitboards.hasWhitePiece(i) ? toupper(BitUtil::bitboardIndexPieceMapping[pieceIdx]) : tolower(BitUtil::bitboardIndexPieceMapping[pieceIdx]);
		if (i % 8 == 7) {
			row.push_back('['); 
			row.push_back(piece);
			row.push_back(']');
			result = row + " " + std::to_string(rowCounter) + "\n" + result;
			row = "";
			rowCounter++;
		}
		else {
			row.push_back('[');
			row.push_back(piece);
			row.push_back(']');
		}
	}
	result += " a  b  c  d  e  f  g  h\n";
	return result;
}

std::string Position::PositionToFullReport(){
	std::string result = "";
	result += PositionToString();
	result += PositionToFen();
	result += " \nFEN \n";
	result += "Whiteturn: " + std::to_string(whiteTurn) + '\n';
	result += "EnPassantSquare: " + std::to_string(enPassantSquare) + '\n';
	result += "Halfmove: " + std::to_string(halfmove) + '\n';
	result += "Fullmove: " + std::to_string(fullmove) + '\n';
	result += " \nPerft \n";
	result += "CheckedAt: " + std::to_string(checkedAt[0]) + ',' + std::to_string(checkedAt[1]) + '\n';
	result += "Ep: " + std::to_string(ep) + '\n';
	result += "Castle: " + std::to_string(castle) + '\n';
	result += "Promotion: " + std::to_string(fullmove) + '\n';
	result += "Check: " + std::to_string(check) + '\n';
	result += "DoubleCheck: " + std::to_string(doubleCheck) + '\n';
	result += "DiscoverCheck: " + std::to_string(discoverCheck) + '\n';
	result += "Checkmate: " + std::to_string(checkmate) + '\n';
	result += "Stalemate: " + std::to_string(stalemate) + '\n';
	result += " \nState \n";
	result += "PrevMove: " + ChessUtil::SimpleMoveToString(stateStack.top().prevMove) + '\n'; 
	result += "TakenPieceType: " + std::to_string(stateStack.top().takenPieceType) + '\n';
	result += "EnPassantSquare: " + std::to_string(stateStack.top().enPassantSquare) + '\n';
	result += "PrevEnPassantSquare: " + std::to_string(stateStack.top().prevEnPassantSquare) + '\n';
	result += "CastlingQuota1: " + std::to_string(stateStack.top().castlingQuota1) + '\n';
	result += "CastlingQuota2: " + std::to_string(stateStack.top().castlingQuota2) + '\n';
	result += "HalfMove: " + std::to_string(stateStack.top().halfMove) + '\n';
	result += " \nBitboards \n";
	result += "PinnedBitboard: \n" + BitUtil::bitboardToString(bitboards.pinnedBitboard) + '\n';
	result += "CheckedBitboard: \n" + BitUtil::bitboardToString(bitboards.checkedBitboard) + '\n';
	result += "AllWhiteBitboard: \n" + BitUtil::bitboardToString(bitboards.allWhiteBitboard()) + '\n';
	result += "AllBlackBitboard: \n" + BitUtil::bitboardToString(bitboards.allBlackBitboard()) + '\n';
	result += "PinnedRays: \n";
	for(auto ray : bitboards.pinnedRays){
		result += std::to_string(ray.first) + '\n' + BitUtil::bitboardToString(ray.second) + '\n';
	}

	return result;
}

std::vector<short> Position::GetCheckedByAndUpdatePin(bool white){
    short target = bitboards.KingLocation(white);
	std::vector<short> result;
	unsigned long long targetBit = 1ULL << target;
	bitboards.pinnedBitboard = 0ULL;
	bitboards.checkedBitboard = 0ULL;

	//Clear pinned piece map
	//pinnedPiece.clear();
	bitboards.pinnedRays.clear();
    //Knight squares
	unsigned long long knightControl = ChessUtil::squareControlMap[target].knightControlBitboard;
	knightControl &= white ? bitboards.blackBitboards[2] : bitboards.whiteBitboards[2];
	if(knightControl > 0ULL){
		result.push_back(BitUtil::getBitPositions(knightControl)[0]);
		bitboards.checkedBitboard |= knightControl;
	}
    //Pawn squares
	unsigned long long pawnControl = white ? ChessUtil::squareControlMap[target].pawnControlUpBitboard : ChessUtil::squareControlMap[target].pawnControlDownBitboard;
	pawnControl &= white ? bitboards.blackBitboards[0] : bitboards.whiteBitboards[0];
	if(pawnControl > 0ULL){
		result.push_back(BitUtil::getBitPositions(pawnControl)[0]);
		bitboards.checkedBitboard |= pawnControl;
	}
	//New Sliding squares

	unsigned long long queenBits = white ? bitboards.blackBitboards[1] : bitboards.whiteBitboards[1];
	unsigned long long bishopBits = white ? bitboards.blackBitboards[3] : bitboards.whiteBitboards[3];
	unsigned long long rookBits = white ? bitboards.blackBitboards[4] : bitboards.whiteBitboards[4];
	unsigned long long targetDiagonalBit = ChessUtil::squareControlMap[target].bishopControlBitboard;
	unsigned long long targetNonDiagonalBit = ChessUtil::squareControlMap[target].rookControlBitboard;
	targetDiagonalBit &= (queenBits | bishopBits);
	targetNonDiagonalBit &= (queenBits | rookBits);
	for(int i = 0; i <= 7; ++i){
		std::vector<short> slidingSquare = ChessUtil::squareControlMap[target].GetSlidingSquare(i);
		bool firstPieceReached = false;
		short pinnedSquare = 99;
		unsigned long long attackingBit = i < 4 ? targetNonDiagonalBit : targetDiagonalBit;
		unsigned long long rayBits = 0ULL;
		for(int j = 0; j < slidingSquare.size(); j++){
			short square = slidingSquare[j];
			unsigned long long squareBit = 1ULL << square;
			rayBits |= squareBit;
			if(bitboards.isEmpty(square)){
				continue;
			}else{
				if(!firstPieceReached){
					firstPieceReached = true;
					if(bitboards.hasWhitePiece(square) == white){
						pinnedSquare = square;
						continue;
					}else{
						if((attackingBit & squareBit) > 0ULL){
							result.push_back(square);
							bitboards.checkedBitboard |= rayBits;
						}
						break;
					}
				}else{
					if((attackingBit & squareBit) > 0ULL){
						bitboards.pinnedBitboard |= 1ULL << pinnedSquare;
						bitboards.pinnedRays.insert({pinnedSquare, rayBits});
					}
					break;
				}
			}
		}

	}
	
	if(result.size() == 0) {
		bitboards.checkedBitboard = ~0ULL;
	}

	//std::cout << BitUtil::bitboardToString(bitboards.checkedBitboard) << std::endl;
	//std::cout << BitUtil::bitboardToString(bitboards.pinnedBitboard) << std::endl;
	//std::cout << PositionToString() << std::endl;

    return result;
}

bool Position::IsChecked(bool white){
	return bitboards.checkedAt(white).size() > 0;
}

bool Position::IsEndgame(){
	short score = 0;
	for(int i = 0; i < 5; i++){
		unsigned long long pieces = bitboards.whiteBitboards[i] | bitboards.blackBitboards[i];
		short numberOfPieces = BitUtil::getNumberOnBits(pieces);
		score += numberOfPieces * ChessUtil::pieceTypeScoreMapping[BitUtil::bitboardIndexPieceMapping[i]];
	}
	return score < 150;
}

bool Position::IsDraw(){
	return halfmove == 100 || stalemate || !SufficientMaterial();
}

bool Position::SufficientMaterial(){
	short numQPR = BitUtil::getNumberOnBits(bitboards.blackBitboards[1] | bitboards.whiteBitboards[1] | bitboards.blackBitboards[0] | bitboards.whiteBitboards[0] | bitboards.blackBitboards[4] | bitboards.whiteBitboards[4]);
	if(numQPR > 0) return true;
	short whiteNumN = BitUtil::getNumberOnBits(bitboards.whiteBitboards[2]);
	short blackNumN = BitUtil::getNumberOnBits(bitboards.blackBitboards[2]);
	if(whiteNumN > 1 || blackNumN > 1) return true;
	if(bitboards.hasBothColorBishop(true) || bitboards.hasBothColorBishop(false)) return true;
	short whiteNumB = BitUtil::getNumberOnBits(bitboards.whiteBitboards[3]);
	short blackNumB = BitUtil::getNumberOnBits(bitboards.blackBitboards[3]);
	if(whiteNumN == 1 && whiteNumB > 0) return true;
	if(blackNumN == 1 && blackNumB > 0) return true;
	return false;
}

std::string Position::MoveToUCIString(unsigned short move){
	short to = ChessUtil::GetTo(move);
	short from = ChessUtil::GetFrom(move);
	bool isPawn = ((1ULL << from) & (bitboards.whiteBitboards[0] | bitboards.blackBitboards[0])) > 0ULL;
	if(isPawn && (ChessUtil::GetRank(to) == 0 || ChessUtil::GetRank(to) == 7)){
		return ChessUtil::SquareToString(from) + ChessUtil::SquareToString(to) + (char)tolower(ChessUtil::GetPromotionType(move));
	}else{
		return ChessUtil::SquareToString(from) + ChessUtil::SquareToString(to);
	}
}

std::string Position::MoveToPNGString(unsigned short move){
    if (move == 0) return "EmptyMove";
	short from = ChessUtil::GetFrom(move);
	short to = ChessUtil::GetFrom(move);
	//short piece = ReadPosition(from);
	bool capture = ChessUtil::GetIsCapture(move);
	char promotionType = ChessUtil::GetPromotionType(move);
	bool fileAmbiguity = false;
	bool rankAmbiguity = false;

	std::string result = "";
	char type = toupper(BitUtil::bitboardIndexPieceMapping[bitboards.GetPieceTypeFromSquare(from)]);

	std::vector<short> canGetToSquares;
	unsigned long long canGetToSameSquareBits = 0ULL;
	if(type == 'N'){
		canGetToSameSquareBits = ChessUtil::squareControlMap[to].knightControlBitboard & bitboards.GetPieceBitboard(whiteTurn, 2);
	}else if(type == 'R'){
		canGetToSameSquareBits = bitboards.slidingControlBits(whiteTurn, to, 4) & bitboards.GetPieceBitboard(whiteTurn, 4);
	}else if(type == 'B'){
		canGetToSameSquareBits = bitboards.slidingControlBits(whiteTurn, to, 3) & bitboards.GetPieceBitboard(whiteTurn, 3);
	}else if(type == 'Q'){
		canGetToSameSquareBits = bitboards.slidingControlBits(whiteTurn, to, 1) & bitboards.GetPieceBitboard(whiteTurn, 1);
	}
	if(BitUtil::getNumberOnBits(canGetToSameSquareBits) > 1){
		rankAmbiguity = true;
		fileAmbiguity = true;
		if(BitUtil::AllBitsOnSameFile(canGetToSameSquareBits))fileAmbiguity = false;
		if(BitUtil::AllBitsOnSameRank(canGetToSameSquareBits))rankAmbiguity = false;
	}

	if(type == 'K' && (to - from == 2)){
		result += "O-O";
	}else if(type == 'K' && (to - from == -2)){
		result += "O-O-O";
	}else{//e.g.: Ra1xe1+
		if(type != 'P') result += type; 
		if((type == 'P' && (capture || to == enPassantSquare)) || fileAmbiguity) result += ChessUtil::GetFileChar(from);
		if(rankAmbiguity) result += ChessUtil::GetRankChar(from);
		if(capture) result += 'x';
		result += ChessUtil::SquareToString(to);
		if(type == 'P' && promotionType != ' ' && (ChessUtil::GetRank(to) == 0 || ChessUtil::GetRank(to) == 7)){
			result += '=';
			result += promotionType;
		}
	}
	if(check) {
		result += '+';
	}else if(checkmate){
		result += '#';
	}

	return result;
}

void Position::UpdateCheck(short attackingFrom){
	std::vector<short> cb = GetCheckedByAndUpdatePin(whiteTurn);
	if(cb.size() > 0) {
		check = true;
		for(int i = 0; i < 2; i++){
			if(cb.size()< i+1) {
				checkedAt[i] = 99;
			}else{
				checkedAt[i] = cb[i];
			}
		}
		if(cb.size() == 1 && attackingFrom != cb[0]) {
			discoverCheck = true;
		}else{
			discoverCheck = false;
		}

		if(cb.size() > 1){
			doubleCheck = true;
		}else{
			doubleCheck = false;
		}
	}else{
		check = false;
		discoverCheck = false;
		doubleCheck = false;
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
		case '-':
			castlingQuota = 0;
			return;
		default:
			return;
	}
	if(on){
		castlingQuota |= (1 << k);
	}else{
		castlingQuota &= ~(1 << k);
	}
	//std::cout << (int)castlingQuota << std::endl;
}

void Position::MovePiece(unsigned short& move)
{

	short to = ChessUtil::GetTo(move);
	short from = ChessUtil::GetFrom(move);
	char promotionType = ChessUtil::GetPromotionType(move);
	int pieceType = bitboards.GetPieceTypeFromSquare(from);
	int captureType = bitboards.GetPieceTypeFromSquare(to);
	PositionState state;
	//Update Perft
	ep = false;
	castle = false;
	promotion = false;
	capture = ChessUtil::GetIsCapture(move);
	discoverCheck = false;
	check = false;
	doubleCheck = false;
	checkmate = false;
	stalemate = false;
	//Update Clock
	halfmove++;
	if(!whiteTurn)fullmove++;
	//Update Board
	state.prevEnPassantSquare = enPassantSquare;
	if(capture) {
		halfmove = 0;
	}
	//Update Bitboard
	bitboards.MoveBit(from, to, whiteTurn);
	//Piece Specific Update
	if (pieceType == 0) {
		halfmove = 0;
		//En Passant Take
		if(to == enPassantSquare){
			bitboards.EnpassantMoveBit(to, whiteTurn);
			ep = true;
		}
		//Set En Passant square
		if (whiteTurn) {
			enPassantSquare = (to - from == 16) ? (from + 8) : 99;
		}else{
			enPassantSquare = (to - from == -16) ? (from - 8) : 99;
		}
		//Promotion
		if(ChessUtil::GetRank(to) == 0 || ChessUtil::GetRank(to) == 7){
			promotion = true;
			bitboards.PromotionMoveBit(to, BitUtil::pieceBitboardIndexMapping[tolower(promotionType)], whiteTurn);
		}
	}else{
		if(enPassantSquare != 99) enPassantSquare = 99;
	}
	if (pieceType == 5) {
		//Update castling quota
		if(whiteTurn){
			if (GetCastlingQuota('K')) {
				SetCastlingQuota('K', false);
				state.castlingQuota1 = 'K';
			}
			if (GetCastlingQuota('Q')) {
				SetCastlingQuota('Q', false);
				state.castlingQuota2 = 'Q';
			}
		}else{
			if(GetCastlingQuota('k')) {
				SetCastlingQuota('k', false);
				state.castlingQuota1 = 'k';
			}
			if(GetCastlingQuota('q')) {
				SetCastlingQuota('q', false);
				state.castlingQuota2 = 'q';
			}
		}
		//Move rook if castling
		if(to == 2 || to == 6 || to == 58 || to == 62){
			bitboards.CastlingMoveBit(to);
		}
		if (to - from == 2 || to - from == -2) {
			castle = true;
		}
	}
	if (pieceType == 4) {
		//Update castling quota
		if(from == 0 && GetCastlingQuota('Q')){
			SetCastlingQuota('Q', false);
			state.castlingQuota1 = 'Q';
		}else if(from == 7 && GetCastlingQuota('K')){
			SetCastlingQuota('K', false);
			state.castlingQuota1 = 'K';
		}else if(from == 56 && GetCastlingQuota('q')){
			SetCastlingQuota('q', false);
			state.castlingQuota1 = 'q';
		}else if(from == 63 && GetCastlingQuota('k')){
			SetCastlingQuota('k', false);
			state.castlingQuota1 = 'k';
		}
	}else if(captureType == 4){
		//Update castling quota
		if(to == 0 && GetCastlingQuota('Q')){
			SetCastlingQuota('Q', false);
			state.castlingQuota1 = 'Q';
		}else if(to == 7 && GetCastlingQuota('K')){
			SetCastlingQuota('K', false);
			state.castlingQuota1 = 'K';
		}else if(to == 56 && GetCastlingQuota('q')){
			SetCastlingQuota('q', false);
			state.castlingQuota1 = 'q';
		}else if(to == 63 && GetCastlingQuota('k')){
			SetCastlingQuota('k', false);
			state.castlingQuota1 = 'k';
		}
	}
	//Update Opposite Turn
	whiteTurn = !whiteTurn;
	//Push new state
	state.prevMove = move;
	state.takenPieceType = captureType;
	state.enPassantSquare = enPassantSquare;
	state.halfMove = halfmove;
	stateStack.push(std::move(state));
	//Update Checked
	UpdateCheck(to);
}

void Position::UnmovePiece(){
	if(stateStack.size() == 0) return;
	short direction = (whiteTurn) ? 1 : -1;
	PositionState prevState = stateStack.top();
	unsigned short move = prevState.prevMove;
	//Initialize Move
	short to = ChessUtil::GetTo(move);
	short from = ChessUtil::GetFrom(move);
	int pieceType = bitboards.GetPieceTypeFromSquare(to);
	int captureType = prevState.takenPieceType;

	//Initialize Capture
	capture = ChessUtil::GetIsCapture(move);
	//short takenPiece = prevState.takenPiece;
	//Initialize En Passant
	enPassantSquare = prevState.enPassantSquare;
	ep = (pieceType == 0 && to == prevState.prevEnPassantSquare);
	//Initialize Promotion
	char promotionType = ChessUtil::GetPromotionType(move);
	promotion = ChessUtil::GetIsPromotion(move);
	//Initialize Castling
	castle = (pieceType == 5 && ((to - from == 2) || (to - from == -2)));

	//Update Clock
	halfmove = prevState.halfMove;
	if(!whiteTurn)fullmove--;
	//Update Board
	whiteTurn = !whiteTurn;
	bitboards.MoveBit(to, from, whiteTurn);
	if(capture) {
		if(!ep){
			bitboards.PutBackTakenPiece(to, captureType, whiteTurn);
		}
	}


	//Piece Specific Update
	if (pieceType == 0) {
		if (ep) {
			bitboards.ReverseEnpassantMoveBit(to, whiteTurn);
		}
		if(promotion){
			bitboards.PromotionMoveBit(to, BitUtil::pieceBitboardIndexMapping[tolower(promotionType)], whiteTurn);
		}
	}
	if (pieceType == 5) {
		//Update castling quota
		if(prevState.castlingQuota1 != ' '){
			SetCastlingQuota(prevState.castlingQuota1, true);
		}
		if(prevState.castlingQuota2 != ' '){
			SetCastlingQuota(prevState.castlingQuota2, true);
		}
		//Move rook if castling
		if(castle){
			bitboards.ReverseCastlingMoveBit(to);
		}
	}
	if (pieceType == 4) {
		if(prevState.castlingQuota1 != ' '){
			SetCastlingQuota(prevState.castlingQuota1, true);
		}
	}
	//Pop prev state
	stateStack.pop();
	//Update Checked
	if(stateStack.size() > 0){
		//short prevMovingPiece = position[ChessUtil::GetTo(stateStack.top().prevMove)];
		UpdateCheck(from);
	}
}

short Position::CalculateScore(){
	//short whiteScore = 0;
	//short blackScore = 0;
	//short finalScore = 0;
	////CheckMate
	//if(checkmate && whiteTurn){
	//	return -4000;
	//}else if(checkmate && !whiteTurn){
	//	return 4000;
	//}
	////std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
	//for(short piece : whitePieceOnBoard){
	//	short square = GetPieceLocation(piece);
	//	//std::cout << ChessUtil::pieceMapping[piece] << ChessUtil::SquareToString(square) << std::endl;;
	//	if(ChessUtil::IsPawn(piece)){
	//		whiteScore += 3 * ChessUtil::pieceScoreMapping[piece];
	//		//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
	//		std::vector<short> controlSquare = ChessUtil::squareControlMap[(int)square].GetPawnSquare(true);
	//		for(short s : controlSquare){
	//			if(TargetIsEmpty(s)){
	//				whiteScore += ChessUtil::midGameScoreMap[(int)s];
	//				if(fullmove < 2) whiteScore += 10 * ChessUtil::midGameScoreMap[(int)s];
	//				//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
	//			}else if(!ChessUtil::IsWhite(ReadPosition(s)) && ChessUtil::IsKing(ReadPosition(s))){
	//				whiteScore += ChessUtil::checkScore;
	//				//std::cout << "King: " << ChessUtil::SquareToString(s) << " Checked by " << ReadPosition(s) << std::endl;
	//				//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
	//			}else{
	//				short targetPiece = ReadPosition(s);
	//				whiteScore += ChessUtil::pieceScoreMapping[ReadPosition(s)];
	//				if(ChessUtil::IsPawn(targetPiece)){
	//					if(ChessUtil::IsWhite(targetPiece)) whiteScore += 2*ChessUtil::pieceScoreMapping[ReadPosition(s)];
	//				}
	//				//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
	//			}
	//		}
	//	}else if(ChessUtil::IsBishop(piece)){
	//		whiteScore += 3 * ChessUtil::pieceScoreMapping[piece];
	//		//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
	//		for(int i = 4; i < 8; i++){
	//			std::vector<short> controlSquare = ChessUtil::squareControlMap[(int)square].GetSlidingSquare(i);
	//			for(short s : controlSquare){
	//				if(TargetIsEmpty(s)){
	//					whiteScore += 2 * ChessUtil::midGameScoreMap[(int)s];
	//					//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
	//				}else if(!ChessUtil::IsWhite(ReadPosition(s)) && ChessUtil::IsKing(ReadPosition(s))){
	//					whiteScore += ChessUtil::checkScore;
	//					//std::cout << "King: " << ChessUtil::SquareToString(s) << " Checked by " << ReadPosition(s) << std::endl;
	//					//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
	//					break;
	//				}else{
	//					whiteScore += 0.5*ChessUtil::pieceScoreMapping[ReadPosition(s)];
	//					//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
	//					break;
	//				}
	//			}
	//		}
	//	}else if(ChessUtil::IsKnight(piece)){
	//		whiteScore += 3 * ChessUtil::pieceScoreMapping[piece];
	//		//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
	//		std::vector<short> controlSquare = ChessUtil::squareControlMap[(int)square].GetKnightSquare();
	//		for(short s : controlSquare){
	//			if(TargetIsEmpty(s)){
	//				whiteScore += 2 * ChessUtil::midGameScoreMap[(int)s];
	//				//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
	//			}else if(!ChessUtil::IsWhite(ReadPosition(s)) && ChessUtil::IsKing(ReadPosition(s))){
	//				whiteScore += ChessUtil::checkScore;
	//				//std::cout << "King: " << ChessUtil::SquareToString(s) << " Checked by " << ReadPosition(s) << std::endl;
	//				//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
	//			}else{
	//				whiteScore += 0.5*ChessUtil::pieceScoreMapping[ReadPosition(s)];
	//				//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
	//			}
	//		}
	//	}else if(ChessUtil::IsRook(piece)){
	//		whiteScore += 3 * ChessUtil::pieceScoreMapping[piece];
	//		//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
	//		for(int i = 0; i < 4; i++){
	//			std::vector<short> controlSquare = ChessUtil::squareControlMap[(int)square].GetSlidingSquare(i);
	//			for(short s : controlSquare){
	//				if(TargetIsEmpty(s)){
	//					whiteScore += 2 * ChessUtil::midGameScoreMap[(int)s];
	//					//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
	//				}else if(!ChessUtil::IsWhite(ReadPosition(s)) && ChessUtil::IsKing(ReadPosition(s))){
	//					whiteScore += ChessUtil::checkScore;
	//					//std::cout << "King: " << ChessUtil::SquareToString(s) << " Checked by " << ReadPosition(s) << std::endl;
	//					//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
	//					break;
	//				}else{
	//					whiteScore += 0.5*ChessUtil::pieceScoreMapping[ReadPosition(s)];
	//					//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
	//					break;
	//				}
	//			}
	//		}
	//	}else if(ChessUtil::IsQueen(piece)){
	//		whiteScore += 3 * ChessUtil::pieceScoreMapping[piece];
	//		//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
	//		for(int i = 0; i < 8; i++){
	//			std::vector<short> controlSquare = ChessUtil::squareControlMap[(int)square].GetSlidingSquare(i);
	//			for(short s : controlSquare){
	//				if(TargetIsEmpty(s)){
	//					whiteScore += ChessUtil::midGameScoreMap[(int)s];
	//					//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
	//				}else if(!ChessUtil::IsWhite(ReadPosition(s)) && ChessUtil::IsKing(ReadPosition(s))){
	//					whiteScore += ChessUtil::checkScore;
	//					//std::cout << "King: " << ChessUtil::SquareToString(s) << " Checked by " << ReadPosition(s) << std::endl;
	//					//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
	//					break;
	//				}else{
	//					whiteScore += 0.5*ChessUtil::pieceScoreMapping[ReadPosition(s)];
	//					//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
	//					break;
	//				}
	//			}
	//		}
	//	}else if(ChessUtil::IsKing(piece)){
	//		whiteScore += 80;
	//		for(int i = 0; i < 8; i++){
	//			std::vector<short> controlSquare = ChessUtil::squareControlMap[(int)square].GetSlidingSquare(i);
	//			for(short s : controlSquare){
	//				if(!TargetIsEmpty(s)){
	//					whiteScore += 60;
	//					break;
	//					//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
	//				}else{
	//					whiteScore -= 10;
	//				}
	//			}
	//		}
	//	}
	//}
	//for(short piece : blackPieceOnBoard){
	//	short square = GetPieceLocation(piece);
	//	//std::cout << ChessUtil::pieceMapping[piece] << ChessUtil::SquareToString(square) << std::endl;
	//	if(ChessUtil::IsPawn(piece)){
	//		blackScore += 3 * ChessUtil::pieceScoreMapping[piece];
	//		//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
	//		std::vector<short> controlSquare = ChessUtil::squareControlMap[(int)square].GetPawnSquare(false);
	//		for(short s : controlSquare){
	//			if(TargetIsEmpty(s)){
	//				blackScore += ChessUtil::midGameScoreMap[(int)s];
	//				if(fullmove < 2) blackScore += 10 * ChessUtil::midGameScoreMap[(int)s];
	//				//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
	//			}else if(ChessUtil::IsWhite(ReadPosition(s)) && ChessUtil::IsKing(ReadPosition(s))){
	//				blackScore += ChessUtil::checkScore;
	//				//std::cout << "King: " << ChessUtil::SquareToString(s) << " Checked by " << ReadPosition(s) << std::endl;
	//				//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
	//			}else{
	//				short targetPiece = ReadPosition(s);
	//				blackScore += ChessUtil::pieceScoreMapping[ReadPosition(s)];
	//				if(ChessUtil::IsPawn(targetPiece)){
	//					if(!ChessUtil::IsWhite(targetPiece)) blackScore += 2*ChessUtil::pieceScoreMapping[ReadPosition(s)];
	//				}
	//				//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
	//			}
	//		}
	//	}else if(ChessUtil::IsBishop(piece)){
	//		blackScore += 3 * ChessUtil::pieceScoreMapping[piece];
	//		//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
	//		for(int i = 4; i < 8; i++){
	//			std::vector<short> controlSquare = ChessUtil::squareControlMap[(int)square].GetSlidingSquare(i);
	//			for(short s : controlSquare){
	//				if(TargetIsEmpty(s)){
	//					blackScore += 2 * ChessUtil::midGameScoreMap[(int)s];
	//					//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
	//				}else if(ChessUtil::IsWhite(ReadPosition(s)) && ChessUtil::IsKing(ReadPosition(s))){
	//					blackScore += ChessUtil::checkScore;
	//					//std::cout << "King: " << ChessUtil::SquareToString(s) << " Checked by " << ReadPosition(s) << std::endl;
	//					//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
	//					break;
	//				}else{
	//					blackScore += 0.5*ChessUtil::pieceScoreMapping[ReadPosition(s)];
	//					//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
	//					break;
	//				}
	//			}
	//		}
	//	}else if(ChessUtil::IsKnight(piece)){
	//		blackScore += 3 * ChessUtil::pieceScoreMapping[piece];
	//		//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
	//		std::vector<short> controlSquare = ChessUtil::squareControlMap[(int)square].GetKnightSquare();
	//		for(short s : controlSquare){
	//			if(TargetIsEmpty(s)){
	//				blackScore += 2 * ChessUtil::midGameScoreMap[(int)s];
	//				//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
	//			}else if(ChessUtil::IsWhite(ReadPosition(s)) && ChessUtil::IsKing(ReadPosition(s))){
	//				blackScore += ChessUtil::checkScore;
	//				//std::cout << "King: " << ChessUtil::SquareToString(s) << " Checked by " << ReadPosition(s) << std::endl;
	//				//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
	//				break;
	//			}else{
	//				blackScore += 0.5*ChessUtil::pieceScoreMapping[ReadPosition(s)];
	//				//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
	//				break;
	//			}
	//		}
	//	}else if(ChessUtil::IsRook(piece)){
	//		blackScore += 3 * ChessUtil::pieceScoreMapping[piece];
	//		//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
	//		for(int i = 0; i < 4; i++){
	//			std::vector<short> controlSquare = ChessUtil::squareControlMap[(int)square].GetSlidingSquare(i);
	//			for(short s : controlSquare){
	//				if(TargetIsEmpty(s)){
	//					blackScore += 2 * ChessUtil::midGameScoreMap[(int)s];
	//					//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
	//				}else if(ChessUtil::IsWhite(ReadPosition(s)) && ChessUtil::IsKing(ReadPosition(s))){
	//					blackScore += ChessUtil::checkScore;
	//					//std::cout << "King: " << ChessUtil::SquareToString(s) << " Checked by " << ReadPosition(s) << std::endl;
	//					//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
	//					break;
	//				}else{
	//					blackScore += 0.5*ChessUtil::pieceScoreMapping[ReadPosition(s)];
	//					//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
	//					break;
	//				}
	//			}
	//		}
	//	}else if(ChessUtil::IsQueen(piece)){
	//		blackScore += 3 * ChessUtil::pieceScoreMapping[piece];
	//		//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
	//		for(int i = 0; i < 8; i++){
	//			std::vector<short> controlSquare = ChessUtil::squareControlMap[(int)square].GetSlidingSquare(i);
	//			for(short s : controlSquare){
	//				if(TargetIsEmpty(s)){
	//					blackScore += ChessUtil::midGameScoreMap[(int)s];
	//					//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
	//				}else if(ChessUtil::IsWhite(ReadPosition(s)) && ChessUtil::IsKing(ReadPosition(s))){
	//					blackScore += ChessUtil::checkScore;
	//					//std::cout << "King: " << ChessUtil::SquareToString(s) << " Checked by " << ReadPosition(s) << std::endl;
	//					//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
	//					break;
	//				}else{
	//					blackScore += 0.5*ChessUtil::pieceScoreMapping[ReadPosition(s)];
	//					//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
	//					break;
	//				}
	//			}
	//		}
	//	}else if(ChessUtil::IsKing(piece)){
	//		blackScore += 80;
	//		for(int i = 0; i < 8; i++){
	//			std::vector<short> controlSquare = ChessUtil::squareControlMap[(int)square].GetSlidingSquare(i);
	//			for(short s : controlSquare){
	//				if(!TargetIsEmpty(s)){
	//					blackScore += 60;
	//					break;
	//					//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
	//				}else{
	//					blackScore -= 10;
	//				}
	//			}
	//		}
	//	}
	//}
	//finalScore = whiteScore - blackScore;
	////Draw
	//if(finalScore > 100 && !whiteTurn && IsDraw()){
	//	finalScore = -2000;
	//}else if(finalScore < 100 && whiteTurn && IsDraw()){
	//	finalScore = 2000;
	//}
	//std::cout << "W: " << whiteScore << ", B: " << blackScore << std::endl;
	//return finalScore;
	return 1;
}