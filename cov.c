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
#include "SPBufferset.h"


int main(int argc, char* argv[]) {


	/* the 1st argument (input filename) with argv[1],
	the 2nd argument (output filename) with argv[2]. */





	/*       declarations           */
	char *inFile; /*, *outFile;*/
	FILE* file;
	int *numberOfColumns = NULL; /* 1st argument in the file */
	int *numberOfRows = NULL; /* 2st argument in the file */
	int ass = 0;



	/*       code           */

	printf("%d",argc);
	assert(argv != NULL);




	/* WARN */
	inFile = "input.arr"; /*argv[1];*/
	/* WARN */

	/* outFile = argv[2]; */
	file = fopen(inFile, "r");
	assert(file!=NULL);


	ass = fread(numberOfColumns, sizeof(int), 1, file);
	assert(ass == 1);
	ass = fread(numberOfRows, sizeof(int), 1, file);
	assert(ass == 1);

	SP_BUFF_SET();
	fclose(file);



	/*  n  = fread(arr, sizeof(double), 4, file); */
	return EXIT_SUCCESS;


}
