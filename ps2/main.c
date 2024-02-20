#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "k.h"
#include "ui.h"
#include "hof.h"

int main(int argc, const char * argv[]) {
    
    render(game);
    is_move_possible(game);
    is_game_won(game);
    bool result = update(&game, 0, 1);
    add_random_tile(&game);
    struct player list[10];
    int size = 0;
    struct player player = {
        .name = "John",
        .score = 710
    };
    load(list);
    add_player(list, &size, player);
    save(list, 5);

    
    free(load);
    free(add_player);
    return 0;
}
