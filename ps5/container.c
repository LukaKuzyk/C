#define error return 0
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "container.h"

struct container* create_container(struct container* first, enum container_type type, void* entry){
    if(entry == NULL || strlen(entry) == 0 ){
        fprintf(stderr, "Epmty entry. (create container)\n");
        error;
    }
    if(first != NULL && first->type != type){
        fprintf(stderr, "Type problem. \n");
        error;
    }
    struct container *result = (struct container*)calloc(1,sizeof(struct container));
    result->type = type;
    result->next = NULL;
    switch(type){
        case TEXT:
            result->text=calloc(1,strlen(entry)+1);
//            strcpy(result->text, entry);
            result->text = entry;
            break;
        case ITEM:
           result->item=calloc(1,sizeof(struct item));
//            memcpy(result->item, entry, sizeof(struct item));
            result->item = entry;
            break;
        case ROOM:
           result->room=calloc(1,sizeof(struct room));
//            memcpy(result->room, entry, sizeof(struct room));
            result->room = entry;
            break;
        case COMMAND:
           result->command=calloc(1,sizeof(struct command));
//            memcpy(result->command, entry, sizeof(struct command));
            result->command = entry;
            break;
    }
    if(first == NULL){
    first = result;
    }else{
        while(first->next != NULL){
        first=first->next;
        }
        first->next = result;
    }
    return result;
}

struct container* destroy_containers(struct container* first){
    if(first == NULL){
        error;
    }
    struct container * point = first;
    // memcpy(point, first, sizeof(struct container));
    
    while(point->next != NULL){
        
        switch (first->type) {
            case ROOM:
                first->room = destroy_room(first->room);
                break;
            case ITEM:
                first->item = destroy_item(first->item);
                break;
            case COMMAND:
                first->command = destroy_command(first->command);
                break;
            case TEXT:
                free(first->text);
                break;
        }
        // first = NULL;
        point = point->next;
        first = point;
        free(first);
    }
    return 0;
}

struct container* remove_container(struct container *first, void *entry){
    if(entry == NULL || first == NULL){
       return first;
    }


    struct container * cont = first, * point = first;
    struct container * prev = calloc(1, sizeof(struct container));

    int index = 0;
    
    while(point != NULL){
        
        cont = point;
        
        switch(first->type){
            case ITEM:
                if(memcmp(cont->item, entry, sizeof(struct item)) == 0)
                    index = 1;
    
                break;
                
            case ROOM:
                if(memcmp(cont->room, entry, sizeof(struct room)) == 0)
                    index = 1;
                
                break;
                
            case COMMAND:
                if(memcmp(cont->command, entry, sizeof(struct command)) == 0)
                    index = 1;
                
                break;
                
            case TEXT:
                if(memcmp(cont->text, entry, strlen(entry)) == 0)
                    index = 1;
                
                break;
        }
        
        if(index == 0){
            point = cont->next;
            prev = cont;
        }else{
            if(prev != NULL)
                prev->next = cont->next;
            else
                first = point->next;
            
            break;
        }
    }
    return first;
}


void* get_from_container_by_name(struct container *first, const char *name){
    if( name == NULL || first == NULL ||strlen(name) == 0){
        fprintf(stderr, "Epmty entry. (get from container by name)\n");
        error;
    }
    
    
    // struct container * point = calloc(1, sizeof(struct container));
    struct container * point = first;
    struct container * output = calloc(1, sizeof(struct container));

    
    // memcpy(point, first, sizeof(struct container));
    char* search = calloc(1,strlen(name)+1);

    
    switch(first->type){
        case ITEM:

            // point->item = calloc(1, sizeof(struct item));
            output->item = calloc(1, sizeof(struct item));
            // memcpy(point->item, first->item, sizeof(struct item));
            point->item = first->item;

            while(search != name && point != NULL){

                search = point->item->name;
                point=point->next;
                if(point != NULL){
                // memcpy(output->item, point->item, sizeof(struct item));
                output->item = point->item;
                }
            }
        break;
        case ROOM:
            
            // point->room = calloc(1, sizeof(struct room));
            output->room = calloc(1, sizeof(struct room));
            // memcpy(point->room, first->room, sizeof(struct room));
            point->room = first->room;

            while(search != name && point != NULL){

                search = point->room->name;
                point=point->next;
                if(point != NULL){
                // memcpy(output->room, point->room, sizeof(struct room));
                output->room = point->room;
                }
            }
        break;
            
        case COMMAND:
            
            // point->command = calloc(1, sizeof(struct command));
            output->command = calloc(1, sizeof(struct command));
            // memcpy(point->command, first->command, sizeof(struct command));
            point->command = first->command;
            while(search != name && point != NULL){

                search = point->command->name;
                point=point->next;
                if(point != NULL){
                // memcpy(output->command, point->command, sizeof(struct command));
                output->command = point->command;
                }
            }
            break;
        case TEXT:
            
            // point->text = calloc(1, strlen(first->text));
            output->text = calloc(1, strlen(first->text));
            // memcpy(point->text, first->text, strlen(first->text));
            point->text = first->text;

            while(search != name && point != NULL){

                search = point->text;
                point=point->next;
                if(point != NULL){
//                memcpy(output->text, point->text, strlen(point->text));
                    strcpy(output->text, point->text);
                }
            }
            
            break;
    }
    // free(point);
    return output;
}
