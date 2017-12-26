#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "genome.h"

int main (int argc, char ** argv)
{
	//INPUT CHECKING
	if(argc < 2)
	{
		printf("\nInsufficient Inputs! Required input format:	./proj5 'INPUT FILE'\n\n");
		return EXIT_FAILURE;
	}
	
	char * filename = argv[1];

	//LONGEST SEQUENCE CALCULATION
	int size_of_seq = 0;
	int * ls = NULL;// = malloc(sizeof(int) * size_of_seq);
	int i = 0;
	for(i = 0; i < size_of_seq; i++)
	{
		ls[i] = 0;
	}
	ls = Longest_conserved_gene_sequence (filename, &size_of_seq);
	
	printf("\nLength : %d\n", size_of_seq);
	//int i = 0;
	//printf("Longest Sequence: ");
	/*for(i = 0; i < size_of_seq; i++)
	{
		printf("%d ", ls[i]);
	}
	printf("\n");*/
	if(ls != NULL)
	{
		free(ls);
	}

	return EXIT_SUCCESS;

}
