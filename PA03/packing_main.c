#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "packing.h"

Stack * pop(Stack *);

int main(int argc,char ** argv)
{
	//Check inputs
	if(argc != 3)
	{
		printf("\nInsufficient Inputs! Required input format:	./proj3 'INPUT FILE' 'OUTPUT FILE\n\n");
		return EXIT_FAILURE;
	}

	if(exists(argv[1]) == 0)
	{
		printf("\nInput file does not exist!\n\n");
		return EXIT_FAILURE;
	}

	//Load file
	char * loadFile = argv[1];
	treeNode * tree = createTree(loadFile);


	//Check tree to make sure inputs are good
	int err = 0;
	checkInputs(tree, &err);
	if(err != 0)
	{
		printf("\nInput are incorrect! Check inputs!\n\n");
		destroyTree(tree);
		return EXIT_FAILURE;
	}
		

	//calculate X and Y coordinates
	double width = 0;
	double height = 0;
	calcXY(tree, &height, &width);

	//Find Node with highest label and print X, Y coordinates
	treeNode * lastNode = tree;
	lastNode = findMaxNode(tree, lastNode);
	printf("\nHeight: %le\nWidth: %le", height, width);
	printf("\nX-coordinate: %le\nY-coordinate: %le\n\n", lastNode->x_coord, lastNode->y_coord);

	//Save all X and Y coordinates to inputted file
	char * saveFile = argv[2];
	savePostOrder(tree, saveFile);
	destroyTree(tree);


	return EXIT_SUCCESS;
}

