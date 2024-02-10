#include "Score.h"

//Score::Score(Position& position);

int Score::FinalEvaluation(){
    return (materialScore[0] - materialScore[1]) + (pawnStructureScore[0] - pawnStructureScore[1]) + (pieceCordinationScore[0] - pieceCordinationScore[1]) + (pieceActivityScore[0] - pieceActivityScore[1]) + (kingSafetyScore[0] - kingSafetyScore[1]);// + (kingActivityScore[0] - kingActivityScore[1]) + (futureScore[0] - futureScore[1]);
}

void Score::calculateMaterialScore(Position& position, bool white){
    for(int i = 0; i < 6; i++){
        short numPiece = BitUtil::getNumberOnBits(position.bitboards.GetPieceBitboard(white, i));
        materialScore[white] += ChessUtil::pieceTypeScoreMapping[i];
    }
}

void Score::calculatePawnStructureScore(Position& position, bool white){
    short numberOfPassedPawn;
    short numberOfChainedPawn;
    short numberOfProtectedPawn;

    short numberOfDoubledPawn;
    short numberOfIsolatedPawn;
    short numberOfBackwardPawn;
    std::vector<short> pawns = BitUtil::getBitPositions(position.bitboards.GetPieceBitboard(white,0));
    for(short square : pawns){

        short file = ChessUtil::GetFile(square);
        short rank = ChessUtil::GetRank(square);
        unsigned long long passedPawnMask = ((~0ULL) << (rank + 1)) & (BitUtil::GetFileBit(file) | BitUtil::GetFileBit(file + 1) | BitUtil::GetFileBit(file - 1));//Forward bits & opposite color pawn
        unsigned long long chainedPawnMask = BitUtil::pawnControlBits(position.bitboards.GetPieceBitboard(white, 0), white);//pawn control bits
        unsigned long long protectedPawnMask = 0ULL;//Other pieces control bits

        unsigned long long doubledPawnMask = position.bitboards.GetPieceBitboard(white, 0) & (BitUtil::GetFileBit(file) & ~(1ULL << square));//Same File bits
        unsigned long long isolatedPawnMask = position.bitboards.GetPieceBitboard(white, 0) & (BitUtil::GetFileBit(file + 1) | BitUtil::GetFileBit(file - 1));//Adjcent File Bits & same color pawns bits
        unsigned long long backwardPawnMask = ((~0ULL) >> (8 - rank)) & (BitUtil::GetFileBit(file) | BitUtil::GetFileBit(file + 1) | BitUtil::GetFileBit(file - 1));//Backward bits & same color pawns
        
    
    }
}

void Score::calculatePieceCoordinationScore(Position& position, bool white){
    //std::vector<short> pieceOnBoard = white? position.whitePieceOnBoard : position.blackPieceOnBoard;
    //for(short piece : pieceOnBoard){
	//	short square = position.GetPieceLocation(piece);
    //    materialScore[white] += ChessUtil::pieceScoreMapping[piece];
    //}
}

void Score::calculatePieceActivityScore(Position& position, bool white){
    //std::vector<short> pieceOnBoard = white? position.whitePieceOnBoard : position.blackPieceOnBoard;
    //for(short piece : pieceOnBoard){
	//	short square = position.GetPieceLocation(piece);
    //    materialScore[white] += ChessUtil::pieceScoreMapping[piece];
    //}
}

void Score::calculateKingSafetyScore(Position& position, bool white){
    //std::vector<short> pieceOnBoard = white? position.whitePieceOnBoard : position.blackPieceOnBoard;
    //for(short piece : pieceOnBoard){
	//	short square = position.GetPieceLocation(piece);
    //    materialScore[white] += ChessUtil::pieceScoreMapping[piece];
    //}
}

void Score::calculateKingActivityScore(Position& position, bool white){
    //std::vector<short> pieceOnBoard = white? position.whitePieceOnBoard : position.blackPieceOnBoard;
    //for(short piece : pieceOnBoard){
	//	short square = position.GetPieceLocation(piece);
    //    materialScore[white] += ChessUtil::pieceScoreMapping[piece];
    //}
}