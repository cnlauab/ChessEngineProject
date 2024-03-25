#include "Score.h"

Score::Score(Position& position){
    CalculateScore(position);
}

void Score::CalculateScore(Position& position){
    calculateMaterialScore(position);
    calculatePawnStructureScore(position);
    calculatePieceCoordinationScore(position);
    calculatePieceActivityScore(position);
    calculateKingSafetyScore(position);
    calculateKingActivityScore(position);
    calculateCheckScore(position);
}

short Score::FinalEvaluation(){
    return (materialScore[0] - materialScore[1]) + (pawnStructureScore[0] - pawnStructureScore[1]) + (pieceCordinationScore[0] - pieceCordinationScore[1]) + (pieceActivityScore[0] - pieceActivityScore[1]) + (kingSafetyScore[0] - kingSafetyScore[1]);// + (kingActivityScore[0] - kingActivityScore[1]) + (checkScore[0] - checkScore[1]);
}

std::string Score::ScoreToString(){
    std::string result = "";
    result += "Material:\n";
    result += "White:" + std::to_string(materialScore[0]) + "\n";
    result += "Black:" + std::to_string(materialScore[1]) + "\n";
    result += "Pawn Structure:\n";
    result += "White:" + std::to_string(pawnStructureScore[0]) + "\n";
    result += "Black:" + std::to_string(pawnStructureScore[1]) + "\n";
    result += "Piece Coordination:\n";
    result += "White:" + std::to_string(pieceCordinationScore[0]) + "\n";
    result += "Black:" + std::to_string(pieceCordinationScore[1]) + "\n";
    result += "Piece Activity:\n";
    result += "White:" + std::to_string(pieceActivityScore[0]) + "\n";
    result += "Black:" + std::to_string(pieceActivityScore[1]) + "\n";
    result += "King Safety:\n";
    result += "White:" + std::to_string(kingSafetyScore[0]) + "\n";
    result += "Black:" + std::to_string(kingSafetyScore[1]) + "\n";
    result += "King Activity:\n";
    result += "White:" + std::to_string(kingActivityScore[0]) + "\n";
    result += "Black:" + std::to_string(kingActivityScore[1]) + "\n";
    result += "Checkmate/Stalemate/Checked:\n";
    result += "White:" + std::to_string(checkScore[0]) + "\n";
    result += "Black:" + std::to_string(checkScore[1]) + "\n"; 
    return result;
}

void Score::calculateMaterialScore(Position& position){
    for(int i = 0; i < 6; i++){
        short numPiece = BitUtil::getNumberOnBits(position.bitboards.GetPieceBitboard(true, i));
        materialScore[0] += ChessUtil::pieceTypeScoreMapping[i];
        numPiece = BitUtil::getNumberOnBits(position.bitboards.GetPieceBitboard(false, i));
        materialScore[1] += ChessUtil::pieceTypeScoreMapping[i];
    }
}

void Score::calculatePawnStructureScore(Position& position){
    short numberOfPassedPawn;
    short numberOfChainedPawn;
    short numberOfProtectedPawn;

    short numberOfDoubledPawn;
    short numberOfIsolatedPawn;
    short numberOfBackwardPawn;
    //White
    std::array<short, 64> pawns = BitUtil::getBitPositions(position.bitboards.GetPieceBitboard(true,0));
    for(int i = 0; i < 64; i++){
        short square = pawns[i];
        if(square == 99) break;
        short file = ChessUtil::GetFile(square);
        short rank = ChessUtil::GetRank(square);
        unsigned long long passedPawnMask = ((~0ULL) << (rank + 1)) & (BitUtil::GetFileBit(file) | BitUtil::GetFileBit(file + 1) | BitUtil::GetFileBit(file - 1));//Forward bits & opposite color pawn
        unsigned long long chainedPawnMask = BitUtil::pawnControlBits(position.bitboards.GetPieceBitboard(true, 0), true);//pawn control bits
        //unsigned long long protectedPawnMask = 0ULL;//Other pieces control bits

        unsigned long long doubledPawnMask = position.bitboards.GetPieceBitboard(true, 0) & (BitUtil::GetFileBit(file) & ~(1ULL << square));//Same File bits
        unsigned long long isolatedPawnMask = position.bitboards.GetPieceBitboard(true, 0) & (BitUtil::GetFileBit(file + 1) | BitUtil::GetFileBit(file - 1));//Adjcent File Bits & same color pawns bits
        unsigned long long backwardPawnMask = ((~0ULL) >> (8 - rank)) & (BitUtil::GetFileBit(file) | BitUtil::GetFileBit(file + 1) | BitUtil::GetFileBit(file - 1));//Backward bits & same color pawns
        
        short numOfPassedPawn = BitUtil::getNumberOnBits(passedPawnMask);
        short numOfChainedPawn = BitUtil::getNumberOnBits(chainedPawnMask);
        short numOfDoubledPawn = BitUtil::getNumberOnBits(doubledPawnMask);
        short numOfIsolatedPawn = BitUtil::getNumberOnBits(isolatedPawnMask);
        short numOfBackwardPawn = BitUtil::getNumberOnBits(backwardPawnMask);
        pawnStructureScore[0] = numOfPassedPawn * 100 + numOfChainedPawn * 50 - numOfDoubledPawn * 50 - numOfIsolatedPawn * 25 - numOfBackwardPawn * 25;
    }
    //Black
    pawns = BitUtil::getBitPositions(position.bitboards.GetPieceBitboard(false,0));
    for(short square : pawns){

        short file = ChessUtil::GetFile(square);
        short rank = ChessUtil::GetRank(square);
        unsigned long long passedPawnMask = ((~0ULL) << (rank + 1)) & (BitUtil::GetFileBit(file) | BitUtil::GetFileBit(file + 1) | BitUtil::GetFileBit(file - 1));//Forward bits & opposite color pawn
        unsigned long long chainedPawnMask = BitUtil::pawnControlBits(position.bitboards.GetPieceBitboard(false, 0), false);//pawn control bits
        //unsigned long long protectedPawnMask = 0ULL;//Other pieces control bits

        unsigned long long doubledPawnMask = position.bitboards.GetPieceBitboard(false, 0) & (BitUtil::GetFileBit(file) & ~(1ULL << square));//Same File bits
        unsigned long long isolatedPawnMask = position.bitboards.GetPieceBitboard(false, 0) & (BitUtil::GetFileBit(file + 1) | BitUtil::GetFileBit(file - 1));//Adjcent File Bits & same color pawns bits
        unsigned long long backwardPawnMask = ((~0ULL) >> (8 - rank)) & (BitUtil::GetFileBit(file) | BitUtil::GetFileBit(file + 1) | BitUtil::GetFileBit(file - 1));//Backward bits & same color pawns
        
        short numOfPassedPawn = BitUtil::getNumberOnBits(passedPawnMask);
        short numOfChainedPawn = BitUtil::getNumberOnBits(chainedPawnMask);
        short numOfDoubledPawn = BitUtil::getNumberOnBits(doubledPawnMask);
        short numOfIsolatedPawn = BitUtil::getNumberOnBits(isolatedPawnMask);
        short numOfBackwardPawn = BitUtil::getNumberOnBits(backwardPawnMask);
        pawnStructureScore[1] = numOfPassedPawn * 100 + numOfChainedPawn * 50 - numOfDoubledPawn * 50 - numOfIsolatedPawn * 25 - numOfBackwardPawn * 25;
    }
}

void Score::calculatePieceCoordinationScore(Position& position){
    unsigned long long controlMap = position.bitboards.controlledBits(true);
    unsigned long long knightMap = position.bitboards.GetPieceBitboard(true, 2) & controlMap;//4x
    unsigned long long bishopMap = position.bitboards.GetPieceBitboard(true, 3) & controlMap;//4x
    unsigned long long rookMap = position.bitboards.GetPieceBitboard(true, 4) & controlMap;//1x
    unsigned long long pawnMap = position.bitboards.GetPieceBitboard(true, 0) & controlMap;//1x
    pieceCordinationScore[0] += BitUtil::getNumberOnBits(knightMap) * 40 + BitUtil::getNumberOnBits(bishopMap) * 40 + BitUtil::getNumberOnBits(rookMap) * 10 + BitUtil::getNumberOnBits(pawnMap) * 10;

    controlMap = position.bitboards.controlledBits(false);
    knightMap = position.bitboards.GetPieceBitboard(false, 2) & controlMap;//4x
    bishopMap = position.bitboards.GetPieceBitboard(false, 3) & controlMap;//4x
    rookMap = position.bitboards.GetPieceBitboard(false, 4) & controlMap;//1x
    pawnMap = position.bitboards.GetPieceBitboard(false, 0) & controlMap;//1x
    pieceCordinationScore[1] += BitUtil::getNumberOnBits(knightMap) * 40 + BitUtil::getNumberOnBits(bishopMap) * 40 + BitUtil::getNumberOnBits(rookMap) * 10 + BitUtil::getNumberOnBits(pawnMap) * 10;
}

void Score::calculatePieceActivityScore(Position& position){
    unsigned long long controlBits = position.bitboards.controlledBits(true);
    int numofBits = BitUtil::getNumberOnBits(controlBits);
    pieceActivityScore[0] += numofBits * 20;
    
    controlBits = position.bitboards.controlledBits(false);
    numofBits = BitUtil::getNumberOnBits(controlBits);
    pieceActivityScore[1] += numofBits * 20;
}

void Score::calculateKingSafetyScore(Position& position){
    short kingLocation = position.bitboards.KingLocation(true);
    unsigned long long kingControlBits = ChessUtil::squareControlMap[kingLocation].kingControlBitboard;
    short kingLocationScore = ChessUtil::kingSafetyScoreMap[kingLocation] * 10;
    kingSafetyScore[0] += BitUtil::getNumberOnBits(kingControlBits & position.bitboards.allWhiteBitboard()) * 10 + kingLocationScore;

    kingLocation = position.bitboards.KingLocation(false);
    kingControlBits = ChessUtil::squareControlMap[kingLocation].kingControlBitboard;
    kingLocationScore = ChessUtil::kingSafetyScoreMap[kingLocation] * 10;
    kingSafetyScore[0] += BitUtil::getNumberOnBits(kingControlBits & position.bitboards.allBlackBitboard()) * 10 + kingLocationScore;
}

void Score::calculateKingActivityScore(Position& position){
    //std::vector<short> pieceOnBoard = white? position.whitePieceOnBoard : position.blackPieceOnBoard;
    //for(short piece : pieceOnBoard){
	//	short square = position.GetPieceLocation(piece);
    //    materialScore[white] += ChessUtil::pieceScoreMapping[piece];
    //}
}

void Score::calculateCheckScore(Position& position){
    if(position.checkmate){
        if(position.whiteTurn){
            checkScore[0] = 0;
            checkScore[1] = 4000;
        }else{
            checkScore[0] = 4000;
            checkScore[1] = 0;
        }
        return;
    }
    if(position.stalemate){
        if(position.whiteTurn){
            checkScore[0] = 4000;
            checkScore[1] = 0;
        }else{
            checkScore[0] = 0;
            checkScore[1] = 4000;
        }
        return;
    }
    if(position.doubleCheck || position.discoverCheck){
        if(position.whiteTurn){
            checkScore[0] = 0;
            checkScore[1] = 2000;
        }else{
            checkScore[0] = 2000;
            checkScore[1] = 0;
        }
        return;
    }
    if(position.check){
        if(position.whiteTurn){
            checkScore[0] = 0;
            checkScore[1] = 1000;
        }else{
            checkScore[0] = 1000;
            checkScore[1] = 0;
        }
        return;
    }
}