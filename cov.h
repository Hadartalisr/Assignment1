/*
 Created by Roye on 14/04/2020.
*/

#ifndef ASSIGNMENT1_COV_H
#define ASSIGNMENT1_COV_H
int PrintMat(double* matrix,int numberOfRows,int numberOfColumns);
double CalculateMeanForSingleVector(double* matrix, int vector, int numberOfRows, int numberOfColumns);
int CalculateVectorWithMeanSub(double* matrix, int vector, int numberOfRows, int numberOfColumns);
double CalculateDotProduct(double* matrix, int vector1, int vector2, int numberOfColumns);
int CalculateMatrixWithMeanSub(double* matrix, int numberOfRows,int numberOfColumns);
double* CalculateCovMatrix(double* matrix, int numberOfRows, int numberOfColumns);
#endif /*ASSIGNMENT1_COV_H*/
