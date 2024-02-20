#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hof.h"

//int write_number(int number, char numb[]);


int comp(const void *i, const void *j){
    const struct player *a = i;
    const struct player *b = j;
    return b->score - a->score;
}

bool save(const struct player list[], const int size){
    FILE *score = fopen(HOF_FILE, "w");
    short i = 0;
    while (i < size) {
        fprintf(score, "%s ", list[i].name);
        fprintf(score, "%d\n", list[i].score);
        i++;
    }
    fclose(score);
    return true;
}

int load(struct player list[]){
    FILE *fp = fopen(HOF_FILE, "rb");
    if(fp == NULL){
        return -1;
    }
    int output = 0;
    char text_check[1000];
    fread(text_check, sizeof(text_check), 1, fp);
    size_t text_check_length = strlen(text_check);
    short eol = 0;
    size_t check = 0;
    for(size_t i = 0; i<text_check_length;i++){
        if(text_check[i] == '\n'){
            eol++;
            check++;
        }
    }
    rewind(fp);
    if(eol >10){
        eol = 10;
    }
    if(eol < 1){
        fclose(fp);
//        printf("end");
        return 0;
    }
    for(short i = 0;i<eol;i++){
        output = i+1;
    fscanf(fp, "%s %d", list[i].name,&list[i].score);
    }
    qsort(list, check, sizeof(struct player), comp);
    fclose(fp);
    return output;
}


bool add_player(struct player list[], int *size, const struct player player){
    for(int dx = *size - 1; dx != -1; dx--){
        for(int dy = dx - 1; dy != -1; dy--){
            if(list[dx].score > list[dy].score){
                struct player tmp = list[dx];
                list[dx] = list[dy];
                list[dy] = tmp;
            }
        }
    }

    if(*size == 0){
        list[0] = player;
        *size+=1;
        return true;
    }

    if(*size == 10){
        if (player.score < list[9].score) {
//            printf("tut end");
            return false;
        }
        else{
            list[*size-=1] = player;
//            printf("tut\n");
        }
    }

    if(*size < 10){
        list[*size] = player;
        *size+=1;
//        printf("tut");
    }
    for(int i = *size - 1; i != -1; i--){
        int j = i - 1;
        if(j >= 0 && list[i].score >= list[j].score){
            struct player tmp = list[i];
            list[i] = list[j];
            list[j] = tmp;
        }
    }
    return true;
}
//int load(struct player list[]){
//    int output = false;
//    char text_check[1000];
//    char text[1000];
//    char numb[10];
//    int num = 0;
//
//    FILE *fp = fopen(HOF_FILE, "rb");
//    if(fp == NULL){
//        return -1;
//    }
//    fread(text_check, sizeof(text_check), 1, fp);
//    size_t text_check_length = strlen(text_check);
////    printf("%s...%zu\n",text_check,text_check_length);
//    short eol = 0;
//    for(size_t i = 0; i<text_check_length;i++){
//        if(text_check[i] == '\n'){
//            eol++;
//        }
//    }
////    printf("eol:%d\n",eol);
//
//    FILE *score = fopen(HOF_FILE, "r");
//    if(score == NULL){
//        return -1;
//    }
//    size_t limit = 0;
//    for(short l =0;l<eol;l++){
//        limit++;
//    }
//    if(limit>10){
//        limit = 10;
//    }
//    for(size_t j = 0; j<limit;j++){
//        short turn = 0;
//        fgets(text, 100, score);// put from line in score
//        size_t text_length = strlen(text);
////        printf("%zu text:%s", j+1 , text);
//        for(short i = 0, n =0; i<text_length;i++){
//            if(text[i] == ' '){ // delimiter
//                turn = 1;
//                continue;
//            }
//            if(turn == 0){
//                list[j].name[i] = text[i];
////                printf("%c %c \n", list[j].name[i], text[i]);
//                list[j].name[i+1] = '\0';
//            }else{
//                if(text[i] >=48 && text[i] <=57){
//                numb[n] = text[i];
//                n++;
//                numb[n] = '\0';
//                }
//            }
//        }
//        int res_num = write_number(num,numb);
//        list[j].score = res_num;
////        printf("FILE:%s\n", list[j].name);
//    }
//    fclose(fp);
//    fclose(score);
//    output = eol;
////    printf("output:%d\n",output);
//    return output;
//}

//int write_number(int number, char numb[]){
//    size_t numb_length = strlen(numb);
//
//    for(size_t i = numb_length-1; i>=0; i--){
//        char num = 0;
//        if(numb[i]=='1'){
//            num = 1;
//        }
//        if(numb[i]=='2'){
//            num = 2;
//        }
//        if(numb[i]=='3'){
//            num = 3;
//        }
//        if(numb[i]=='4'){
//            num = 4;
//        }
//        if(numb[i]=='5'){
//            num = 5;
//        }
//        if(numb[i]=='6'){
//            num = 6;
//        }
//        if(numb[i]=='7'){
//            num = 7;
//        }
//        if(numb[i]=='8'){
//            num = 8;
//        }
//        if(numb[i]=='9'){
//            num = 9;
//        }
//        if(numb[i]=='0'){
//            num = 0;
//        }
//
//
//        if(numb_length==4){
//            if(i == 3){
//                number+=num;
//            }
//            if(i == 2){
//                number+=(num*10);
//            }
//            if(i == 1){
//                number+=(num*100);
//            }
//            if(i == 0){
//                number+=(num*1000);
//            }
//        }
//        if(numb_length==3){
//            if(i == 2){
//                number+=num;
//            }
//            if(i == 1){
//                number+=(num*10);
//            }
//            if(i == 0){
//                number+=(num*100);
//            }
//        }
//        if(numb_length==2){
//            if(i == 1){
//                number+=num;
//            }
//            if(i == 0){
//                number+=(num*10);
//            }
//        }
//        if(numb_length==1){
//            if(i == 0){
//                number+=num;
//            }
//        }
//
//    }
////    printf("%d NUM:%d\n", numb_length,number);
//    return number;
//}
