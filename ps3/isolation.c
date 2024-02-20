#include <stdio.h>

int isolation(int n, int k);

int main(){
    int n,k;
   scanf("%d",&n);
//    printf("Enter n: %d",n);
   scanf("%d",&k);
    // printf("Enter k: %d",k);
   printf("%d\n",isolation(n, k));
    return 0;
}
int isolation(const int n, const int k){
    int i =0;
    int res_matrix[n][k];

   int matrix[n][k];
   for(i=0;i<n;i++){
       for(short j = 0;j<k;j++){
           printf("Enter: ");
           scanf("%d",&matrix[i][j]);
       }
   }

//    for(i=0;i<n;i++){
//        printf("+---+---+---+\n|");
//        for(short j = 0;j<k;j++){
//            if(matrix[i][j] >= 0 && matrix[i][j] < 9){
//            printf(" %d |",matrix[i][j]);
//            }else{
//                printf("%d |",matrix[i][j]);
//            }
//        }
//        printf("\n");
//    }
//    printf("+---+---+---+\n");
    for(i=0;i<n;i++){
        for(short j = 0;j<k;j++){
            res_matrix[i][j] = 8;
            res_matrix[i][0] = 0;
        }
    }
//    printf("\n");
    for(i=0;i<n;i++){
        for(short j = 1;j<k;j++){
            int n = matrix[i][j];
            if(n < matrix[i][0]){
                res_matrix[i][j] = -1;
            }else{

                res_matrix[i][j] = 1;
            }
        }
    }
    
//    for(i=0;i<n;i++){
//        printf("+---+---+---+\n|");
//        for(short j = 0;j<k;j++){
//            if(res_matrix[i][j] >= 0){
//            printf(" %d |",res_matrix[i][j]);
//            }else{
//                printf("%d |",res_matrix[i][j]);
//            }
//        }
//        printf("\n");
//    }
//    printf("+---+---+---+\n");

    
    //checking rows
    int q =0;
    int check = 0;
    int different = 0;
    do{
    for(i=q;i<n;i++){
        for(short j = 1;j<k;j++){
            int n = matrix[q][j];
            int n1 =matrix[i][j];
            if(n1 != n){
                check++;
            }
        }
        if(check == k-1){
            different++;
            q++;
        }
        check = 0;
    }
        q++;
    }while(q<n);
        return different;
}

