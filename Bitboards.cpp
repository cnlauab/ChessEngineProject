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

unsigned long long Bitboards::allEmptySquareBitboard(){
    return !(allWhiteBitboard() | allBlackBitboard());
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

void Bitboards::MoveBit(short from, short to, bool whiteTurn){
    unsigned long long fromBit = 1ULL << from;
    unsigned long long toBit = 1ULL << to;
    if(whiteTurn){
        for(int i = 0; i < 6; i++){
            //Move Piece
            if(whiteBitboards[i] & fromBit) {
                whiteBitboards[i] = (whiteBitboards[i] & !fromBit) | toBit;
            }
            //Capture Piece
            if(blackBitboards[i] & toBit) {
                blackBitboards[i] = blackBitboards[i] & !toBit;
            }
        }
    }else{
        for(int i = 0; i < 6; i++){
            //Move Piece
            if(blackBitboards[i] & fromBit) {
                blackBitboards[i] = (blackBitboards[i] & !fromBit) | toBit;
            }
            //Capture Piece
            if(whiteBitboards[i] & toBit) {
                whiteBitboards[i] = whiteBitboards[i] & !toBit;
            }
        }
    }
}

std::string Bitboards::BitboardsToString(){

	std::string result;
	std::string row;
	int rowCounter = 1;
	for (int i = 0; i < 64; ++i) {
		auto pieceIdx = GetPieceTypeFromSquare(i);
        char piece = ' ';
        if(pieceIdx != -1){
            piece = hasWhitePiece(i) ? toupper(ChessUtil::bitboardIndexPieceMapping[pieceIdx]) : tolower(ChessUtil::bitboardIndexPieceMapping[pieceIdx]);
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