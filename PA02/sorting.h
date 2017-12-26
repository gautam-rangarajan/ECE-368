
typedef struct Node{
	long value;
	struct Node *next;
}Node;

typedef struct List{
	Node *node;
	struct List *next;
}List;

Node * Load_From_File(char *);

int Save_To_File(char *, Node *);

Node * Shell_Sort(Node * list);



