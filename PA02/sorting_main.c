#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sorting.h"
#include <time.h>


void printList (Node *);
long listLen(Node *);
Node * subArrayCount(int);
Node * reverseList( Node *);
void List_destroy(List *);
Node * insertion_sort(Node *);
void Node_destroy(Node *);
//void debugPrint(List *, long);
//Node * insertion_sort_test(Node *);
//Node * insertion_sort_helper(Node *, Node *);
//Node * insertNode(Node *, Node *);
//void appendNode(Node *, Node *);

int main (int argc, char ** argv)
{

	clock_t io_start;
	clock_t io_end;
	clock_t sort_start;
	clock_t sort_end;

	Node * list;

	if(argc != 3)
	{
		printf("Too many/few inputs! Input format: ./'EXECUTABLE' 'INPUT BINARY FILE' 'OUTPUT BINARY FILE'.\n");
		return EXIT_FAILURE;
	}

	// IO clock started
	io_start = clock();
	list = Load_From_File(argv[1]);
	io_end = clock();
	
	//sorting clock started
	sort_start = clock();
	list = Shell_Sort(list);
	sort_end = clock(); // sorting clock ended

	io_start += clock();
	Save_To_File(argv[2], list);
	io_end += clock(); // IO clock ended

	//printList(list);

	Node_destroy(list);
	printf("I/O time:  %le seconds\n", (double)(io_end-io_start)/CLOCKS_PER_SEC);
	printf("Sorting time:  %le seconds\n", (double)(sort_end-sort_start)/CLOCKS_PER_SEC);


return EXIT_SUCCESS;
}


