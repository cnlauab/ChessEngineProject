#include "Bitboards.h"

Bitboards::Bitboards(){
}

Bitboards::Bitboards(std::string fen){
	std::vector<std::string> rows;
	std::string delimiter = "/";

	size_t pos = 0;
	std::string token;
	while ((pos = fen.find(delimiter)) != std::string::npos) {
		token = fen.substr(0, pos);
		//std::cout << token << std::endl;
		rows.emplace_back(token);
		fen.erase(0, pos + delimiter.length());
	}
	rows.emplace_back(fen);

    for(int i = rows.size() - 1; i >= 0; i--){
        unsigned long long whiteBitRows[6] = {0ULL,0ULL,0ULL,0ULL,0ULL,0ULL};
        unsigned long long blackBitRows[6] = {0ULL,0ULL,0ULL,0ULL,0ULL,0ULL};
        int counter = 0;
        int charIdx = 0;
        while(counter < 8){
            if(isdigit(rows[i][charIdx])){
			    int emptyCounter = rows[i][charIdx] - '0';
                counter += emptyCounter;
                charIdx++;
            }else{
                switch(rows[i][charIdx]){
                    case 'P':
                        whiteBitRows[0] |= 1ULL << counter;
                        break;
                    case 'Q':
                        whiteBitRows[1] |= 1ULL << counter;
                        break;
                    case 'N':
                        whiteBitRows[2] |= 1ULL << counter;
                        break;
                    case 'B':
                        whiteBitRows[3] |= 1ULL << counter;
                        break;
                    case 'R':
                        whiteBitRows[4] |= 1ULL << counter;
                        break;
                    case 'K':
                        whiteBitRows[5] |= 1ULL << counter;
                        break;
                    case 'p':
                        blackBitRows[0] |= 1ULL << counter;
                        break;
                    case 'q':
                        blackBitRows[1] |= 1ULL << counter;
                        break;
                    case 'n':
                        blackBitRows[2] |= 1ULL << counter;
                        break;
                    case 'b':
                        blackBitRows[3] |= 1ULL << counter;
                        break;
                    case 'r':
                        blackBitRows[4] |= 1ULL << counter;
                        break;
                    case 'k':
                        blackBitRows[5] |= 1ULL << counter;
                        break;
                    default:
                        break;
                }
                counter++;
                charIdx++;
            }
        }
        for(int j = 0; j < 6; j++){
            whiteBitboards[j] |= whiteBitRows[j] << ((7-i) * 8);
            blackBitboards[j] |= blackBitRows[j] << ((7-i) * 8);
        }
    }
}

Bitboards::Bitboards(const Bitboards& other){
    for(int i = 0; i < 6; i++){
        whiteBitboards[i] = other.whiteBitboards[i];
        blackBitboards[i] = other.blackBitboards[i];
    }
}

unsigned long long Bitboards::allWhiteBitboard(){
    return whiteBitboards[0] | whiteBitboards[1] | whiteBitboards[2] | whiteBitboards[3] | whiteBitboards[4] | whiteBitboards[5];
}

unsigned long long Bitboards::allBlackBitboard(){
    return blackBitboards[0] | blackBitboards[1] | blackBitboards[2] | blackBitboards[3] | blackBitboards[4] | blackBitboards[5];
}

unsigned long long Bitboards::getBitboard(bool white){
    if(white){
        return allWhiteBitboard();
    }else{
        return allBlackBitboard();
    }
}

unsigned long long Bitboards::allEmptySquareBitboard(){
    return ~(allWhiteBitboard() | allBlackBitboard());
}

unsigned long long Bitboards::GetPieceBitboard(bool white, short index){
    return white ? whiteBitboards[index] : blackBitboards[index];
}

short Bitboards::KingLocation(bool white){
    return white ? BitUtil::bitToSquareMap[whiteBitboards[5]] : BitUtil::bitToSquareMap[blackBitboards[5]];
}

bool Bitboards::isEmpty(short square){
    return allEmptySquareBitboard() & 1ULL << square;
}

bool Bitboards::hasWhitePiece(short square){
    return allWhiteBitboard() & 1ULL << square;
}

int Bitboards::GetPieceTypeFromSquare(short square){
    unsigned long long squareBit = 1ULL << square;
    for(int i = 0; i < 6; i++){
        if(whiteBitboards[i] & squareBit) return i;
        if(blackBitboards[i] & squareBit) return i;
    }
    return -1;
}

bool Bitboards::hasBothColorBishop(bool white){
    unsigned long long darkSquareBishop = BitUtil::darkSquares & GetPieceBitboard(white, 3);
    unsigned long long lightSquareBishop = BitUtil::lightSquares & GetPieceBitboard(white, 3);
    return darkSquareBishop > 0ULL && lightSquareBishop > 0ULL;
}

void Bitboards::MoveBit(short from, short to, bool whiteTurn){
    unsigned long long fromBit = 1ULL << from;
    unsigned long long toBit = 1ULL << to;
    if(whiteTurn){
        for(int i = 0; i < 6; i++){
            //Move Piece
            if(whiteBitboards[i] & fromBit) {
                whiteBitboards[i] = (whiteBitboards[i] & ~fromBit) | toBit;
            }
            //Capture Piece
            if(blackBitboards[i] & toBit) {
                blackBitboards[i] = blackBitboards[i] & ~toBit;
            }
        }
    }else{
        for(int i = 0; i < 6; i++){
            //Move Piece
            if(blackBitboards[i] & fromBit) {
                blackBitboards[i] = (blackBitboards[i] & ~fromBit) | toBit;
            }
            //Capture Piece
            if(whiteBitboards[i] & toBit) {
                whiteBitboards[i] = whiteBitboards[i] & ~toBit;
            }
        }
    }
}

void Bitboards::EnpassantMoveBit(short to, bool whiteTurn){
    short pawnSquare = whiteTurn ? to - 8 : to + 8;
    if(whiteTurn){
        blackBitboards[0] &= ~(1ULL << pawnSquare);
    }else{
        whiteBitboards[0] &= ~(1ULL << pawnSquare);
    }
}

void Bitboards::CastlingMoveBit(short to){
    if(to == 2){
        whiteBitboards[4] = whiteBitboards[4] & ~(1ULL << 0) | (1ULL << 3);
    }else if(to == 6){
        whiteBitboards[4] = whiteBitboards[4] & ~(1ULL << 7) | (1ULL << 5);
    }else if(to == 58){
        blackBitboards[4] = blackBitboards[4] & ~(1ULL << 56) | (1ULL << 59);
    }else if(to == 62){
        blackBitboards[4] = blackBitboards[4] & ~(1ULL << 63) | (1ULL << 61);
    }
}

void Bitboards::PromotionMoveBit(short to, short promotionType, bool whiteTurn){
    if(whiteTurn){
        whiteBitboards[0] &= ~(1ULL << to);
        whiteBitboards[promotionType] |= 1ULL << to;
    }else{
        blackBitboards[0] &= ~(1ULL << to);
        blackBitboards[promotionType] |= 1ULL << to;
    }
}

void Bitboards::PutBackTakenPiece(short to, int type, bool whiteTurn){
    if(whiteTurn){
        blackBitboards[type] |= 1ULL << to;
    }else{
        whiteBitboards[type] |= 1ULL << to;
    }
}

void Bitboards::ReverseEnpassantMoveBit(short to, bool whiteTurn){
    short pawnSquare = whiteTurn ? to - 8 : to + 8;
    if(whiteTurn){
        blackBitboards[0] |= (1ULL << pawnSquare);
    }else{
        whiteBitboards[0] |= (1ULL << pawnSquare);
    }
}

void Bitboards::ReverseCastlingMoveBit(short to){
    if(to == 2){
        whiteBitboards[4] = whiteBitboards[4] & ~(1ULL << 3) | (1ULL << 0);
    }else if(to == 6){
        whiteBitboards[4] = whiteBitboards[4] & ~(1ULL << 5) | (1ULL << 7);
    }else if(to == 58){
        blackBitboards[4] = blackBitboards[4] & ~(1ULL << 59) | (1ULL << 56);
    }else if(to == 62){
        blackBitboards[4] = blackBitboards[4] & ~(1ULL << 61) | (1ULL << 63);
    }
}

void Bitboards::ReversePromotionMoveBit(short to, short promotionType, bool whiteTurn){
    if(whiteTurn){
        whiteBitboards[0] |= (1ULL << to);
        whiteBitboards[promotionType] &= ~(1ULL << to);
    }else{
        blackBitboards[0] |= (1ULL << to);
        blackBitboards[promotionType] &= ~(1ULL << to);
    }
}

unsigned long long Bitboards::controlledBits(bool white){
    unsigned long long result = 0ULL;
    unsigned long long* bitboards = white ? whiteBitboards : blackBitboards;
    for(int i = 0; i < 6; i++){
        if(i==0){
            result |= BitUtil::pawnControlBits(bitboards[i],white);
        }else if(i==2){
            result |= BitUtil::knightControlBits(bitboards[i]);
        }else if(i==5){
            result |= BitUtil::kingControlBits(bitboards[i]);
        }else{
            std::vector<short> squares = BitUtil::getBitPositions(bitboards[i]);
            for(short square : squares){
                //unsigned long long sildingBits = slidingControlBits(white, square, i);
                //if(i==1)std::cout << i << BitUtil::bitboardToString(sildingBits) << std::endl;
                result |= slidingControlBits(white, square, i);
            }
        }
    }
    //std::cout << result << std::endl;
    return result;
}

unsigned long long Bitboards::slidingControlBits(bool white, short square, short typeIndex){

	unsigned long long allPieces = ~allEmptySquareBitboard();
	unsigned long long friendlyPieces = white ? allWhiteBitboard() : allBlackBitboard();
    if(typeIndex == 1){
        unsigned long long bishopKey = BitUtil::GetMagicKey(allPieces, square, true);
	    unsigned long long rookKey = BitUtil::GetMagicKey(allPieces, square, false);
        return MagicUtil::magicBits.GetQueenMagic(square, rookKey, bishopKey) & ~friendlyPieces;
    }else if(typeIndex == 3){
        unsigned long long bishopKey = BitUtil::GetMagicKey(allPieces, square, true);
        return MagicUtil::magicBits.GetBishopMagic(square, bishopKey) & ~friendlyPieces;
    }else if(typeIndex == 4){
	    unsigned long long rookKey = BitUtil::GetMagicKey(allPieces, square, false);
        return MagicUtil::magicBits.GetRookMagic(square, rookKey) & ~friendlyPieces;
    }else{
        return 0ULL;
    }
}

std::vector<short> Bitboards::checkedAt(bool white){
    short kingLocation = KingLocation(white);
    unsigned long long pawnControl = white ? ChessUtil::squareControlMap[kingLocation].pawnControlUpBitboard : ChessUtil::squareControlMap[kingLocation].pawnControlDownBitboard;
    unsigned long long knightControl = ChessUtil::squareControlMap[kingLocation].knightControlBitboard;
    unsigned long long diagonalControl = slidingControlBits(white, kingLocation, 3);
    unsigned long long nonDiagonalControl = slidingControlBits(white, kingLocation, 4);

    pawnControl &= white ? blackBitboards[0] : whiteBitboards[0];
    knightControl &= white ? blackBitboards[2] : whiteBitboards[2];
    diagonalControl &= white ? blackBitboards[1] | blackBitboards[3] : whiteBitboards[1] | whiteBitboards[3];
    nonDiagonalControl &= white ? blackBitboards[1] | blackBitboards[4] : whiteBitboards[1] | whiteBitboards[4];

    unsigned long long checkedByBits = pawnControl | knightControl | diagonalControl | nonDiagonalControl;
    return BitUtil::getBitPositions(checkedByBits);
}

std::string Bitboards::BitboardsToString(){

	std::string result;
	std::string row;
	int rowCounter = 1;
	for (int i = 0; i < 64; ++i) {
		auto pieceIdx = GetPieceTypeFromSquare(i);
        char piece = ' ';
        if(pieceIdx != -1){
            piece = hasWhitePiece(i) ? toupper(BitUtil::bitboardIndexPieceMapping[pieceIdx]) : tolower(BitUtil::bitboardIndexPieceMapping[pieceIdx]);
        }
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

std::string Bitboards::ToFen(){
	std::string result;
	std::string temp = "";
	std::vector<std::string> ranks;
	
	int spaceCounter = 0;
	for(int i = 0; i < 64; ++i){
		auto pieceIdx = GetPieceTypeFromSquare(i);
        char piece = ' ';
        if(pieceIdx != -1){
            piece = hasWhitePiece(i) ? toupper(BitUtil::bitboardIndexPieceMapping[pieceIdx]) : tolower(BitUtil::bitboardIndexPieceMapping[pieceIdx]);
            if(spaceCounter > 0){
                temp += (48 + spaceCounter);
                spaceCounter = 0;
            }
            temp += piece;
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

	return result;
}