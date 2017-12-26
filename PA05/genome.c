#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static void loadSize (char * filename, int * n, int * m)
{
	FILE * fp = fopen(filename, "rb");

	int num[2] = {0,0};
	fread(num, sizeof(int), 2, fp);
	int cols = num[0];
	int rows = num[1];
	*n = cols;
	*m = rows;

	fclose(fp);
}

static void loadFile (char * filename, int cols, int rows, int ** seqs)
{
	FILE * fp = fopen(filename, "rb");

	int num[2] = {0,0};
	fread(num, sizeof(int), 2, fp);

	int i = 0;
	int j = 0;
	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < cols; j++)
		{
			fread(&seqs[i][j], sizeof(int), 1, fp);
		}
	}

	fclose(fp);

}

static int checkSeq(int ** seqs, int * curTop_posn, int curMax, int * max, int * maxSeq, int cols, int rows)
{

	int s1_curNum = seqs[0][curTop_posn[0]];
	
	int found = 0;
	int i = 0;
	int j = 0;
	int * nextTop_posn = malloc(sizeof(int) * cols);
	
	for(i = 1; i < rows; i++)
	{
		if(curTop_posn[i] > cols)
		{
			free(nextTop_posn);
			return 0;
		}

		found = 0;
		for(j = curTop_posn[i]; (j < cols) && (found == 0); j++)
		{
			if(seqs[i][j] == s1_curNum)
			{
				found = 1;
				//printf("%d ", s1_curNum);
				nextTop_posn[i] = j+1;
			}
		}

		if(found == 0)
		{
			free(nextTop_posn);
			return 0;
		}
	}


	//UPDATE MAX
	curMax = curMax + 1;
	int maxChanged = 0;
	if(curMax > *max)
	{
		*max = curMax;
		maxChanged = 1;
	}

	
	for(nextTop_posn[0] = curTop_posn[0] + 1; nextTop_posn[0] < cols; nextTop_posn[0]++)
	{
		if(checkSeq(seqs, nextTop_posn, curMax, max, maxSeq, cols, rows))
		{
			maxChanged = 1;
		}
	}

	if(maxChanged)
	{
		maxSeq[curMax - 1] = s1_curNum;
	}
	
	free(nextTop_posn);	
	
	return maxChanged;
}

	
int * Longest_conserved_gene_sequence (char * filename, int  * size_of_seq)
{
	//Check file
	FILE *file = NULL;
   	if ((file = fopen(filename, "rb")))
   	{
        	fclose(file);
    	}
	else
	{
		* size_of_seq = 0;
		return NULL;		
	}

	//load the value of row and column
	int n = 0;
	int m = 0;
	loadSize (filename, &n, &m);

	if(m > 10000 || n > 100000)
	{
		* size_of_seq = 0;
		return NULL;
	}

	//create and fill sequences matrix
	int ** seqs = malloc(sizeof(int *) * m);
	int i = 0;
	for(i = 0; i < m; i++)
	{
		seqs[i] = malloc(sizeof(int) * n);
	}
	int rows = m;
	int cols = n;
	loadFile(filename, cols, rows, seqs);

	//find longest subsequence
	int * curTop_posn = malloc(sizeof(int) * cols);
	int * maxSeq = malloc(sizeof(int) * cols);
	for(i = 0; i < cols; i++)
	{
		curTop_posn[i] = 0;
		maxSeq[i] = 0;
	}
	int curMax = 0;
	int max = 0;

	for(i = 0; i < cols; i++)
	{
		curTop_posn[0] = i;
		checkSeq(seqs, curTop_posn, curMax, &max, maxSeq, cols, rows);
	}
	
	int * longestSeq = malloc(sizeof(int) * (max));
	for(i = 0; i < max; i++)
	{
		longestSeq[i] = maxSeq[i];
	}

	//FREE VARIABLES
	free(maxSeq);
	free(curTop_posn);
	for(i = 0; i < m; i++)
	{
		free(seqs[i]);
	}
	free(seqs);

	*size_of_seq = max;

	return longestSeq;

}

		
	//printSeq(&longestSeq, max, 1);
	//printf("\n MAX: %d", max);
	//printf("\n--------------------\n RESULT:\n");


	//print the sequence to check if it is correct
	//printf("\nNumber of columns/ numbers per sequence (n) = %d \nNumber of rows/ sequences (m) = %d\n", cols, rows);
	//printSeq(seqs, cols, rows);


	/*static void printSeq(int ** seq, int cols, int rows)
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

	}*/


