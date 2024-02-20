#include <stdio.h>
#define error return 0
#define empty NULL
// #define alloc NULL
#define out return
#include <string.h>
#include <stdlib.h>
#include "game.h"

struct game* create_game(){
    struct game * point = calloc(1,sizeof(struct game));
    struct room * room = create_room("Room", "my Big room");
    point->state = PLAYING;
    point->world = create_container(point->world, ROOM, room);;
    point->backpack = create_backpack(30);
    point->parser = create_parser();
    point->current_room = point->world->room;
    out point;
}

struct game* destroy_game(struct game* game){
    if(game == empty){
        error;
    }
    if(game->backpack != empty){
        game->backpack = destroy_backpack(game->backpack);
    }
    if(game->world != empty){
        game->world = destroy_containers(game->world);
    }
    if(game->parser != empty){
        game->parser = destroy_parser(game->parser);
    }
    free(game);
    error;
}

