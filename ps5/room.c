#include <stdio.h>
#include "room.h"
#include <string.h>
#define error return 0
#include <stdlib.h>

struct room* create_room(char *name, char *description){
    
    if(name == NULL || description == NULL || strlen(name) == 0 || strlen(description) == 0){
        fprintf(stderr, "Empty input.\n");
        error;
    }
    
    struct room * output = (struct room*)calloc(1,sizeof(struct room));
    output->name = calloc(1,strlen(name)+1);
    strcpy(output->name, name);

    output->description = calloc(1,strlen(description)+1);
    strcpy(output->description, description);
    
    
    return output;
}

struct room* destroy_room(struct room* room){
    free(room->name);
    free(room->description);
    free(room);
    error;
}

struct item* get_item_from_room(const struct room* room, const char* name){
    if(room == NULL || name == NULL){
        fprintf(stderr, "Error input\n");
        error;
    }
    struct item* output = get_from_container_by_name(room->items, name);
    
    if (output == NULL)
        error;
    
    return output;
}


void delete_item_from_room(struct room* room, struct item* item){
    if(room == NULL || item == NULL)
        return;
    
    // const struct room* point = (struct room*) calloc(1, sizeof(struct room));
    // memcpy(point, room, sizeof(struct room));
    
    struct container* container = remove_container(room->items, item);
    
    room->items = container;
}

void add_item_to_room(struct room* room, struct item* item){
    if(room == NULL || item == NULL){
        return;
    }

    // struct room* point = (struct room*) calloc(1, sizeof(struct room));
    // memcpy(point, room, sizeof(struct room));
    
    struct container* container = create_container(room->items, ITEM, item);
    
    // if(point->items == NULL){
        room->items = container;
    // }
}


void set_exits_from_room(struct room *room, struct room *north, struct room *south, struct room *east, struct room *west){
    if(room == NULL){
        return;
    }
    
    room->north = north;
    room->south = south;
    room->east = east;
    room->west = west;

}
