#include "Bitboards.h"

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
                        //std::cout << "White Pawn " << (1ULL << counter) << " counter=" << counter << std::endl;
                        whiteBitRows[0] |= 1ULL << counter;
                        //std::cout << whiteBitRows[0] << std::endl;
                        //std::cout << ChessUtil::bitboardToString(whiteBitRows[0]) << std::endl;
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
                }
                counter++;
                charIdx++;
            }
        }
                        //std::cout << "##########" << whiteBitRows[0] << std::endl;
                        //std::cout << ChessUtil::bitboardToString(whiteBitRows[0]) << std::endl;
        for(int j = 0; j < 6; j++){
            //if(j==0){
            //    std::cout << "White Pawn Board: " << ChessUtil::bitboardToString(whiteBitboards[j]) << " to " << ChessUtil::bitboardToString((whiteBitRows[j] << (i * 8))) << " shifted " << i * 8 << std::endl;
            //}
            whiteBitboards[j] |= whiteBitRows[j] << (i * 8);
            blackBitboards[j] |= blackBitRows[j] << (i * 8);
        }
    }
}