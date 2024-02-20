#include "parser.h"
#include <stdio.h>
#define error return 0
#define alloc NULL
#define out return
#include <string.h>
#include <stdlib.h>

struct parser* create_parser(){
        short size = 17;
    char * data_command[17]={ "KONIEC",
                                "SEVER",
                                "JUH",
                                "VYCHOD",
                                "ZAPAD",
                                "ROZHLIADNI SA",
                                "PRIKAZY",
                                "VERZIA",
                                "RESTART",
                                "O HRE",
                                "VEZMI",
                                "POLOZ",
                                "INVENTAR",
                                "POUZI",
                                "PRESKUMAJ"
                                "NAHRAJ"
                                "ULOZ"
    };

    char * data_patterns[17]={"KONIEC",
                                "SEVER",
                                "JUH",
                                "VYCHOD",
                                "ZAPAD",
                                "(ROZHLADNI SA)",
                                "(PRIKAZY)",
                                "(VERZIA)",
                                "RESTART",
                                "(O HRE)",
                                "(VEZMI)",
                                "(POLOZ)",
                                "(INVENTAR)",
                                "(POUZI)",
                                "(PRESKUMAJ)",
                                "(NAHRAJ)",
                                "(ULOZ)"
    };
    // struct container * point = alloc;
    struct parser * output = calloc(1,sizeof(struct parser));
    struct command * point_c = alloc;
    for(short i=0; i<size; i++){
        point_c = create_command(data_command[i], "Command to use", data_patterns[i], 1);
        create_container(output->commands, COMMAND, point_c);
    }
//    output->commands = point;
    out output;
}

struct parser* destroy_parser(struct parser* parser){
    if(parser == NULL){
        error;
    }
    parser->history = destroy_containers(parser->history);
    parser->commands = destroy_containers(parser->commands);
    free(parser);
    error;
}
