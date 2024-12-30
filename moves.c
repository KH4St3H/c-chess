#include <stdlib.h>
#include "utils.h"
#include "moves.h"

extern char board[8][8];

int pawn(int player, int si, int sj, int di, int dj){
    int distance = abs(si - di);
    if(distance > 2)
        return 0;

    if(distance == 1 && sj == dj && board[di][dj] == '.')
        return 1;

    if(distance == 1 && (sj-1 == dj || sj+1==dj) && board[di][dj] != '.' && getPiecePlayer(board[di][dj])!=player)
        return 1;

    if(distance == 2 && sj == dj && board[di][dj] == '.' && si==1 && board[di-1][dj] == '.' && player)
        return 1;

    if(distance == 2 && sj == dj && board[di][dj] == '.' && si==6 && board[di+1][dj] == '.' && !player)
        return 1;

    return 0;
}

int king(int player, int si, int sj, int di, int dj){
    if(!(abs(si-di)<2 && abs(sj-dj)<2))
        return 0;
    if(board[di][dj] == '.')
        return 1;
    return (getPiecePlayer(board[si][sj]) != getPiecePlayer(board[di][dj]));
}

int knight(int player, int si, int sj, int di, int dj){
    if(!(abs(si-di)==1 && abs(sj-dj)==2) && !(abs(si-di)==2 && abs(sj-dj)==1))
        return 0;
    if(board[di][dj] == '.')
        return 1;
    return (getPiecePlayer(board[si][sj]) != getPiecePlayer(board[di][dj]));
}

int rook(int player, int si, int sj, int di, int dj)
{
    int ni, nj;
    int mul[2] = {1, -1};
    for(int mm=0; mm<2; mm++){
        int m = mul[mm];
        for (int i = 1; i < 8; i++)
        {
            ni = si + i*m;
            nj = sj;
            if (ni < 0 || nj < 0 || ni > 7 || nj > 7)
                continue;
            if (ni == di && dj == nj)
                return board[ni][nj]=='.' || (getPiecePlayer(board[ni][nj]) != player);
            if (board[ni][nj] != '.')
                break;
        }
        for (int i = 1; i < 8; i++)
        {
            ni = si;
            nj = si + i*m;
            if (ni < 0 || nj < 0 || ni > 7 || nj > 7)
                continue;
            if (ni == di && dj == nj)
                return board[ni][nj]=='.' || (getPiecePlayer(board[ni][nj]) != player);
            if (board[ni][nj] != '.')
                break;
        }
    }
    
    return 0;
}

int bishop(int player, int si, int sj, int di, int dj)
{
    int ni, nj;
    int mul[2] = {1, -1};
    for(int mm=0; mm<2; mm++){
        int m = mul[mm];
        for (int i = 1; i < 8; i++)
        {
            ni = si + i*m;
            nj = sj + i*m;
            if (ni < 0 || nj < 0 || ni > 7 || nj > 7)
                continue;
            if (ni == di && dj == nj)
                return board[ni][nj]=='.' || (getPiecePlayer(board[ni][nj]) != player);
            if (board[ni][nj] != '.')
                break;
        }
        for (int i = 1; i < 8; i++)
        {
            ni = si + i*m;
            nj = si - i*m;
            if (ni < 0 || nj < 0 || ni > 7 || nj > 7)
                continue;
            if (ni == di && dj == nj)
                return board[ni][nj]=='.' || (getPiecePlayer(board[ni][nj]) != player);
            if (board[ni][nj] != '.')
                break;
        }
    }
    return 0;
}


int queen(int player, int si, int sj, int di, int dj){
    return rook(player, si, sj, di, dj) || bishop(player, si, sj, di, dj);
}
