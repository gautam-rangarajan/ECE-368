typedef struct pole{
	struct pole * o_up;
	struct pole * o_down;
	struct pole * o_left;
	struct pole * o_right;
	struct pole * pred;
	int row;
	int col;
	int dist;
	int i_up;
	int i_down;
	int i_left;
	int i_right;
	int board;
}pole;



void loadSize (char * , int * , int * );
void loadFile (char * , int , int , int ** );
void printSeq(int ** seq, int cols, int rows);
void printGraph(pole * firstPole);
pole * createPole(int row, int col, int ** list);
pole * createGraph (int rows, int cols, int ** list);
void genQueue(pole * firstPole, int rows, int cols, pole ** PQ);
void downwardHeapify (pole ** PQ, int i, int rows, int cols);
pole * dequeue(pole ** PQ, int * last);
void shortestPathHelper(pole * curPole, pole ** PQ, int * last);
void shortestPath(pole * firstPole, int rows, int cols);
int findMin(pole * firstPole);
void destroyBoardList( int ** , int, int);
void destroyGraph(pole * firstPole);
int exists(const char * filename);
