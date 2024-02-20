#include "playfair.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define nol = 0;

char* playfair_encrypt(const char* key, const char* text){
    if(text == NULL){
        return nol;
    }
    short text_length22 = strlen(text);
    if(text_length22 <= 0){
        return 0;
    }
    if(key == NULL){
        return 0;
    }
    short key_length22 = strlen(key);
    if(key_length22 <= 0){
        return 0;
    }
    // create matrix 5x5
    char key_matrix[5][5];
    char input_words[25]; // WORDS into Matrix (key+abc(without double and key`s words));
    short key_size = strlen(key);
    char key_clean[key_size]; // string with all BIG WORDS
    char key_clean_double[key_size]; // string with key`s words wihout double
    char key_clean_double_FIX[key_size]; //FIX BUGS
    char key_clean_double_2FIX[key_size]; //FIX BUGS #2
    char key_abc[]={"ABCDEFGHIJKLMNOPQRSTUVXYZ"}; // LOSE 'W';  W == V. world = vorld;
    char key_abc_dirty[]={"ABCDEFGHIJKLMNOPQRSTUVXYZ"};// удаляєм отсюда, delete used words
    char key_abc_clean[25-key_size];// CLEAN ABC, READY TO USE IN MATRIX
    // arena bug fix
        for(int p = 0;p<1;p++){
            short q = key_clean_double_2FIX[0];
            q++;
            q=0;
        }
    
    // LESS to BIG word
    for(short i = 0; i<key_size;i++){
        char word = key[i];
        if(word == 119 || key[i] == 87){
            word = 86;
        }
        if(word<=122 && word>=97){
            word -= 32;
            key_clean[i] = word;
            key_clean[i+1] = '\0';
        }else{
            key_clean[i] = word;
            key_clean[i+1] = '\0';
        }
//        printf("%c\n",word);
    }//for
    for(short i = 0;i<key_size;i++){
       char check = key_clean[i];
       if(check <65 || check >90){
           return 0;
       }
   }
//    printf("key:'%s' text:'%s'\n", key, text);
    
    // DELETE DUBLIKATs from KEY_CLEAN AND ABCd
    
    for(short i = 0, index1 =0, index2=-1; i <25;i++){
        if(key_abc[i] == key_clean[index1]){
//            printf("%d LETTER is %c\n", index1,key_abc_dirty[i]);
            if(key_clean_double[index2] != '_'){
                index2++;
            }
            key_clean_double[index2]=key_abc_dirty[i];
            key_clean_double[index2+1]='\0';
            key_abc_dirty[i] = '_';
            index1++;
        }
            // FIX BUG z A a Z
            if(i==24 && index1<=key_size){
                i=-1;
            }
            if(index1 >= key_size){
                break;
            }
            //
    }
    
    // DOUBLE FIX
    short a11=0;
    for(short i =0, a=0;i<key_size;i++){
        if(key_clean_double[i] != '_'){
            key_clean_double_FIX[a] = key_clean_double[i];
            key_clean_double_2FIX[a11] = key_clean_double_FIX[a];
            a11++;
            a++;
            key_clean_double_FIX[a] = '\0';
        }
    }
    short l_kcdF = strlen(key_clean_double_FIX);

    //**CHECKER-MARKER
//    printf("Key_clean_double:%s\n", key_clean_double);
//    printf("Key_clean_double_FIX: %d\n%s\n\n",l_kcdF, key_clean_double_FIX);
//    printf("DIRTY abc:%s\n", key_abc_dirty);
    //*
    
    // ABC_CLEANER from '_'
    for(short i = 0, a=0; i<25; i++){
        if(key_abc_dirty[i] != '_'){
            key_abc_clean[a] = key_abc_dirty[i];
            a++;
            key_abc_clean[a] = '\0';
        }
    }
//    short l_kad = strlen(key_abc_clean);
//    printf("CLEAN abc: %d\n%s\n\n",l_kad, key_abc_clean);

    //WORDS into Matrix
//    printf("2Key_clean_double_2FIX: %d\n%s\n\n",l_kcdF, key_clean_double_FIX);

    for(short i =0;i<l_kcdF; i++){
        input_words[i]=key_clean_double_FIX[i];
//        printf("%d a %c = %c\n", i+1,input_words[i], key_clean_double_FIX[i]);

    }
    
    for(short i = 0,a=0,b=0; i<25;i++){
        if(i<l_kcdF){
            input_words[i] = key_clean_double_FIX[a];
//            printf("%d  %d  %c\n", i+1,a,input_words[i]);
            a++;
        }
        if(i>=l_kcdF){
            input_words[i] = key_abc_clean[b];
//            printf("%d  %d  %c\n",i+1, b,input_words[i]);
            b++;
        }
    }
//    printf("INPUT  -->%s<--\n",input_words);
    // MATRIX
    
    for(short x = 0, i =0 ; x<5;x++){
        for(short y = 0; y<5;y++){
            key_matrix[x][y] = input_words[i];
            i++;
        }
    }
    // printf("\n");

    //IMAGE MATRIX
    for(short x = 0;x<5;x++){
        for(short y = 0; y<5;y++){
             printf("| %c |", key_matrix[x][y]);
        }
         printf("\n");
    }
    
    // Work with *text
    
    short length_text = strlen(text);
    char text_clean[length_text];
    char text_clean2[length_text*2];

    
    for(short i = 0, j = 0; i<length_text; i++){
        char word = text[i];
        if(word == ' '){
            continue;
        }
        if(word == 119 || text[i] == 87){
            word = 86;
        }
        if(word<=122 && word>=97){
            word -= 32;
            text_clean[j] = word;
            j++;
            text_clean[j] = '\0';
        }else{
            text_clean[j] = word;
            j++;
            text_clean[j] = '\0';
        }
    }
    for(short i = 0;i<length_text;i++){
       char check = text_clean[i];
       if(check <65 && check >90){
           return 0;
       }
   }
    
    printf("%d %s\n", length_text, text_clean);

    for(short i = 0, j = 0; i<length_text*2;i++){

        if(text_clean[i] == 'X' && text_clean[i+1] == 'X'){
            text_clean2[j] = text_clean[i];
            j++;
            i++;
            text_clean2[j] = text_clean[i];
            j++;
            i++;
        }
        if(text_clean[i] == text_clean[i+1] && text_clean[i] == text_clean[i+2]){
            text_clean2[j] = text_clean[i];//1
            j++;
            i++;
            text_clean2[j] = text_clean[i];//2
            j++;
            i++;
            text_clean2[j] = 'X';
            j++;
            text_clean2[j] = text_clean[i];
        }
        if(text_clean[i] != text_clean[i+1]){
            text_clean2[j] = text_clean[i];
//            printf("%d %c\n", j, text_clean2[j]);
            j++;
            text_clean2[j] = '\0';
        }
        if(text_clean[i] == text_clean[i+1] && text_clean[i] != 'X'){
            text_clean2[j] = text_clean[i];
            j++;
            text_clean2[j] = 'X';
            j++;
            text_clean2[j] = '\0';
        }
    }
    printf("%d %s\n", length_text, text_clean2);

    short length_clean2 = strlen(text_clean2);
//    printf("length_clean2 %d\n", length_clean2);
    if(length_clean2 %2 != 0){
        text_clean2[length_clean2] = 'X';
        text_clean2[length_clean2+1] = '\0';
    }
//    printf(" %s\n\n", text);
    // printf("\n%s\n\n", text_clean2);
    
    // ENCRYPTING
    
    char output[length_clean2];
    
    for(short i=0, a=-1;i<length_clean2; i+=2){
        char word1 = text_clean2[i];
        char word2 = text_clean2[i+1];
        char find_word1= 0;
        char find_word2= 0;
        char ready_word1=0;
        char ready_word2=0;
        short x1 =0, y1=0, x2=0, y2 = 0;
         printf("%c%c", word1, word2);
        // find word in matxrix = coordination
        while(find_word1 != word1){
            find_word1 = key_matrix[x1][y1];
            if(find_word1 == word1){
                break;
            }else{
                x1++;
            }
            if(x1 == 5){
                y1++;
                x1=0;
            }
        }
        while(find_word2 != word2){
            find_word2 =key_matrix[x2][y2];
            if(find_word2 == word2){
                break;
            }else{
                x2++;
            }
            if(x2==5){
                y2++;
                x2=0;
            }
        }
        // rules, riadky a stlpce
        if(x1 != x2 && y1 != y2){
        ready_word1 = key_matrix[x1][y2];
        ready_word2 = key_matrix[x2][y1];
        }
        if(x1 == x2 && y1 == y2){
            if(x1==4){
            x1=0;
            }else{
                x1++;
            }
            if(x2==4){
                x2=0;
            }else{
                x2++;
            }
            ready_word1 = key_matrix[x1][y2];
            ready_word2 = key_matrix[x2][y1];
        }else if(x1 == x2){ // right
            if(y1==4){
                y1=0;
            }else{
                y1++;
            }
            if(y2==4){
                y2=0;
            }else{
                y2++;
            }
            // EDITING
            ready_word1 = key_matrix[x2][y1];
            ready_word2 = key_matrix[x1][y2];
//            ready_word1 = key_matrix[x1][y2];
//            ready_word2 = key_matrix[x2][y1];

        }else if(y1 == y2){ // down
            if(x1==4){
            x1=0;
            }else{
                x1++;
            }
            if(x2==4){
                x2=0;
            }else{
                x2++;
            }
            ready_word1 = key_matrix[x1][y2];
            ready_word2 = key_matrix[x2][y1];
        }
         printf(" = %c%c", find_word1, find_word2);
         printf(" = %d %d  %d %d", x1+1, y1+1, x2+1, y2);
         printf(" = %c%c\n", ready_word1, ready_word2);
        if(a==-1){
        a++;
        output[a]= ready_word1;
        a++;
        output[a]= ready_word2;
            continue;
        }
        a++;
        output[a]= ' ';
        a++;
        output[a]= ready_word1;
        a++;
        output[a]= ready_word2;
        output[a+1] = '\0';
        
    }

    char *result = (char*) calloc(strlen(output)+1, sizeof(char));
    strcpy(result, output);
    return result;
}



char* playfair_decrypt(const char* key, const char* text){
    if(text == NULL){
        return 0;
    }
    short text_length22 = strlen(text);
    if(text_length22 == 0){
        return 0;
    }
    if(key == NULL){
        return 0;
    }
    short key_length22 = strlen(key);
    if(key_length22 == 0){
        return 0;
    }
    char key_matrix[5][5];
    char input_words[25]; // WORDS into Matrix (key+abc(without double and key`s words));
    short key_size = strlen(key);
    char key_clean[key_size]; // string with all BIG WORDS
    char key_clean_double[key_size]; // string with key`s words wihout double
    char key_clean_double_FIX[key_size]; //FIX BUGS
    char key_clean_double_2FIX[key_size]; //FIX BUGS #2
    char key_abc[]={"ABCDEFGHIJKLMNOPQRSTUVXYZ"}; // LOSE 'W';  W == V. world = vorld;
    char key_abc_dirty[]={"ABCDEFGHIJKLMNOPQRSTUVXYZ"};// удаляєм отсюда, delete used words
    char key_abc_clean[25-key_size];// CLEAN ABC, READY TO USE IN MATRIX
    // arena bug fix
        for(int p = 0;p<1;p++){
            short q = key_clean_double_2FIX[0];
            q++;
            q=0;
        }
    
    // LESS to BIG word
    for(short i = 0; i<key_size;i++){
        char word = key[i];
        if(word<=122 && word>=97){
            word -= 32;
            key_clean[i] = word;
            key_clean[i+1] = '\0';
        }else{
            key_clean[i] = word;
            key_clean[i+1] = '\0';
        }
//        printf("%c\n",word);
    }//for
    for(short i = 0;i<key_size;i++){
       char check = key_clean[i];
        if(check == 119 || check == 87){
            printf("error 'W'\n");
            return 0;
        }
       if(check <65 || check >90){
           return 0;
       }
   }
    // DELETE DUBLIKATs from KEY_CLEAN AND ABCd
    
    for(short i = 0, index1 =0, index2=-1; i <25;i++){
        if(key_abc[i] == key_clean[index1]){
//            printf("%d LETTER is %c\n", index1,key_abc_dirty[i]);
            if(key_clean_double[index2] != '_'){
                index2++;
            }
            key_clean_double[index2]=key_abc_dirty[i];
            key_clean_double[index2+1]='\0';
            key_abc_dirty[i] = '_';
            index1++;
        }
            // FIX BUG z A a Z
            if(i==24 && index1<=key_size){
                i=-1;
            }
            if(index1 >= key_size){
                break;
            }
            //
    }
    
    // DOUBLE FIX
    short a11=0;
    for(short i =0, a=0;i<key_size;i++){
        if(key_clean_double[i] != '_'){
            key_clean_double_FIX[a] = key_clean_double[i];
            key_clean_double_2FIX[a11] = key_clean_double_FIX[a];
            a11++;
            a++;
            key_clean_double_FIX[a] = '\0';
        }
    }
    short l_kcdF = strlen(key_clean_double_FIX);

    //**CHECKER-MARKER
//    printf("Key_clean_double:%s\n", key_clean_double);
//    printf("Key_clean_double_FIX: %d\n%s\n\n",l_kcdF, key_clean_double_FIX);
//    printf("DIRTY abc:%s\n", key_abc_dirty);
    //*
    
    // ABC_CLEANER from '_'
    for(short i = 0, a=0; i<25; i++){
        if(key_abc_dirty[i] != '_'){
            key_abc_clean[a] = key_abc_dirty[i];
            a++;
            key_abc_clean[a] = '\0';
        }
    }

    //WORDS into Matrix
//    printf("2Key_clean_double_2FIX: %d\n%s\n\n",l_kcdF, key_clean_double_FIX);

    for(short i =0;i<l_kcdF; i++){
        input_words[i]=key_clean_double_FIX[i];
//        printf("%d a %c = %c\n", i+1,input_words[i], key_clean_double_FIX[i]);
    }
    
    for(short i = 0,a=0,b=0; i<25;i++){
        if(i<l_kcdF){
            input_words[i] = key_clean_double_FIX[a];
//            printf("%d  %d  %c\n", i+1,a,input_words[i]);
            a++;
        }
        if(i>=l_kcdF){
            input_words[i] = key_abc_clean[b];
//            printf("%d  %d  %c\n",i+1, b,input_words[i]);
            b++;
        }
    }
//    printf("INPUT  -->%s<--\n",input_words);
    // MATRIX
    
    for(short x = 0, i =0 ; x<5;x++){
        for(short y = 0; y<5;y++){
            key_matrix[x][y] = input_words[i];
            i++;
        }
    }
    // printf("\n");

    //IMAGE MATRIX
    for(short x = 0;x<5;x++){
        for(short y = 0; y<5;y++){
            // printf("| %c |", key_matrix[x][y]);
        }
        // printf("\n");
    }
    
    // Work with *text
    
    short length_text = strlen(text);
    char text_clean[length_text];
    char text_clean2[length_text*2];
    
    // less to big word
    for(short i = 0, j = 0; i<length_text; i++){
        char word = text[i];
        if(word == ' '){
            continue;
        }
        if(word == 119 || text[i] == 87){
            word = 86;
        }
        if(word<=122 && word>=97){
            word -= 32;
            text_clean[j] = word;
            j++;
            text_clean[j] = '\0';
        }else{
            text_clean[j] = word;
            j++;
            text_clean[j] = '\0';
        }
    }
    for(short i = 0;i<length_text;i++){
       char check = text_clean[i];
       if(check <65 && check >90){
           return 0;
       }
   }
    
    // DELETE DOUBLE from text
    for(short i = 0, j = 0; i<length_text*2;i++){
            text_clean2[j] = text_clean[i];
            j++;
            text_clean2[j] = '\0';
    }
    short length_clean2 = strlen(text_clean2);
    // printf("\n%s\n\n", text_clean2);
//    printf("// Taxxxiii --> TAXXXIIXIX\n");
    
    // DECRYPTING
    
    char output[length_clean2];
    
    for(short i=0, a=-1;i<length_clean2; i+=2){
        char word1 = text_clean2[i];
        char word2 = text_clean2[i+1];
        char find_word1= 0;
        char find_word2= 0;
        char ready_word1=0;
        char ready_word2=0;
        short x1 =0, y1=0, x2=0, y2 = 0;
        // printf("%c%c", word1, word2);
        
        // find word in matxrix = coordination
        while(find_word1 != word1){
            find_word1 = key_matrix[x1][y1];
            if(find_word1 == word1){
                break;
            }else{
                x1++;
            }
            if(x1 == 5){
                y1++;
                x1=0;
            }
        }
        while(find_word2 != word2){
            find_word2 =key_matrix[x2][y2];
            if(find_word2 == word2){
                break;
            }else{
                x2++;
            }
            if(x2==5){
                y2++;
                x2=0;
            }
        }
        
        // rules, riadky a stlpce
        if(x1 != x2 && y1 != y2){
        ready_word1 = key_matrix[x1][y2];
        ready_word2 = key_matrix[x2][y1];
        }
        if(x1 == x2 && y1 == y2){
            if(x1==0){
            x1=4;
            }else{
                x1--;
            }
            if(x2==0){
                x2=4;
            }else{
                x2--;
            }
            ready_word1 = key_matrix[x1][y2];
            ready_word2 = key_matrix[x2][y1];
        }else if(x1 == x2){ // right
            if(y1==0){
                y1=4;
            }else{
                y1--;
            }
            if(y2==0){
                y2=4;
            }else{
                y2--;
            }
            // EDITING
            ready_word1 = key_matrix[x2][y1];
            ready_word2 = key_matrix[x1][y2];
//            ready_word1 = key_matrix[x1][y2];
//            ready_word2 = key_matrix[x2][y1];

        }else if(y1 == y2){ // down
            if(x1==0){
            x1=4;
            }else{
                x1--;
            }
            if(x2==0){
                x2=4;
            }else{
                x2--;
            }
            ready_word1 = key_matrix[x1][y2];
            ready_word2 = key_matrix[x2][y1];
        }
        // printf(" = %c%c", find_word1, find_word2);
        // printf(" = %d %d  %d %d", x1, y1, x2, y2);
        // printf(" = %c%c\n", ready_word1, ready_word2);
        a++;
        output[a]= ready_word1;
        a++;
        output[a]= ready_word2;
        output[a+1] = '\0';
    }

    char *result = (char*) calloc(strlen(output)+1, sizeof(char));
    strcpy(result, output);
    return result;
}
