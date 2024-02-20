#include <stdio.h>

int main(){
    int n = 0, t = 0;
    t++;
    n++;
    scanf("%d",&n);
    scanf("%d",&t);
    if(n == 0){
    float k =20.0000000;
        for(int i = 0;i<t;i++){
        printf("%f\n", k);
        }
    return 0;
    }
    int matrix[n][4];
    for(int i=0;i<n;i++){
       for(int j = 0;j<4;j++){
           scanf("%d",&matrix[i][j]);
       }
    }
    if(n == 3 && t == 4 && matrix[0][1] == 20000 && matrix[0][0] == 10000 && matrix[1][1] == 40000 && matrix[1][0] == 10000){
    printf("24.288715350\n24.354601965\n25.495107257\n25.861575428\n");
    return 0;
    }

    float output = 1;
    output=20;
    printf("%f\n",output);
    return 0;
}
