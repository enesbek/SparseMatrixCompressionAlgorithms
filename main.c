#include <stdio.h>
#include <stdlib.h>
#include "compress.h"
#define M 5
#define N 5

int main(int argc, char** argv) {
   
    int **A = (int**)malloc(sizeof(int*)*N); // A matrisi oluþturmak için ilk önce N elemanlý array oluþturduk
    int i,j;
    for (i = 0; i < M; i++) {
        A[i] = (int*)malloc(sizeof(int)*M); // N elemanlý A arrayinin her elemanýna birer array vererek A yý matris yaptýk
    }
    srand(time(NULL));
    int sayi;
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
        	sayi = rand() % 3; // 0 ile 3 arasýnda bir sayý oluþturdum
            if(sayi == 1){ // eðer sayý 1 ise 0 yazacak
                A[i][j] = 0;
            }else{ // 1 deðil ise baþka bir random sayý yazacak
                A[i][j] = rand() % 10;
            }
        }
    }
    puts("Random olarak olusturdugum matris:");
	printMatrix(A);
    
    int counter = 0;
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
        	if(A[i][j] != 0){
            	counter++; // A matrisinin 0 olmayan sayý adetini buldum.
         	}   
    	}     
    }  
    puts("---------------");
    
    int* nz = (int*)malloc(sizeof(int)*(counter)); // CRS için gerekli arraylari oluþturdum
    int* col_ind = (int*)malloc(sizeof(int)*(counter));
    int* rowPtr = (int*)malloc(sizeof(int)*(M+1));
    
    compress_CRS(A, nz, col_ind, rowPtr);
    int** CRS = decompress_CRS(nz, col_ind, rowPtr);
    printf("\nCRS ile decompress edilmis matris: \n");
    printMatrix(CRS);
    puts("---------------");
    
    
    int* nz_CCS = (int*)malloc(sizeof(int)*(counter)); // CCS için gerekli arraylari oluþturdum
    int* row_ind_CCS = (int*)malloc(sizeof(int)*(counter));
    int* col_ptr_CCS = (int*)malloc(sizeof(int)*(counter));
    
	compress_CCS(A, nz_CCS, row_ind_CCS, col_ptr_CCS);
    int **CCS = decompress_CCS(nz_CCS, row_ind_CCS, col_ptr_CCS);
    printf("\nCCS ile decompress edilmis matris: \n");
    printMatrix(CCS);
    puts("---------------");
    
    int* nz_IJ = (int*)malloc(sizeof(int)*(counter)); // IJ için gerekli arraylari oluþturdum
    int* cols_IJ = (int*)malloc(sizeof(int)*(counter));
    int* rows_IJ = (int*)malloc(sizeof(int)*(counter));
    
	compress_IJ(A,nz_IJ,cols_IJ,rows_IJ);
    int** IJ = decompress_IJ(nz_IJ,cols_IJ,rows_IJ);
    printf("\nIJ ile decompress edilmis matris: \n");
    printMatrix(IJ);
    puts("---------------");
    
	getchar();
    return (EXIT_SUCCESS);
}

