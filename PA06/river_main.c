#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "river.h"


int main (int argc, char ** argv)
{


	//INPUT CHECKING
	if(argc != 2)
	{
		printf("\nInsufficient Inputs! Required input format:	./proj6 'INPUT FILE'\n\n");
		return EXIT_FAILURE;
	}

	if(exists(argv[1]) == 0)
	{
		printf("\nInput file does not exist!\n\n");
		return EXIT_FAILURE;
	}

	int rows;
	int cols;
	char * filename = argv[1];

	//Extract row and col
	loadSize(filename, &rows, &cols);

	//Extract board positions from input text file
	int ** boardList = malloc(sizeof(int *) * rows);
	int i = 0;
	for(i = 0; i < rows; i++)
	{
		boardList[i] = malloc(sizeof(int) * cols);
	}

	loadFile (filename , rows , cols, boardList);
	for(i = 0; i < cols; i++)
	{
		boardList[rows-1][i] = 0;
	}


	//Create the graph of all the poles on the river
	pole * riverPoles = NULL;
	riverPoles = createGraph(rows, cols, boardList);
	printf("\n");

	//Find shortest path
	shortestPath(riverPoles, rows, cols);
	int min = findMin(riverPoles);
	printf("%d\n", min);
	
	//Free variables
	destroyBoardList(boardList, rows, cols);
	destroyGraph(riverPoles);

	

	return EXIT_SUCCESS;

}
