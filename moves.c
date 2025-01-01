#include <stdlib.h>
#include "utils.h"
#include "moves.h"

extern char board[8][8];
extern int touched[8][8];

int canReachWithStep(int diffi, int diffj, int si, int sj, int di, int dj);

int pawn(int player, int si, int sj, int di, int dj){
    int distance = abs(si - di);
    if(distance > 2)
        return 0;

    if(distance == 1 && sj == dj && board[di][dj] == '.')
        return 1;

    if((((di<si) && !player) || ((di>si) && player)) && distance == 1 && (sj-1 == dj || sj+1==dj) && board[di][dj] != '.' && getPiecePlayer(board[di][dj])!=player)
        return 1;

    if(distance == 2 && sj == dj && board[di][dj] == '.'){
        if(player)
            return si==1 && board[di-1][dj] == '.';
        else
            return si==6 && board[di+1][dj] == '.';
    }
    return 0;
}

int king(int player, int si, int sj, int di, int dj){
    char k = board[si][sj];
    if(!touched[si][di] && si==di){
        if(dj-sj==2){
            int row = 7-getPiecePlayer(k)*7;
            if(!touched[di][7] && canReachWithStep(0, 1, si, sj, si, 7)){
                touched[di][7] = 1;
                touched[di][dj-1] = 1;
                board[di][dj-1] = board[di][7];
                board[di][7] = '.';
                return 1;
            }
                
        }
        if(dj-sj==-2){
            if(!touched[di][0] && canReachWithStep(0, -1, si, sj, si, 0)){
                touched[di][0] = 1;
                touched[di][sj-1] = 1;
                board[di][sj-1] = board[si][0];
                board[di][0] = '.';
                return 1;
            }
                
        }
    }
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

int canReachWithStep(int diffi, int diffj, int si, int sj, int di, int dj){
    int ni, nj;
    for (int i = 1; i < 8; i++)
    {
        ni = si + diffi*i;
        nj = sj + diffj*i;
        if (ni < 0 || nj < 0 || ni > 7 || nj > 7)
            continue;
        if (ni == di && dj == nj){
            return 1;
        }
        if (board[ni][nj] != '.')
            return 0;
    }
    return 0;
}

int rook(int player, int si, int sj, int di, int dj)
{
    int diffi = di - si;
    int diffj = dj - sj;
    if(diffi && diffj)
        return 0;

    if(!(canReachWithStep(-1, 0, si, sj, di, dj) || canReachWithStep(1, 0, si, sj, di, dj) || canReachWithStep(0, 1, si, sj, di, dj) || canReachWithStep(0, -1, si, sj, di, dj)))
        return 0;

    return board[di][dj]=='.' || (getPiecePlayer(board[di][dj]) != player);
}

int bishop(int player, int si, int sj, int di, int dj)
{
    int diffi = di - si;
    int diffj = dj - sj;
    if(abs(diffi) != abs(diffj))
        return 0;

    if(!(canReachWithStep(-1, -1, si, sj, di, dj) || canReachWithStep(1, 1, si, sj, di, dj) || canReachWithStep(1, -1, si, sj, di, dj) || canReachWithStep(-1, 1, si, sj, di, dj)))
        return 0;

    return board[di][dj]=='.' || (getPiecePlayer(board[di][dj]) != player);
}


int queen(int player, int si, int sj, int di, int dj){
    return rook(player, si, sj, di, dj) || bishop(player, si, sj, di, dj);
}
