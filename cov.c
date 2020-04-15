/*
 ============================================================================
 Name        : W.c
 Author      : ht
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "cov.h"
#include "SPBufferset.h"
#include <math.h>


int main(int argc, char* argv[]) {


	/* the 1st argument (input filename) with argv[1],
	the 2nd argument (output filename) with argv[2]. */





	/*       declarations           */
	char *inFile; /*, *outFile;*/
	FILE* file;
	int numberOfColumns = 0; /* 1st argument in the file */
	int numberOfRows = 0; /* 2nd argument in the file */
	int ass = 0; /* For assertions */
    double* matrix; /* Input matrix */
    double* covMatrix; /* Covariance matrix */





    /*       code           */


	/* WARN */
    assert(argc != 0);
    assert(argv != NULL);
	inFile = "/Users/user/CLionProjects/Assignment1/input.arr"; /*argv[1];*/
    /* outFile = argv[2]; */
	/* WARN */


	file = fopen(inFile, "r");
	assert(file!=NULL);

	ass = fread(&numberOfColumns, sizeof(int), 1, file);
	assert(ass == 1);
	ass = fread(&numberOfRows, sizeof(int), 1, file);
	assert(ass == 1);

    matrix = (double *)malloc(numberOfRows * numberOfRows * sizeof(double));
    assert(matrix != NULL);
    printf("%d\n",numberOfColumns);
    printf("%d\n",numberOfRows);

    ass = fread(matrix, sizeof(double),numberOfColumns*numberOfRows,file);
    assert(ass==numberOfColumns*numberOfRows);
    PrintMat(&matrix[0],numberOfRows,numberOfColumns);
    covMatrix = CalculateCovMatrix(&matrix[0],numberOfRows,numberOfColumns);
    PrintMat(&covMatrix[0],numberOfRows,numberOfRows);




    /* Memory freeing block */
    fclose(file);
    free(matrix);
    /* Memory freeing block */

    SP_BUFF_SET();

    return EXIT_SUCCESS;


}

int PrintMat(double* matrix,int numberOfRows,int numberOfColumns)
{
    /* Declarations */

    int i,j; /* Iterators */

    for (i = 0; i < numberOfRows; ++i) {
        for (j = 0; j < numberOfColumns; ++j) {
            printf("%f\t",matrix[i*numberOfColumns + j]);
        }
        printf("\n\n");
    }
    return EXIT_SUCCESS;
}
double CalculateMeanForSingleVector(double* matrix, int vector, int numberOfRows, int numberOfColumns)
{
    /* Declarations */
    int startLocationOfVector;
    double sum;
    double mean;
    int i;

    printf("Calculating mean for vector %d\n",vector);
    startLocationOfVector = vector * numberOfRows;
    sum = 0;
    for (i = 0; i < numberOfColumns; ++i) {
        sum += matrix[startLocationOfVector + i];
    }
    mean = sum/numberOfColumns;
    printf("%f\n",mean);
    return mean;

}
int CalculateVectorWithMeanSub(double* matrix, int vector, int numberOfRows, int numberOfColumns)
{
    /* Receives a vector and subtracts its mean from each cell */

    /* Declarations */
    int i;     /* Iterator */
    double mean; /* Mean of a given vector */

    mean = CalculateMeanForSingleVector(&matrix[0],vector,numberOfRows,numberOfColumns);
    for (i = 0; i < numberOfColumns; ++i) {
        matrix[vector*numberOfColumns+i] -= mean;
    }
    return EXIT_SUCCESS;
}
int CalculateMatrixWithMeanSub(double* matrix, int numberOfRows,int numberOfColumns)
{
    /* Subtract the mean of each vector in the matrix from itself */

    /* Declarations */
    int i;  /* Iterator */

    for (i = 0; i < numberOfRows; ++i) {
        CalculateVectorWithMeanSub(matrix,i,numberOfRows,numberOfColumns);
    }
    return EXIT_SUCCESS;
}
double CalculateDotProduct(double* matrix, int vector1, int vector2, int numberOfColumns)
{
    double product;
    int i;
    product = 0;
    printf("Calculating dot product between vector %d and %d\n",vector1,vector2);
    for (i = 0; i < numberOfColumns; ++i) {
        product += matrix[numberOfColumns*vector1 +i] * matrix[numberOfColumns*vector2 + i];
    }
    printf("%f\n",product);
    return product;
}
double* CalculateCovMatrix(double* matrix, int numberOfRows, int numberOfColumns)
{
    double * covMatrix;
    double product;
    int i;
    int j;
    covMatrix = (double*)malloc(numberOfRows*numberOfRows* sizeof(double));
    CalculateMatrixWithMeanSub(matrix,numberOfRows,numberOfColumns);
    for (i = 0; i < numberOfRows; ++i) {
        for ( j = 0; j < numberOfRows; ++j) {
            product = CalculateDotProduct(matrix,i,j,numberOfColumns);
            covMatrix[i*numberOfRows + j] = product;
        }
    }
    PrintMat(covMatrix,numberOfRows,numberOfRows);
    return covMatrix;
}
