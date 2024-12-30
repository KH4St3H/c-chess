#include "utils.h"

int getPiecePlayer(char c){
    return (c > 96);
}

char getPieceLower(char piece){
    return piece > 96 ? piece : piece + 32;
}