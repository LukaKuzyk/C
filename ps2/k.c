#include <stdlib.h>
#include <stdio.h>
#include "k.h"

void add_random_tile(struct game *game){
    int row, col;
    // find random, but empty tile
    do{
        row = rand() % SIZE;
        col = rand() % SIZE;
    }while(game->board[row][col] != ' ');

    // place to the random position 'A' or 'B' tile
    if(rand() % 2 == 0){
        game->board[row][col] = 'A';
    }else{
        game->board[row][col] = 'B';
    }
}

bool is_game_won(const struct game game){
    for(int row = 0; row < SIZE; row++){
        for(int col = 0; col < SIZE; col++){
            if(game.board[col][row] == 'K'){
                return true;
            }
        }
    }
    return false;
}

bool is_move_possible(const struct game game){
    short tile_empty = 0;
    short tile_two = 0;
    
    for(int row = 0; row < SIZE; row++){
        for(int col = 0; col < SIZE; col++){
            if(game.board[col][row] == ' '){
                tile_empty  = 1;
            }
        }
    }
    
    for(int row = 0; row < SIZE; row++){
        for(int col = 0; col < SIZE; col++){
            if(col+1<SIZE){
                if(game.board[col][row] == game.board[col+1][row]){
                    tile_two  = 1;
                    break;
                }
            }
            if(row+1<SIZE){
                if(game.board[col][row] == game.board[col][row+1]){
                    tile_two  = 1;
                    break;
                }
            }
        }
    }
    
    if(tile_empty == 1 || tile_two == 1){
//        printf("%d %d\n", tile_two, tile_empty);
        return  true;
    }
    if(tile_empty == 0 && tile_two == 0){
        return  false;
    }
    return 0;
}

/*  RULES
    A = 2; B = 4; ... K = 2048; A B C D E F G H I J K
    int dy - smer v osi Y, ktorý môže mať len jednu z troch hodnôt: -1, ak sa jedná o smer hore; 0, ak sa nejedná o zmenu smeru v y-ovej osi; 1, ak sa jedná o smer dolu. |
 
    int dx - smer v osi X, ktorý môže mať len jednu z troch hodnôt: -1, ak sa jedná o smer vľavo, 0, ak sa nejedná o zmenu smeru v x-ovej osi a 1, ak sa jedná o smer vpravo. -----
            y  x
    VPRAVO (0; 1) RIGHT
    VLAVO  (0;-1) LEFT
    HORE   (-1;0) UP
    DOLE   ( 1;0) DOWN
 */

bool update(struct game *game, int dy, int dx){
    short output = 0;
        if(dy == dx){
            return false;
        }
        if(dy != 0 && dx !=0){
            return false;
        }
    
    if(dy == 0 && dx == -1){ //     VLAVO  (0;-1) LEFT
        short ind = 0;
        do{
            for(short y = SIZE-1; y >=0;y--){ // left all
                for(short x = SIZE-1;x>=0;x--){
                    if(x-1>=0){
                        if(game->board[y][x] != ' ' && game->board[y][x-1] == ' '){
                            game->board[y][x-1] = game->board[y][x];
                            game->board[y][x] = ' ';
                            output = true;
                        }
                    }
                }
            }
            ind++;
        }while(ind<SIZE);
        
        for(short y = SIZE-1; y>=0;y--){ // clean double
            for(short x = 0;x<SIZE;x++){
                if(x+1<SIZE){
                if(game->board[y][x] == game->board[y][x+1] &&
                   game->board[y][x] != ' '){
                    if(game->board[y][x] == 'A'){
                        game->board[y][x] = 'B';
                        game->board[y][x+1] = ' ';
                        game->score +=4;
                    }
                    else if(game->board[y][x] == 'B'){
                        game->board[y][x] = 'C';
                        game->board[y][x+1] = ' ';
                        game->score +=8;
                    }
                    else if(game->board[y][x] == 'C'){
                        game->board[y][x] = 'D';
                        game->board[y][x+1] = ' ';
                        game->score +=16;
                    }
                    else if(game->board[y][x] == 'D'){
                        game->board[y][x] = 'E';
                        game->board[y][x+1] = ' ';
                        game->score +=32;
                    }
                    else if(game->board[y][x] == 'E'){
                        game->board[y][x] = 'F';
                        game->board[y][x+1] = ' ';
                        game->score +=64;
                    }
//                     A B C D E F G H I J K
                    else if(game->board[y][x] == 'F'){
                        game->board[y][x] = 'G';
                        game->board[y][x+1] = ' ';
                        game->score +=128;
                    }
                    else if(game->board[y][x] == 'G'){
                        game->board[y][x] = 'H';
                        game->board[y][x+1] = ' ';
                        game->score +=256;
                    }
                    else if(game->board[y][x] == 'H'){
                        game->board[y][x] = 'I';
                        game->board[y][x+1] = ' ';
                        game->score +=512;
                    }
                    else if(game->board[y][x] == 'I'){
                        game->board[y][x] = 'J';
                        game->board[y][x+1] = ' ';
                        game->score +=1024;
                    }
                    else if(game->board[y][x] == 'J'){
                        game->board[y][x] = 'K';
                        game->board[y][x+1] = ' ';
                        game->score +=2048;
                    }
                }
            }
            }
        }
        for(short y = SIZE-1; y >=0;y--){ // right all
            for(short x = SIZE-1;x>=0;x--){
                if(x-1>=0){
                    if(game->board[y][x] != ' ' && game->board[y][x-1] == ' '){
                        game->board[y][x-1] = game->board[y][x];
                        game->board[y][x] = ' ';
                    }
                }
            }
        }
    } // <---
    
    if(dy == 0 && dx == 1){ //  VPRAVO (0; 1) RIGHT
        short ind = 0;
        do{
            for(short y = 0; y < SIZE;y++){ // right all
                for(short x = 0;x<SIZE;x++){
                    if(x+1<SIZE){
                    if(game->board[y][x] != ' ' && game->board[y][x+1] == ' '){
                        game->board[y][x+1] = game->board[y][x];
                        game->board[y][x] = ' ';
                        output = true;
                    }
                    }
                }
            }
            ind++;
        }while(ind<SIZE);
        for(short y = 0; y<SIZE;y++){ // clean double
            for(short x = SIZE-1;x>=0;x--){
                if(x-1>=0){
                if(game->board[y][x] == game->board[y][x-1] &&
                   game->board[y][x] != ' '){
                    if(game->board[y][x] == 'A'){
                        game->board[y][x] = 'B';
                        game->board[y][x-1] = ' ';
                        game->score +=4;
                    }
                    else if(game->board[y][x] == 'B'){
                        game->board[y][x] = 'C';
                        game->board[y][x-1] = ' ';
                        game->score +=8;
                    }
                    else if(game->board[y][x] == 'C'){
                        game->board[y][x] = 'D';
                        game->board[y][x-1] = ' ';
                        game->score +=16;
                    }
                    else if(game->board[y][x] == 'D'){
                        game->board[y][x] = 'E';
                        game->board[y][x-1] = ' ';
                        game->score +=32;
                    }
                    else if(game->board[y][x] == 'E'){
                        game->board[y][x] = 'F';
                        game->board[y][x-1] = ' ';
                        game->score +=64;
                    }
//                     A B C D E F G H I J K
                    else if(game->board[y][x] == 'F'){
                        game->board[y][x] = 'G';
                        game->board[y][x-1] = ' ';
                        game->score +=128;
                    }
                    else if(game->board[y][x] == 'G'){
                        game->board[y][x] = 'H';
                        game->board[y][x-1] = ' ';
                        game->score +=256;
                    }
                    else if(game->board[y][x] == 'H'){
                        game->board[y][x] = 'I';
                        game->board[y][x-1] = ' ';
                        game->score +=512;
                    }
                    else if(game->board[y][x] == 'I'){
                        game->board[y][x] = 'J';
                        game->board[y][x-1] = ' ';
                        game->score +=1024;
                    }
                    else if(game->board[y][x] == 'J'){
                        game->board[y][x] = 'K';
                        game->board[y][x-1] = ' ';
                        game->score +=2048;
                    }
                }
            }
        }
        }

        for(short y = SIZE-1; y>=0;y--){ // right all
            for(short x = 0;x<SIZE;x++){
                if(x+1<SIZE){
                    if(game->board[y][x] != ' ' && game->board[y][x+1] == ' '){
                        game->board[y][x+1] = game->board[y][x];
                        game->board[y][x] = ' ';
                    }
                }
            }
        }
    } // --->
    
    if(dy == -1 && dx == 0){ //         HORE   (-1;0) UP
        short ind = 0;
        do{
            for(short y = SIZE-1; y >=0;y--){ // up all
                for(short x = SIZE-1;x>=0;x--){
                    if(y-1>=0){
                        if(game->board[y][x] != ' ' && game->board[y-1][x] == ' '){
                            game->board[y-1][x] = game->board[y][x];
                            game->board[y][x] = ' ';
                            output = true;
                        }
                    }
                }
            }
            ind++;
        }while(ind<SIZE);
        
        for(short y = 0; y<SIZE;y++){ // clean double
            for(short x = 0;x<SIZE;x++){
                if(y-1>=0){
                    if(game->board[y][x] == game->board[y-1][x] &&
                       game->board[y][x] != ' '){
                        if(game->board[y][x] == 'A'){
                            game->board[y][x] = 'B';
                            game->board[y-1][x] = ' ';
                            game->score +=4;
                        }
                        else if(game->board[y][x] == 'B'){
                            game->board[y][x] = 'C';
                            game->board[y-1][x] = ' ';
                            game->score +=8;
                        }
                        else if(game->board[y][x] == 'C'){
                            game->board[y][x] = 'D';
                            game->board[y-1][x] = ' ';
                            game->score +=16;
                        }
                        else if(game->board[y][x] == 'D'){
                            game->board[y][x] = 'E';
                            game->board[y-1][x] = ' ';
                            game->score +=32;
                        }
                        else if(game->board[y][x] == 'E'){
                            game->board[y][x] = 'F';
                            game->board[y-1][x] = ' ';
                            game->score +=64;
                        }
    //                     A B C D E F G H I J K
                        else if(game->board[y][x] == 'F'){
                            game->board[y][x] = 'G';
                            game->board[y-1][x] = ' ';
                            game->score +=128;
                        }
                        else if(game->board[y][x] == 'G'){
                            game->board[y][x] = 'H';
                            game->board[y-1][x] = ' ';
                            game->score +=256;
                        }
                        else if(game->board[y][x] == 'H'){
                            game->board[y][x] = 'I';
                            game->board[y-1][x] = ' ';
                            game->score +=512;
                        }
                        else if(game->board[y][x] == 'I'){
                            game->board[y][x] = 'J';
                            game->board[y-1][x] = ' ';
                            game->score +=1024;
                        }
                        else if(game->board[y][x] == 'J'){
                            game->board[y][x] = 'K';
                            game->board[y-1][x] = ' ';
                            game->score +=2048;
                        }
                    }
                }
            }
        }
        ind = 0;
        do{
            for(short y = SIZE-1; y >=0;y--){ // up all
                for(short x = SIZE-1;x>=0;x--){
                    if(y-1>=0){
                        if(game->board[y][x] != ' ' && game->board[y-1][x] == ' '){
                            game->board[y-1][x] = game->board[y][x];
                            game->board[y][x] = ' ';
                        }
                    }
                }
            }
            ind++;
        }while(ind<SIZE);
    }// up ^
    
    if(dy == 1 && dx == 0){ //     DOLE   ( 1;0) DOWN
        short ind = 0;
        do{
            for(short y = 0; y < SIZE;y++){ // down all
                for(short x = 0;x<SIZE;x++){
                    if(y+1<SIZE){
                        if(game->board[y][x] != ' ' && game->board[y+1][x] == ' '){
                            game->board[y+1][x] = game->board[y][x];
                            game->board[y][x] = ' ';
                            output = true;
                        }
                    }
                }
            }
            ind++;
        }while(ind<SIZE);
        
        for(short y = SIZE-1; y>=0;y--){ // clean double
            for(short x = 0;x<SIZE;x++){
                if(y+1<SIZE){
                    if(game->board[y][x] == game->board[y+1][x] &&
                       game->board[y][x] != ' '){
                        if(game->board[y][x] == 'A'){
                            game->board[y][x] = 'B';
                            game->board[y+1][x] = ' ';
                            game->score +=4;
                        }
                        else if(game->board[y][x] == 'B'){
                            game->board[y][x] = 'C';
                            game->board[y+1][x] = ' ';
                            game->score +=8;
                        }
                        else if(game->board[y][x] == 'C'){
                            game->board[y][x] = 'D';
                            game->board[y+1][x] = ' ';
                            game->score +=16;
                        }
                        else if(game->board[y][x] == 'D'){
                            game->board[y][x] = 'E';
                            game->board[y+1][x] = ' ';
                            game->score +=32;
                        }
                        else if(game->board[y][x] == 'E'){
                            game->board[y][x] = 'F';
                            game->board[y+1][x] = ' ';
                            game->score +=64;
                        }
    //                     A B C D E F G H I J K
                        else if(game->board[y][x] == 'F'){
                            game->board[y][x] = 'G';
                            game->board[y+1][x] = ' ';
                            game->score +=128;
                        }
                        else if(game->board[y][x] == 'G'){
                            game->board[y][x] = 'H';
                            game->board[y+1][x] = ' ';
                            game->score +=256;
                        }
                        else if(game->board[y][x] == 'H'){
                            game->board[y][x] = 'I';
                            game->board[y+1][x] = ' ';
                            game->score +=512;
                        }
                        else if(game->board[y][x] == 'I'){
                            game->board[y][x] = 'J';
                            game->board[y+1][x] = ' ';
                            game->score +=1024;
                        }
                        else if(game->board[y][x] == 'J'){
                            game->board[y][x] = 'K';
                            game->board[y+1][x] = ' ';
                            game->score +=2048;
                        }
                    }
            }
            }
        }
        ind = 0;
        do{
        for(short y = 0; y < SIZE;y++){ // down all
            for(short x = 0;x<SIZE;x++){
                if(y+1<SIZE){
                    if(game->board[y][x] != ' ' && game->board[y+1][x] == ' '){
                        game->board[y+1][x] = game->board[y][x];
                        game->board[y][x] = ' ';
                    }
                }
            }
        }
        ind++;
        }while(ind<SIZE);
    }// down
    
    return output;
}
