#include "SquareControl.h"

SquareControl::SquareControl(short square){
    //std::cout << "Square Control Constructed " << square << std::endl;
    origin = square;
    rank = square / 8;
    file = square % 8;
    //Knight squares
	short starting1 = square - 10;
	short starting2 = square - 17;
	short starting3 = square - 15;
	short starting4 = square - 6;
	short starting5 = square + 6;
	short starting6 = square + 15;
	short starting7 = square + 17;
	short starting8 = square + 10;
	short knight[8] = { starting1, starting2, starting3, starting4, starting5, starting6, starting7, starting8 };
	//short knight[8] = { square - 10, square - 17, square - 15, square - 6, square + 6, square + 15, square + 17, square + 10 };
	for (int i = 0; i < 8; i++)
	{
		if (knight[i] > 63 || knight[i] < 0) continue;
		if (i == 0 || i == 1) {
			bool lefter = SquareControl::GetFile(knight[i]) < SquareControl::GetFile(square);
			bool lower = SquareControl::GetRank(knight[i]) < SquareControl::GetRank(square);
			if (lefter && lower) {
                //std::cout << "Knight square (" << square << "): " << knight[i] << std::endl;
                knightSquare.push_back(knight[i]);
                knightControlBitboard |= 1ULL << knight[i];
            }
		}
		else if (i == 2 || i == 3) {
			bool righter = SquareControl::GetFile(knight[i]) > SquareControl::GetFile(square);
			bool lower = SquareControl::GetRank(knight[i]) < SquareControl::GetRank(square);
			if (righter && lower) {
                //std::cout << "Knight square (" << square << "): " << knight[i] << std::endl;
                knightSquare.push_back(knight[i]);
                knightControlBitboard |= 1ULL << knight[i];
            }
		}
		else if (i == 4 || i == 5) {
			bool lefter = SquareControl::GetFile(knight[i]) < SquareControl::GetFile(square);
			bool higher = SquareControl::GetRank(knight[i]) > SquareControl::GetRank(square);
			if (lefter && higher) {
                //std::cout << "Knight square (" << square << "): " << knight[i] << std::endl;
                knightSquare.push_back(knight[i]);
                knightControlBitboard |= 1ULL << knight[i];
            }
		}
		else if (i == 6 || i == 7) {
			bool righter = SquareControl::GetFile(knight[i]) > SquareControl::GetFile(square);
			bool higher = SquareControl::GetRank(knight[i]) > SquareControl::GetRank(square);
			if (righter && higher) {
                //std::cout << "Knight square (" << square << "): " << knight[i] << std::endl;
                knightSquare.push_back(knight[i]);
                knightControlBitboard |= 1ULL << knight[i];
            }
		}
    }
    //Sliding squares and King squares and Pawn squares
    short offsets[8] = {-1,1,-8,8,-9,-7,7,9};
    for(int i = 0; i < 8; ++i){
        short offset = offsets[i];
		short target = square + offset;
		bool outOfBound = SquareControl::SquareOutbound(square, target, i);
        
        if(!outOfBound) {
            //King
            kingSquare.push_back(target);
            kingControlBitboard |= 1ULL << target;
            //Pawn
            if(i == 6 || i == 7){
                pawnControlUpBitboard |= 1ULL << target;
                pawnSquareAbove.push_back(target);
            }
            if(i == 4 || i == 5){
                pawnControlDownBitboard |= 1ULL << target;
                pawnSquareBelow.push_back(target);
            }
            if(i == 3){
                pawnShiftUpBitboard |= 1ULL << target;
            }
            if(i == 2){
                pawnShiftDownBitboard |= 1ULL << target;
            }
        }
        //Sliding
		while (!outOfBound) {
            slidingSquare[i].push_back(target);
            allSlidingSquare.push_back(target);
            queenControlBitboard |= 1ULL << target;
            if(i < 4) {
                rookControlBitboard |= 1ULL << target;
            }else{
                bishopControlBitboard |= 1ULL << target;
            }
			target += offset;
			outOfBound = SquareControl::SquareOutbound(square, target, i);
		}
    }
    //Pawn push squares
    whitePawnPushTwoSquare = (square > 7 && square < 16) ? square + 16 : 99;
    if(square > 7 && square < 16) pawnShiftTwoUpBitboard |= 1ULL << (square + 16);
    blackPawnPushTwoSquare = (square > 47 && square < 56) ? square - 16 : 99;
    if(square > 47 && square < 56) pawnShiftTwoDownBitboard |= 1ULL << (square - 16);
    whitePawnPushOneSquare = (square <= 55) ? square + 8 : 99;
    blackPawnPushOneSquare = (square >= 8) ? square - 8 : 99;

    rookMagicBitMask = rookControlBitboard;
    bishopMagicBitMask = bishopControlBitboard;
    bool onAFile = (1ULL << square & 72340172838076673ULL) > 0ULL;
    bool onHFile = (1ULL << square & 9259542123273814144ULL) > 0ULL;
    bool on1stRank = (1ULL << square & 255ULL) > 0ULL;
    bool on8thRank = (1ULL << square & 18374686479671623680ULL) > 0ULL;
    if(!onAFile){
        rookMagicBitMask &= ~72340172838076673ULL;
        bishopMagicBitMask &= ~72340172838076673ULL;
    }
    if(!onHFile){
        rookMagicBitMask &= ~9259542123273814144ULL;
        bishopMagicBitMask &= ~9259542123273814144ULL;
    }
    if(!on1stRank){
        rookMagicBitMask &= ~255ULL;
        bishopMagicBitMask &= ~255ULL;
    }
    if(!on8thRank){
        rookMagicBitMask &= ~18374686479671623680ULL;
        bishopMagicBitMask &= ~18374686479671623680ULL;
    }
}

std::string SquareControl::toString()
{
    std::string result = "";
    result += "Kight Squares: ";
    for(short square : knightSquare) {
        result += std::to_string(square);
        result += " ";
    }
    result += "\n";
    result += "Sliding Squares: ";
    for(int i = 0; i < 8; i++){
        for(short square : slidingSquare[i]) {
            result += std::to_string(square);
            result += " ";
        }
        result += "\n";
    }
    result += "King Squares: ";
    for(short square : kingSquare) {
        result += std::to_string(square);
        result += " ";
    }
    result += "\n";
    result += "Pawn(Above) Squares: ";
    for(short square : pawnSquareAbove) {
        result += std::to_string(square);
        result += " ";
    }
    result += "\n";
    result += "Pawn(Below) Squares: ";
    for(short square : pawnSquareBelow) {
        result += std::to_string(square);
        result += " ";
    }
    return result;
}

std::vector<short> SquareControl::GetKnightSquare(){
    return knightSquare;
}

std::vector<short> SquareControl::GetSlidingSquare(int offsetType){
    return slidingSquare[offsetType];
}

std::vector<short> SquareControl::GetQueenSquare(){
    std::vector<short> result;
    for(int i = 0; i < 8; i++){
        result.insert(result.end(), slidingSquare[i].begin(), slidingSquare[i].end());
    }
    return result;
}

std::vector<short> SquareControl::GetBishopSquare(){
    std::vector<short> result;
    for(int i = 4; i < 8; i++){
        result.insert(result.end(), slidingSquare[i].begin(), slidingSquare[i].end());
    }
    return result;
}

std::vector<short> SquareControl::GetRookSquare(){
    std::vector<short> result;
    for(int i = 0; i < 4; i++){
        result.insert(result.end(), slidingSquare[i].begin(), slidingSquare[i].end());
    }
    return result;
}

std::vector<short> SquareControl::GetKingSquare(){
    return kingSquare;
}

std::vector<short> SquareControl::GetPawnSquare(bool upward){
    if(upward) return pawnSquareAbove;
    return pawnSquareBelow;
}

bool SquareControl::OnSameLine(short square){
    for(int i = 0; i < 8; i++){
        if(slidingSquare[i].size() == 0) continue;
        for(int j = 0; j < slidingSquare[i].size(); j++){
            if(square == slidingSquare[i][j]) return true;
        }
    }
    return false;
}

int SquareControl::GetRank(short square)
{
    return square / 8;
}

int SquareControl::GetFile(short square)
{
    return square % 8;
}

bool SquareControl::SquareOutbound(short startingSquare, short targetSquare, short offsetType) {
	if (targetSquare > 63 || targetSquare < 0) return true;
	if (offsetType < 2) {
		return SquareControl::GetRank(startingSquare) != SquareControl::GetRank(targetSquare);
	}
	if (offsetType < 4) {
		return SquareControl::GetFile(startingSquare) != SquareControl::GetFile(targetSquare);
	}
	else {
		bool higher = SquareControl::GetRank(targetSquare) > SquareControl::GetRank(startingSquare);
		bool lower = SquareControl::GetRank(targetSquare) < SquareControl::GetRank(startingSquare);
		bool righter = SquareControl::GetFile(targetSquare) > SquareControl::GetFile(startingSquare);
		bool lefter = SquareControl::GetFile(targetSquare) < SquareControl::GetFile(startingSquare);
		if (offsetType == 4) return !(lower && lefter);
		if (offsetType == 5) return !(lower && righter);
		if (offsetType == 6) return !(higher && lefter);
		if (offsetType == 7) return !(higher && righter);
	}
	return false;
}