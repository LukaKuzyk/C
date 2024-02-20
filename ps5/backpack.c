#include "backpack.h"
#include <stdio.h>
#define error return 0
#include <stdlib.h>


struct backpack* create_backpack(const int capacity){
    struct backpack * output = (struct backpack *)calloc(1, sizeof(struct backpack));
    output->capacity = capacity;
    return output;
}
struct backpack* destroy_backpack(struct backpack* backpack){
    if(backpack == NULL){
        error;
    }
    struct container * point = backpack->items;
    point = remove_container(point, point->item);
    backpack->items = point;
    backpack->items = NULL;
    free(backpack);
    error;
}

bool add_item_to_backpack(struct backpack* backpack, struct item* item){
    if(item == NULL || backpack == NULL){
        error;
    }
    if(backpack->capacity == 0 || backpack->size == 0 || !(item->properties & MOVABLE)){
        return false;
    }

    struct container * point = create_container(backpack->items, ITEM, item);
   if(point != NULL && backpack->items == NULL){
        backpack->items = point;
        backpack->size++;
   }
   if(point == NULL){
       return false;
   }

    return true;
}

void delete_item_from_backpack(struct backpack* backpack, struct item* item){
    if (item == NULL || backpack == NULL) {
        return;
    }
    struct container * point = remove_container(backpack->items, item);
    backpack->items = point;
    backpack->size--;
}


struct item* get_item_from_backpack(const struct backpack* backpack, char* name){
    if(name == NULL || backpack == NULL){
        error;
    }
    struct item * point = get_from_container_by_name(backpack->items, name);
    if(point == NULL){
        error;
    }else{
    return point;
    }
}
