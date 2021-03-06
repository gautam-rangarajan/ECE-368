typedef struct treeNode{
	struct treeNode * left;
	struct treeNode * right;
	double width;
	double height;
	double x_coord;
	double y_coord;
	int label;
	char cutline;
}treeNode;

typedef struct Stack{
	treeNode ** stk;
	int top;
	int size;
}Stack;


void printTreeNode(treeNode *);
void printPostorder(treeNode *);
void savePostOrder(treeNode *, char *);
int exists(const char *);
void savePostOrderHelper(treeNode *, FILE *);
int checkCutline(treeNode *);
Stack * createStack(int);
int countlines(char *);
int isEmpty(Stack *);
void push(Stack *, treeNode *);
treeNode * findMaxNode (treeNode *, treeNode *);
treeNode * createNodeBox(int, double, double);
treeNode * createNodeCutline(char);
treeNode * createTree(char *);
double max(double, double);
void calcXYhelper(treeNode *);
void calcXY(treeNode *, double *, double *);
void destroyTree(treeNode *);
void checkInputs(treeNode *, int *);

