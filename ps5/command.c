#include "command.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define error return 0

struct command* create_command(char* name, char* description, char* pattern, size_t nmatch){
    
    if(strlen(name) == 0 || name == NULL || description == NULL || strlen(description) == 0 || pattern == NULL || strlen(pattern)== 0 ){
        error;
    }
    
    struct command * output = (struct command *) calloc(1, sizeof(struct command));
    output->name = calloc(1, strlen(name)+1);
    output->description = calloc(1, strlen(description)+1);
    output->nmatch = nmatch;
    // strcpy(output->name, name);
    // strcpy(output->description, description);
    output->name = name;
    output->description = description;
    if(pattern != NULL){
        regcomp(&output->preg, pattern, REG_ICASE);
    }

    return output;
}

struct command* destroy_command(struct command* command) {

    regfree(&command->preg);
    free(command->name);
    free(command->description);
    free(command);

    error;
}
