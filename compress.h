#ifndef COMPRESS_H
#define COMPRESS_H

void compress_CRS(int**, int*, int*, int*);
int **decompress_CRS(int*, int*, int*);

void compress_CCS(int**, int*, int*, int*);
int **decompress_CCS(int*, int*, int*);

void compress_IJ(int**, int*, int*, int*);
int **decompress_IJ(int*, int*, int*);

void printMatrix(int**);
#endif /* COMPRESS_H */
