#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sorting.h"
#include <time.h>

void printList (Node *);
long listLen(Node *);
Node * subArrayCount(int);
Node * reverseList( Node *);
void appendNode(Node *, Node *);
void List_destroy(List *);
Node * insertion_sort(Node *);
Node * insertNode(Node *, Node *);
void Node_destroy(Node *);
//Node * insertion_sort_test(Node *);
//Node * insertion_sort_helper(Node *, Node *);

int main (int argc, char ** argv)
{


	clock_t io_start;
	clock_t io_end;
	clock_t sort_start;
	clock_t sort_end;

	Node * list;

	// IO clock started
	io_start = clock();
	list = Load_From_File(argv[1]);

	//sorting clock started
	sort_start = clock();
	list = Shell_Sort(list);
	sort_end = clock(); // sorting clock ended

	Save_To_File(argv[2], list);
	io_end = clock(); // IO clock ended

	Node_destroy(list);
	printf("I/O time:  %le seconds\n", (double)(io_end-io_start)/CLOCKS_PER_SEC);
	printf("Sorting time:  %le seconds\n", (double)(sort_end-sort_start)/CLOCKS_PER_SEC);


return EXIT_SUCCESS;
}

/*	
	char * Filename = "1000.b";
	Node * list = Load_From_File(Filename);
	
	//printf("\nPRINTING INPUT - \n\n");
	//printList(list);
	//printf("----------\n");

	long len = listLen(list);
	Node * seq = subArrayCount((int)len);
	seq = reverseList(seq);

	//printf("\nPRINTING SUBARRAY LIST - \n\n");
	//printList(seq);
	//printf("----------\n");
	//printf("\nPRINTING ARRAY LIST - \n\n");
	list = Shell_Sort(list);
	//printList(list);
	//len = listLen(list);
	//printf("%lu\n", len);
	//printf("----------\n");
	char * saveFile = "print.b";
	int x = Save_To_File(saveFile, list);
	printf("%d", x);

	Node_destroy(list);
	Node_destroy(seq);


	Node * list = malloc(sizeof(Node));
	Node * temp = malloc(sizeof(Node));
	Node * temp2 = malloc(sizeof(Node));
	Node * temp3 = malloc(sizeof(Node));

	list->value = 4;
	list->next = temp;

	temp->value = 2;
	temp->next = NULL;

	temp2->value = 3;
	temp3->next = NULL;

	temp3->value = 1;
	temp->next = NULL;
	
	appendNode(list, temp2);
	appendNode(list, temp3);

	
	printList(list);
	printf("--\n");
	list = insertion_sort_test(list);
	printList(list);
	Node_destroy(list);
*/

