#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "river.h"

void loadSize (char * filename, int * rows, int * cols)
{
	FILE * fp = fopen(filename, "r");

	fscanf(fp, "%d %d", rows, cols);

	fclose(fp);
}

void loadFile (char * filename, int rows, int cols, int ** boardList)
{
	FILE * fp = fopen(filename, "rb");
	int i = 0;
	int j = 0;
	char ch = 0;

	fscanf(fp, "%d %d", &i, &j); //Just to skip the first row
	ch = fgetc(fp);

	for(i = 0; i < rows - 1; i++)
	{
		for(j = 0; j < cols; j++)
		{
			ch = fgetc(fp);
			if(ch == '\n')
			{
				ch = fgetc(fp);
			}
			boardList[i][j] = (int)ch - 48;
		}
	}

	fclose(fp);

}

void printSeq(int ** seq, int cols, int rows)
{
	int i = 0;
	int j = 0;
	printf("\n");
	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < cols; j++)
		{
			printf("%d ", seq[i][j]);
		}
		printf("\n");
	}

}

void printGraph(pole * firstPole)
{
	pole * colPole = firstPole;
	pole * rowPole = firstPole;
	
	while(rowPole != NULL)
	{
		while(colPole != NULL)
		{
			printf("(%d, %d)->%d   ", colPole->row, colPole->col, colPole->dist);
			colPole = colPole->o_right;		
		}

		printf("\n");
		rowPole = rowPole->o_down;
		colPole = rowPole;
	}
}

pole * createPole(int row, int col, int ** list)
{
	pole * newPole = malloc(sizeof(pole));
	newPole->o_up = NULL;	
	newPole->o_down = NULL;	
	newPole->o_left = NULL;	
	newPole->o_right = NULL;
	newPole->pred = NULL;	
	newPole->i_up = 0;
	newPole->i_down = 0;
	newPole->i_left = 0;
	newPole->i_right = 0;
	newPole->dist = 10 * col;
	newPole->row = row;
	newPole->col = col;
	
	if(list[row][col] == 1)
	{
		newPole->board = 1;
	}
	else
	{
		newPole->board = 0;
	}

	return newPole;
}



pole * createGraph (int rows, int cols, int ** list)
{
	int i = 0;
	int j = 0;

	//Create the first column of poles
	pole * newPole = createPole(i, 0, list);
	pole * tempPole = newPole;
	pole * firstPole = newPole;

	for(i = 1; i < rows; i++)
	{
		newPole = createPole(i, 0, list);
		tempPole->o_down = newPole;
		newPole->o_up = tempPole;
		tempPole = newPole;
	}
	
	//Create and attach the first row of poles to the first column of poles
	newPole = firstPole;
	tempPole = newPole;

	for(j = 1; j < cols; j++)
	{
		newPole = createPole(0, j, list);
		tempPole->o_right = newPole;
		newPole->o_left = tempPole;
		tempPole = newPole;
	}

	//Create the remaining poles
	pole * leftPole = firstPole->o_down;
	pole * upPole = firstPole->o_right;
	pole * next_leftPole = leftPole;
	pole * next_upPole = upPole;

	for(j = 1; j < cols; j++)
	{
		leftPole = next_leftPole;
		upPole = next_upPole;

		for(i = 1; i < rows; i++)
		{
			newPole = createPole(i, j, list);
			leftPole->o_right = newPole;
			newPole->o_left = leftPole;
			upPole->o_down = newPole;
			newPole->o_up = upPole;
			leftPole = leftPole->o_down;
			upPole = upPole->o_down;
		}

		next_leftPole = next_leftPole->o_right;
		next_upPole = next_upPole->o_right;
	}
		
	
	return firstPole;
}


void downwardHeapify (pole ** PQ, int i, int rows, int cols)
{
	int parent = i;
	int n = rows * cols-1;
	pole * temp = PQ[i];
	int child = 2 * parent + 1;

	while(child <= n)
	{
		if(child + 1 <= n && PQ[child]->dist > PQ[child + 1]->dist)
		{
			child = child + 1;
		}

		if(temp->dist <= PQ[child]->dist)
		{
			break;
		}
		else
		{
			PQ[parent] = PQ[child];
			parent = child;
			child = 2 * parent + 1;
		}
	}
	
	PQ[parent] = temp;
		
}


pole * dequeue(pole ** PQ, int * last)
{
	pole * temp = PQ[0];
	PQ[0] = PQ[*last];
	*last = *last - 1;
	downwardHeapify(PQ, 0, 1, *last); //last+1 is the number of columns

	return temp;
}


void genQueue(pole * firstPole, int rows, int cols, pole ** PQ)
{

	int i = 0;
	int rowNum = 0;
	int colNum = 0;
	pole * curPole = firstPole;
	

	for(i = 0; i < rows*cols ; i++)
	{
	
		for(rowNum = i/cols; rowNum > 0; rowNum--)
		{
			curPole = curPole->o_down;
		}
		for(colNum = i%cols; colNum > 0; colNum--)
		{
			curPole = curPole->o_right;
		}

		PQ[i] = curPole;
		curPole = firstPole;
	}

	
	int n = rows * cols - 1;
	for(i = (n-1)/2; i >= 0; i--)
	{
		downwardHeapify(PQ, i, rows, cols);
	}

	return;
}



void shortestPathHelper(pole * curPole, pole ** PQ, int * last)
{
	if(curPole == NULL)
	{
		return;
	}
	
	//pole * curPoleTemp = NULL;
	pole * upPole = curPole->o_up;
	pole * downPole = curPole->o_down;
	pole * leftPole = curPole->o_left;
	pole * rightPole = curPole->o_right;

	int downDist = 1;
	int upDist = 1;
	int leftDist = 1;
	int rightDist = 1;


	//calculating up,down,left and rights distance from current node
	if(curPole->i_left == 1)
	{
		rightDist = 2;
	}
	else if(curPole->i_up == 1)
	{
		downDist = 2;
	}
	else if(curPole->i_down == 1)
	{
		upDist = 2;
	}
	else if(curPole->i_right == 1)
	{
		leftDist = 2;
	}

	if(curPole->board == 1)
	{
		leftDist = 1;
		rightDist = 1;
		downDist = 0;
	}

	if(curPole->o_up != NULL && curPole->o_up->board == 1)
	{
		upDist = 0;
		rightDist = 1;
		leftDist = 1;
	}

	//Checking the overall distance for downPole
	if(downPole != NULL)
	{
		if(downPole->dist > curPole->dist + downDist)
		{
			downPole->dist = curPole->dist + downDist;
			downPole->i_up = 1;
		}
	}

	//Checking the overall distance for upPole
	if(upPole != NULL)
	{
		if(upPole->dist > curPole->dist + upDist)
		{
			upPole->dist = curPole->dist + upDist;
			upPole->i_down = 1;
		}
	}

	//Checking the overall distance for rightPole
	if(rightPole != NULL)
	{
		if(rightPole->dist > curPole->dist + rightDist)
		{
			rightPole->dist = curPole->dist + rightDist;
			rightPole->i_left = 1;
		}
	}

	//Checking the overall distance for leftPole
	if(leftPole != NULL)
	{
		if(leftPole->dist > curPole->dist + leftDist)
		{
			leftPole->dist = curPole->dist + leftDist;
			leftPole->i_right = 1;
		}
	}

	pole * nextPole = dequeue(PQ, last);
	
	if(*last > 0)
	{
		shortestPathHelper(nextPole, PQ, last);
	}

	return;

}


void shortestPath(pole * firstPole, int rows, int cols)
{

	pole * curPole = firstPole;
	
	//set the distance for all the poles in the first column as 1
	while(curPole != NULL)
	{
		curPole->dist = 1;
		curPole->i_left = 1;
		curPole = curPole->o_down;
	}
	curPole = firstPole;

	//Create Priority Queue
	pole ** PQ = malloc(sizeof(pole*) * rows * cols);
	genQueue(curPole, rows, cols, PQ);
	int last = rows * cols - 1;

	//Update shortest distance in graph
	curPole = firstPole;
	shortestPathHelper(curPole, PQ, &last);

	free(PQ);

}


int findMin(pole * firstPole)
{
	pole * curPole = firstPole;

	while(curPole->o_right != NULL)
	{
		curPole = curPole->o_right;
	}

	int min = curPole->dist;

	while(curPole != NULL)
	{
		if(curPole->dist < min)
		{
			min = curPole->dist;
		}

		curPole = curPole->o_down;

	}

	return min;
}	


void destroyBoardList( int ** boardList, int rows, int cols)
{

	int i = 0;
	for(i = 0; i < rows; i++)
	{
		free(boardList[i]);
	}

	free(boardList);

	return;
}


void destroyGraph(pole * firstPole)
{
	pole * curRow = firstPole;
	pole * nextRow = firstPole;
	pole * curPole = curRow;
	pole * nextPole = curPole;

	while(curRow != NULL)
	{
		nextRow = nextRow->o_right;
		curPole = curRow;
		nextPole = curPole;

		while(curPole != NULL)
		{
			nextPole = nextPole->o_down;
			free(curPole);
			curPole = nextPole;	
		}

		
		curRow = nextRow;
	}

	return;
}

int exists(const char * filename)
{
    FILE *file;

    if ((file = fopen(filename, "r")))
    {
        fclose(file);
        return 1;
    }
    return 0;
}
		
