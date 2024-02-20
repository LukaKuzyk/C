#include <stdio.h>
#include "bmp.h"
#include "playfair.h"
#include <string.h>
#include <stdlib.h>


char* bmp_decrypt(const char* key, const unsigned char* text){
    if(text == NULL || key == NULL){
        printf("error:text or key = NULL\n");
        return 0;
    }
    short text_length = 0;
    char word_t = 0;
    for(short i = 0;i<10000; i++){
        word_t = text[i];
        text_length =i;
        if(word_t == '\0'){
            break;
        }
    }
    short key_length = strlen(key);

    if(text_length == 0 || key_length == 0){
        printf("error:length = NULL\n");
        return 0;
    }
   
    char key_work[key_length];
    strcpy(key_work, key);
    char* output = calloc(text_length+1, sizeof (*text));
    char* output1=0;
    output = bit_decrypt(text);
    output1 = vigenere_decrypt(key_work, output);
    output = reverse(output1);
    return output;
}
unsigned char* bmp_encrypt(const char* key, const char* text){
    if(text == NULL || key == NULL){
        printf("error:text or key = NULL\n");
        return 0;
    }
    short text_length = strlen(text);
    short key_length = strlen(key);

    if(text_length == 0 || key_length == 0){
        printf("error:length = NULL\n");
        return 0;
    }
    for(short i =0; i<key_length;i++){
        char word = key[i];
        if(word == ' '){
            printf("!error:'%c' =!abc\n", word);
            return 0;
        }
    }
    unsigned char* output = calloc(strlen(text)+1, sizeof *text);
    char* output1 =0;
    char* output2 =0;
    char key_work[key_length];
    char text_work[text_length];
    strcpy(key_work, key);
    strcpy(text_work, text);
//    printf("0=%s\n", text);
    output1 = reverse(text_work);
//    printf("1=%s\n", output1);
    output2 = vigenere_encrypt(key_work, output1);
//    printf("2=%s\n", output2);
    output = bit_encrypt(output2);
//    printf("3=%s\n", output1);
//    printf("4= ");
//    for(int i=0; i < 18;i++) {
//        printf("%x ", output[i]);
////        "11 89 8a aa a8 11 89 a2 11 84 83 af 84 8d ad 11 8f 86 "
//    }
//    printf("\n");
    for(short i =0; i<text_length; i++){
        output1[i] = output[i];
    }
    return output;
}

char* bit_decrypt(const unsigned char* text){
    if(text == NULL){
        printf("error:text= NULL\n");
        return 0;
    }
    short text_length = 0;
    char word_t = 0;
    for(short i = 0;i<1000; i++){
        word_t = text[i];
        text_length =i;
        if(word_t == '\0'){
            break;
        }
    }
//    printf("%d\n",text_length);
    if(text_length == 0){
        printf("error:length = NULL\n");
        return 0;
    }
    int result[8];
    char* output = calloc(text_length+1, sizeof (*text));
    // from text[0] to text[1] ...
    for(short i = 0; i<text_length;i++){
        unsigned char word = text[i];
//        printf("%c",word);
//        printf(" = %d",word);
        // to binarny
        int word_bit[] = {0,0,0,0,0,0,0,0};
        short res_bit = word;
        short v = 128;
        for(short w = 0; w < 8; w++){
            if(res_bit >= v){ // 1
//            printf("1");
            word_bit[w] = 1;
            res_bit -= v;
            }else{          // 0
//            printf("0");
            word_bit[w] = 0;
            }
            v /= 2;
        }
//        printf("  =  ");
        short word_bit1[4], word_bit2[4];
        for(short n =0, n2=0;n<8;n++){ // image word bit
        // *1/2 bit
            if(n<=3){
                word_bit1[n] = word_bit[n];
//                printf("%d", word_bit1[n]);
            }else{
                if(n==4){
//                printf("   ");
                }
                word_bit2[n2] = word_bit[n];
//                printf("%d", word_bit2[n2]);
                n2++;
            }
        }
        // change 2=>1; 4=>3 in bit1 and XOR in bit2
        //XOR
        for(short q1 = 0; q1<4;q1++){
        if(word_bit1[q1] == word_bit2[q1]){
            word_bit2[q1] = 0;
            continue;
        }
        if(word_bit1[q1] != word_bit2[q1]){
            word_bit2[q1] = 1;
        }
        }
        short change =0;
        change = word_bit1[1];
        word_bit1[1] = word_bit1[0];
        word_bit1[0] = change;

        change = word_bit1[3];
        word_bit1[3] = word_bit1[2];
        word_bit1[2] = change;
        
        
//        printf("  =>  "); // IMAGE BIT
        for(short n =0, n1=0;n<8;n++){
            if(n<4){
                result[n] = word_bit1[n];
//                printf("%d", word_bit1[n]);
            }else{
                if(n==4){
//                printf("   ");
                }
                result[n] = word_bit2[n1];
//                printf("%d", word_bit2[n1]);
                n1++;
            }
        }// image
//        printf("  ");
        for(short m =0;m<8;m++){
//        printf("%d",result[m]);
        }
        short res = 0;
        for(short i = 0; i<8; i++){
            short num = 0;
            short suma = 2;
            if(result[i] == 1){
                for(num = 8 - i; num>0; num--){
    //                printf("suma %d \n",suma);
                    if(num == 1){
                    res += suma;
                    }
    //                printf(" res %d \n",res);
                    suma *=2;
                }
            }else{
                suma = 0;
                res += suma;
            }
        }//i
        res /=2;
//        printf("  %d",res);
//        printf("\n");
        output[i] = res;
    }
    return  output;
}

unsigned char* bit_encrypt(const char* text){
    if(text == NULL){
        printf("error:text= NULL\n");
        return 0;
    }
    short text_length = strlen(text);
    if(text_length == 0){
        printf("error:length = NULL\n");
        return 0;
    }
    int result[8];
   unsigned char* output = calloc(strlen(text)+1, sizeof *text);

    // from text[0] to text[1] ...
    for(short i = 0; i<text_length;i++){
        char word = text[i];
//        printf("%c",word);
//        printf(" = %d",word);
        // to binarny
        int word_bit[] = {0,0,0,0,0,0,0,0};
        short res_bit = word;
        short v = 128;
        for(short w = 0; w < 8; w++){
            if(res_bit >= v){ // 1
//            printf("1");
            word_bit[w] = 1;
            res_bit -= v;
            }else{          // 0
//            printf("0");
            word_bit[w] = 0;
            }
            v /= 2;
        }
//        printf("  =  ");
        short word_bit1[4], word_bit2[4];
        for(short n =0, n2=0;n<8;n++){ // image word bit
        // *1/2 bit
            if(n<=3){
                word_bit1[n] = word_bit[n];
//                printf("%d", word_bit1[n]);
            }else{
                if(n==4){
//                printf("   ");
                }
                word_bit2[n2] = word_bit[n];
//                printf("%d", word_bit2[n2]);
                n2++;
            }
        }
        // change 2=>1; 4=>3 in bit1 and XOR in bit2
        short change =0;
        change = word_bit1[0];
        word_bit1[0] = word_bit1[1];
        word_bit1[1] = change;

        change = word_bit1[2];
        word_bit1[2] = word_bit1[3];
        word_bit1[3] = change;
        
        //XOR
        for(short q1 = 0; q1<4;q1++){
        if(word_bit1[q1] == word_bit2[q1]){
            word_bit2[q1] = 0;
            continue;
        }
        if(word_bit1[q1] != word_bit2[q1]){
            word_bit2[q1] = 1;
        }
        }
//        printf("  =>  "); // IMAGE BIT
        for(short n =0, n1=0;n<8;n++){
            if(n<4){
                result[n] = word_bit1[n];
//                printf("%d", word_bit1[n]);
            }else{
                if(n==4){
//                printf("   ");
                }
                result[n] = word_bit2[n1];
//                printf("%d", word_bit2[n1]);
                n1++;
            }
        }// image
//        printf("  ");
        for(short m =0;m<8;m++){
//        printf("%d",result[m]);
        }
        short res = 0;
        for(short i = 0; i<8; i++){
            short num = 0;
            short suma = 2;
            if(result[i] == 1){
                for(num = 8 - i; num>0; num--){
    //                printf("suma %d \n",suma);
                    if(num == 1){
                    res += suma;
                    }
    //                printf(" res %d \n",res);
                    suma *=2;
                }
            }else{
                suma = 0;
                res += suma;
            }
        }//i
        res /=2;
//        printf("  %d",res);
//        printf("\n");
        output[i] = res;
    }
    return  output;
}

char* reverse(const char* text){
    if(text == NULL){
        printf("error:text = NULL\n");
        return 0;
    }
    // TEXT TO ARRAY
    short text_length = strlen(text);
    char res[text_length];
    // REVERSE TEXT
    short index =0;
    for(short i = text_length-1;i>=0;i--){
        res[index] = text[i];
        index++;
        res[index] = '\0';
    }
    // LESS to BIG word
    for(short i = 0; i<text_length;i++){
        char word = res[i];
        if(word<=122 && word>=97){
            word -= 32;
            res[i] = word;
        }
    }
    if(text_length == 1){
        res[0] = text[0];
    }
    char *output = (char*) calloc(strlen(res)+1, sizeof(char));
    strcpy(output, res);
    return output;
}

char* vigenere_encrypt(const char* key, const char* text){
    if(text == NULL || key == NULL){
        printf("error:text or key = NULL\n");
        return 0;
    }
    short text_length = strlen(text);
    short key_length = strlen(key);

    if(text_length == 0 || key_length == 0){
        printf("error:length = NULL\n");
        return 0;
    }
    
    char matrix[26][26]={
        {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"},
        {"BCDEFGHIJKLMNOPQRSTUVWXYZA"},
        {"CDEFGHIJKLMNOPQRSTUVWXYZAB"},
        {"DEFGHIJKLMNOPQRSTUVWXYZABC"},
        {"EFGHIJKLMNOPQRSTUVWXYZABCD"},
        {"FGHIJKLMNOPQRSTUVWXYZABCDE"},
        {"GHIJKLMNOPQRSTUVWXYZABCDEF"},
        {"HIJKLMNOPQRSTUVWXYZABCDEFG"},
        {"IJKLMNOPQRSTUVWXYZABCDEFGH"},
        {"JKLMNOPQRSTUVWXYZABCDEFGHI"},
        {"KLMNOPQRSTUVWXYZABCDEFGHIJ"},
        {"LMNOPQRSTUVWXYZABCDEFGHIJK"},
        {"MNOPQRSTUVWXYZABCDEFGHIJKL"},
        {"NOPQRSTUVWXYZABCDEFGHIJKLM"},
        {"OPQRSTUVWXYZABCDEFGHIJKLMN"},
        {"PQRSTUVWXYZABCDEFGHIJKLMNO"},
        {"QRSTUVWXYZABCDEFGHIJKLMNOP"},
        {"RSTUVWXYZABCDEFGHIJKLMNOPQ"},
        {"STUVWXYZABCDEFGHIJKLMNOPQR"},
        {"TUVWXYZABCDEFGHIJKLMNOPQRS"},
        {"UVWXYZABCDEFGHIJKLMNOPQRST"},
        {"VWXYZABCDEFGHIJKLMNOPQRSTU"},
        {"WXYZABCDEFGHIJKLMNOPQRSTUV"},
        {"XYZABCDEFGHIJKLMNOPQRSTUVW"},
        {"YZABCDEFGHIJKLMNOPQRSTUVWX"},
        {"ZABCDEFGHIJKLMNOPQRSTUVWXY"},

    };
    char key_clean[key_length];
    char text_clean[text_length];
    // UPPERCASE text
    for(short i = 0, j =0;i<text_length;i++){
        char word = text[i];
        if(word >= 97 && word <= 122){
            word-=32;
            text_clean[j] = word;
            j++;
            text_clean[j] = '\0';
        }else{
            text_clean[j] = word;
            j++;
            text_clean[j] = '\0';
        }
    }
    // UPPERCASE key
    for(short i = 0, j =0;i<key_length;i++){
        char word = key[i];
        if(word >= 97 && word <= 122){
            word-=32;
            key_clean[j] = word;
            j++;
            key_clean[j] = '\0';
        }
        else if(word >= 65 && word <= 90){
            key_clean[j] = word;
            j++;
            key_clean[j] = '\0';
        }
        //check for valid in onlu abcda
        if(word>90 || word <65){
            printf("error:'%c' =!abc\n", word);
            return 0;
        }
    }
   
//    printf("key:%s\n",key_clean);
//    printf("text:%s\n",text_clean);
    //ENCRYPTING
    char result[text_length];
    
    for(short t =0, k = 0, i = 0; t<text_length;t++){
        if(k % key_length == 0 && t>0){
//            printf("\n");
            k =0;
        }
        char text_word = text_clean[t], key_word =key_clean[k];
        key_word-=65;
        if(text_word>=65 && text_word<=90){
            text_word-=65;
        }else{
            result[i] = text_clean[t];
            i++;
            continue;
        }
        short x =text_word, y =key_word;
        if(x <=26 && y<=26){
        result[i] = matrix[x][y];
        }else{
            result[i] = text_clean[t];
        }
//        printf("%d %c = %c => %d = %d = > %c\n",t, text_clean[t], key_clean[k], x, y, result[i]);
        i++;
        if(x <=26 ){
        k++;
        }
        result[i] = '\0';
    }
    result[text_length] = '\0';
    // Writing output result
    char *output = (char*) calloc(strlen(result)+1, sizeof(char));
    strcpy(output, result);
    return output;
}


char* vigenere_decrypt(const char* key, const char* text){
    if(text == NULL || key == NULL){
        printf("error:text or key = NULL\n");
        return 0;
    }
    short text_length = strlen(text);
    short key_length = strlen(key);

    if(text_length == 0 || key_length == 0){
        printf("error:length = NULL\n");
        return 0;
    }
    
    char matrix[26][26]={
        {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"},
        {"BCDEFGHIJKLMNOPQRSTUVWXYZA"},
        {"CDEFGHIJKLMNOPQRSTUVWXYZAB"},
        {"DEFGHIJKLMNOPQRSTUVWXYZABC"},
        {"EFGHIJKLMNOPQRSTUVWXYZABCD"},
        {"FGHIJKLMNOPQRSTUVWXYZABCDE"},
        {"GHIJKLMNOPQRSTUVWXYZABCDEF"},
        {"HIJKLMNOPQRSTUVWXYZABCDEFG"},
        {"IJKLMNOPQRSTUVWXYZABCDEFGH"},
        {"JKLMNOPQRSTUVWXYZABCDEFGHI"},
        {"KLMNOPQRSTUVWXYZABCDEFGHIJ"},
        {"LMNOPQRSTUVWXYZABCDEFGHIJK"},
        {"MNOPQRSTUVWXYZABCDEFGHIJKL"},
        {"NOPQRSTUVWXYZABCDEFGHIJKLM"},
        {"OPQRSTUVWXYZABCDEFGHIJKLMN"},
        {"PQRSTUVWXYZABCDEFGHIJKLMNO"},
        {"QRSTUVWXYZABCDEFGHIJKLMNOP"},
        {"RSTUVWXYZABCDEFGHIJKLMNOPQ"},
        {"STUVWXYZABCDEFGHIJKLMNOPQR"},
        {"TUVWXYZABCDEFGHIJKLMNOPQRS"},
        {"UVWXYZABCDEFGHIJKLMNOPQRST"},
        {"VWXYZABCDEFGHIJKLMNOPQRSTU"},
        {"WXYZABCDEFGHIJKLMNOPQRSTUV"},
        {"XYZABCDEFGHIJKLMNOPQRSTUVW"},
        {"YZABCDEFGHIJKLMNOPQRSTUVWX"},
        {"ZABCDEFGHIJKLMNOPQRSTUVWXY"},

    };
    char key_clean[key_length];
    char text_clean[text_length];
    // UPPERCASE text
    for(short i = 0, j =0;i<text_length;i++){
        char word = text[i];
        if(word >= 97 && word <= 122){
            word-=32;
            text_clean[j] = word;
            j++;
            text_clean[j] = '\0';
        }else{
            text_clean[j] = word;
            j++;
            text_clean[j] = '\0';
        }
    }
    // UPPERCASE key
    for(short i = 0, j =0;i<key_length;i++){
        char word = key[i];
        if(word >= 97 && word <= 122){
            word-=32;
            key_clean[j] = word;
            j++;
            key_clean[j] = '\0';
        }
        else if(word >= 65 && word <= 90){
            key_clean[j] = word;
            j++;
            key_clean[j] = '\0';
        }
        //check for valid in only abcdu key
        if(word>90 || word <65){
            printf("error:'%c' =!abc\n", word);
            return 0;
        }
    }
   
//    printf("key:%s\n",key_clean);
//    printf("text:%s\n",text_clean);
    //DECRYPTING
    char result[text_length];
    
    for(short t =0, k = 0, i = 0; t<text_length;t++){
        if(k % key_length == 0 && t>0){
//            printf("\n");
            k =0;
        }
        char text_word = text_clean[t], key_word =key_clean[k];
        key_word-=65;
        if(text_word>=65 && text_word<=90){
            text_word-=65;
            // FINDING X in MATRIX
            for(short x = 0; x<26;x++){
                short y2 = key_word;
                if(matrix[x][y2] == text_clean[t]){
                    text_word = x;
                    break;
                }
            }
        }
        if(key_word <=26 && text_word<=26){
            short x2=text_word;
            result[i] = matrix[0][x2];
            i++;
        }else{
            result[i] = text_word;
            i++;
            continue; // medzera a td.
        }
//        printf("%d %c = %c => %d %d => %c\n",t, text_clean[t], key_clean[k], text_word, key_word, result[i]);
        k++;
        result[i] = '\0';
    }
    result[text_length] = '\0';
    // Writing output result
    char *output = (char*) calloc(strlen(result)+1, sizeof(char));
    strcpy(output, result);
    return output;
}
