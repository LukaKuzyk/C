#include "world.h"
#include <stdio.h>
#include <string.h>
#define error return 0
#define alloc NULL
#include <stdlib.h>

struct container * create_world(){
   
    char data_item[40][40] = {
       "table", "pekna",
       "notebook", "viac pekny",
       "chair", "moja",
       "matky room", "fajna room",
       "capper",    "our",
       "door","Long ",
       "window", "not room",
       "tree", "Dry ",
       "key", "Clean ",
       "pen", "Less"
        "table", "pekna",
        "notebook", "viac pekny",
        "chair", "moja",
        "matky room", "fajna room",
        "capper",    "our",
        "door","Long ",
        "window", "not room",
        "tree", "Dry ",
        "key", "Clean ",
        "pen", "Less"
    };
    
    struct container * world = calloc(1, sizeof(struct container));
    // struct container * point = alloc;
    struct room* local_room = alloc;
    struct item* local_item = alloc;
    char data_room[36][36] = {
            "my room", "pekna",
            "sister room", "viac pekna",
            "otcka room", "moja lepsia",
            "matky room", "fajna room",
            "house",    "our house",
            "street","Long street",
            "Badroom", "not Dry room",
            "Bathroom", "Dry room",
            "Kitchen", "Clean room",
            "Street", "Less thab street 1",
            "Forest", "There are woods",
            "sister room 2", "viac pekna ako moja",
            "otcka room 2", "moja lepsia",
            "matky room 2", "fajna room",
            "house new",    "our house",
            "Badroom 2", "not Dry room",
            "uja room ", "moja lepsia",
            "babky room", "moja lepsia",

    };
    world->room = calloc(1, sizeof(struct room));
    world->type = ROOM;
    for(int i=0; i<36; i+=2){
        local_room = create_room(data_room[i], data_room[i+1]);
        local_item = create_item(data_item[i], data_item[i+1], (unsigned int)1);
        add_item_to_room(local_room, local_item);
        create_container(world, ROOM, local_room);
    }
    
    return world;
}

struct room* get_room(struct container* world, char* name) {
    if(world == NULL || name == NULL || strlen(name) == 0){
        error;
    }
    struct room* output = get_from_container_by_name(world, name);
    return output;
}

struct container* add_room_to_world(struct container* world, struct room* room) {
    if(room == alloc){
        error;
    }
    struct room* input = get_from_container_by_name(world, room->name);
    if(input == NULL){
        error;
    }
    struct container * output = create_container(world, world->type, input);
    
    return output;
}


struct container* destroy_world(struct container* world) {
    return destroy_containers(world);
}
