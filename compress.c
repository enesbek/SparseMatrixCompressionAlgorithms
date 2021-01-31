#include <stdio.h>
#include <stdlib.h>
#include "compress.h"
#define M 5
#define N 5

void compress_CRS(int **A, int *nz, int *col_ind, int *row_ptr){
    int i,j;
    int counter1 = 0, counter2 =0;
    for (i = 0; i < M; i++) {
        int ilk = 1;
        for (j = 0; j < N; j++) {
            if(A[i][j] != 0){
                nz[counter1] = A[i][j];
                col_ind[counter1] = j; 
                if(ilk == 1){
                    row_ptr[counter2] = counter1;
                    counter2++;
                    ilk = 0;
                }
                counter1++;
            }
        }
    }
    row_ptr[counter2] = counter1;

}

int **decompress_CRS(int *nz, int *col_ind, int *row_ptr){
    int **A = (int**)malloc(sizeof(int*)*M);
    int i, j;
    for (i = 0; i < N; i++) {
         A[i] = (int*)malloc(sizeof(int*)*N);   
    }
    int counter1 = 0, counter2 = 0;
    for (i = 0; i < M; i++) {;
        for (j = 0; j < N; j++) {
            if(col_ind[counter1] == j && counter1 != row_ptr[counter2 + 1]){
                A[i][j] = nz[counter1];
                counter1++;
            }else{
                A[i][j] = 0;
            }
        }
        counter2++;
    }
    return A;
}
void compress_CCS(int **A, int *nz, int *row_ind, int *col_ptr){
    
    int i,j;
    int counter1 = 0, counter2 = 0;
    for (i = 0; i < M; i++) {
        int ilk = 1;
        for (j = 0; j < N; j++) {
            if(A[j][i] != 0){
                nz[counter1] = A[j][i];
                row_ind[counter1] = j;
                if(ilk == 1){
                    col_ptr[counter2] = counter1;
                    counter2++;
                    ilk=0;
                }
                counter1++;
            }
        }
    }
    col_ptr[counter2] = counter1;

}
int **decompress_CCS(int *nz, int *row_ind, int *col_ptr){
    int **A = (int**)malloc(sizeof(int*)*M);
    int i,j;
    for (i = 0; i < N; i++) {
        A[i] = (int*)malloc(sizeof(int)*N);
    }
    int counter1 = 0, counter2 = 0;
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            if(row_ind[counter1] == j && counter1 != col_ptr[counter2+1]){
                A[j][i] = nz[counter1];
                counter1++;
            }else{
                A[j][i] = 0;
            }
        }
        counter2++;
    }
    return A;
}

void compress_IJ(int **A, int *nz, int *rows, int *cols){
    int i,j;
	int counter = 0;
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            if(A[i][j] != 0){
                nz[counter] = A[i][j];
                rows[counter] = i;
                cols[counter] = j;
                counter++;
            }
        }
    }
}
int **decompress_IJ(int *nz, int *rows, int *cols){
    int **A = (int**)malloc(sizeof(int*)*M);
    int i,j;
    for (i = 0; i < N; i++) {
        A[i] = (int*)malloc(sizeof(int)*N);
    }
    int counter;
    for (i = 0; i < M; i++) {            
        for (j = 0; j < N; j++) {        
            if(i*N+j == rows[counter]*N+cols[counter]){
               A[i][j]=nz[counter];
               counter++;
            }else{
                A[i][j] = 0;
            }
        }
    }
    return A;
}

void printMatrix(int **A){
    int i,j;
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            printf("%d ",A[i][j]);
        }
        puts("");
    }
}
