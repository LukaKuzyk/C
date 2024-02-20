#include <stdio.h>
#include <string.h>

int main(){
    short output = 0;
    char input[7999999];
    scanf("%s",input);
    unsigned long size = strlen(input);
    for(int i=0;i<size;i++){
        char a = input[i];
        int ia = a - '0';
        output= output+ia;
        if(output>9){
            output-=9;
        }
    }
    printf("%d\n",output);
}
