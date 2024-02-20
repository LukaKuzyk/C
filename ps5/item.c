#define error return 0
#include "item.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct item* create_item(char* name, char* description, unsigned int properties){
    if(name == NULL || description == NULL || strlen(name) == 0 || strlen(description) == 0){
        fprintf(stderr, "Empty input.\n");
        error;
    }
    
    struct item * output = (struct item*)calloc(1,sizeof(struct item));
    output->name = calloc(1,strlen(name)+1);
    // memcpy(output->name, name, strlen(name));
    strcpy(output->name, name);
    output->properties = properties;

    output->description = calloc(1,strlen(description)+1);
//    memcpy(output->description, description, strlen(description)+1);
    strcpy(output->description, description);
    
    return output;
}

struct item* destroy_item(struct item* item){
    free(item->name);
    free(item->description);
    free(item);
    error;
}
