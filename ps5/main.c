#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "backpack.h"
#include "world.h"
#include "room.h"
#include "parser.h"
#include "item.h"
#include "game.h"
#include "command.h"
#include "container.h"

//void print_container(struct container *first);

int main(int argc, const char * argv[]) {
    struct container *first = create_container(0, TEXT, "Hello one");
    destroy_containers(first);
    struct item* entry = create_item("LANO", "Pouzitelne na dostanie sa von z hradu.", USABLE);  
    remove_container(first, entry);
    create_container(first, ITEM, entry);
    get_from_container_by_name(first, "LANO");
    destroy_item(entry);
    struct room * room =create_room("room", "Pouzitelne na dostanie sa von z hradu.");
    destroy_room(room);
    struct command * comm = create_command("first","start game",0,0);
    destroy_command(comm);
    delete_item_from_room(room, NULL);
    add_item_to_room(room, NULL);
    get_item_from_room(room, "ivan");
    set_exits_from_room(room, NULL,NULL,NULL,NULL);
    create_backpack(1);
    create_world();
    destroy_backpack(NULL);
    add_item_to_backpack(NULL, NULL);
    delete_item_from_backpack(NULL, NULL);
    get_item_from_backpack(NULL, "ITEM");
    create_parser();
    destroy_parser(NULL);
    // parse_input(NULL, "hopa");
    create_game();
    destroy_game(NULL);
    destroy_world(NULL);
    add_room_to_world(NULL,NULL);
    get_room(NULL, NULL);
    return 0;
}

//void print_container(struct container *first){
//    switch(first->type){
//        case TEXT:
//            printf("TYPE: TEXT\n");
//            printf("Enter: %s\n",first->text);
//            break;
//        case ITEM:
//            printf("TYPE: ITEM\n");
//            printf("Item name: %s\n",first->item->name);
//            break;
//        case ROOM:
//            printf("TYPE: ROOM\n");
//            printf("Room name: %s\n",first->room->name);
//            break;
//        case COMMAND:
//            printf("TYPE: COMMAND\n");
//            printf("Command name: %s\n",first->command->name);
//            break;
//    }
//
//    printf("\n");
//}
