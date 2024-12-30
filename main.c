#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include "moves.h"
#include "utils.h"

char board[8][8];

char tempBoard[8][8];

void populateBoard();
void printBoard();

int isChecked();
int try(int, int, int, int);
int move(char, int, char, int);

int playerToMove = 0;


int main(){
    populateBoard();

    char s1;
    int s2;
    char d1;
    int d2;

    int succ;
    while(1){
        printBoard();
        printf("Enter move(Player %d):\n", playerToMove+1);
        scanf("%*[\n]");
        scanf("%c%d %c%d", &s1, &s2, &d1, &d2);
        succ = move(s1, s2, d1, d2);
        if(!succ){
            continue;
        }
        playerToMove = playerToMove ? 0 : 1;
    }

    return 0;
}

int canReach(int si, int sj, int di, int dj){
    char piece = board[si][sj];
    int player = 1;
    if(piece < 97){
        player = 0;
        piece += 32;
    }

    int ni, nj;
    int found;
    switch(piece){
        case 'r': 
            return rook(player, si, sj, di, dj);
        case 'b': 
            return bishop(player, si, sj, di, dj);
        case 'p':
            return pawn(player, si, sj, di, dj);
        case 'k':
            return king(player, si, sj, di, dj);
        case 'n':
            return knight(player, si, sj, di, dj);
        case 'q':
            return queen(player, si, sj, di, dj);
    }
    return 0;
}

int isChecked(){
    int ki=-1, kj=-1;
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            if(!(getPieceLower(board[i][j]) == 'k'))
                continue;
            if(getPiecePlayer(board[i][j]) != playerToMove){
                continue;
            }
            ki = i;
            kj = j;
        }
    }
    if(ki < 0)
        return 1;

    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            if(getPiecePlayer(board[i][j]) == playerToMove || board[i][j] == '.')
                continue;
            if(canReach(i, j, ki, kj))
                return 1;
        }
    }
    return 0;
}

int try(int i1, int j1, int i2, int j2){
    memcpy(tempBoard, board, 64*sizeof(char));
    board[i2][j2] = board[i1][j1];
    board[i1][j1] = '.';
    int c = isChecked();
    memcpy(board, tempBoard, 64*sizeof(char));
    return !c;
}

void promote(int i, int j){
    char piece = board[i][j];
    if(getPieceLower(piece) != 'p')
        return;
    if (i!=7 && i != 0)
        return;
    


    char c;
    while(1){
        printf("What do you want to promote to(q, r, n, b)? ");
        scanf("%*[\n]");
        scanf("%c", &c);
        if(c > 96)
            c -= 32;

        if(c=='Q' || c=='R' || c=='N' || c=='B'){
            c += playerToMove * 32;
            board[i][j] = c;
            return;
        }
    }

    
}


int move(char s1, int s2, char d1, int d2){
    int sj = s1 - 97;
    int si = 8 - s2;
    int dj = d1 - 97;
    int di = 8 - d2;

    int bounds[4] = {si, sj, di, dj};
    for(int i=0; i<4; i++){
        if(bounds[i] < 0 || bounds[i] > 7){
            printf("\nYou must play inside the board!\n");
            return 0;
        }
    }
    if(board[si][sj] == '.'){
        printf("\nNo piece there!\n");
        return 0;
    }
    if(getPiecePlayer(board[si][sj]) != playerToMove){
        printf("\nThis piece is not yours!\n");
        return 0;
    }
    if(!canReach(si, sj, di, dj)){
        return 0;
        printf("\nThis piece can't go there!\n");
    }
    if(!try(si, sj, di, dj)){
        printf("\nYou lose your king if you go there!\n");
        return 0;
    }
    
    board[di][dj] = board[si][sj];
    board[si][sj] = '.';
    promote(di, dj);

    return 1;
}

void printBoard(){
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

void populateBoard(){
    char row[8] = {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'};
    for(int i=0; i<8; i++){
        for(int j=2; j<6; j++){
            board[j][i] = '.';
        }
        board[0][i] = row[i];
        board[6][i] = 'P';
        board[1][i] = 'p';
        board[7][i] = row[i] - 32;
    }
}
