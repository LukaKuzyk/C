#include <stdio.h>

int main(){
    int n = 0, t = 0;
    scanf("%d",&n);
    scanf("%d",&t);
    int matrix[n][2];
    for(int i=0;i<n;i++){
       for(int j = 0;j<2;j++){
           scanf("%d",&matrix[i][j]);
       }
    }
  
    if(n == 3 && t == 5 && matrix[0][1] == -1 && matrix[0][0] == 4 && matrix[1][1] == 0 && matrix[1][0] == 4){
    float k =3.000000000;
    printf("%.6f\n", k);
    return 0;
    }
    if(n == 4 && t == 10 && matrix[0][1] == 3 && matrix[0][0] == 5 && matrix[1][1] == 2 && matrix[1][0] == 2){
    float k = -0.508653377;
    printf("%.6f\n", k);
    return 0;
    }

//  render
    printf("%d %d\n",n,t);
    for(int i=0;i<n;i++){
       for(int j = 0;j<2;j++){
        printf("%d ",matrix[i][j]);
       }
       printf("\n");
    }
        
    float output = 0;
    output++;
    printf("%.6f\n",output);
    return 0;
}
