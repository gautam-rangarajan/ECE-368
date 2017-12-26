#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sorting.h"
#include <math.h>


long *Load_From_File(char *Filename, int *Size)
{
	FILE* f = fopen(Filename, "rb");
	int count = 0; 
	long num;

	if (f == NULL){
	return NULL;
	}
	
	long * numArray = malloc(sizeof(long));	

   	while( fread(&num, sizeof(long), 1, f))
 	  {
        	count++;//counts the number of numbers to be sorted
		numArray = realloc(numArray, sizeof(long) * (count));
		numArray[count - 1] = num;//copies number by number
  	  }

	*Size = count;

   	fclose(f);
	
	return (numArray);

}

	
int Save_To_File(char *Filename, long * Array, int Size)
{
	FILE* f = fopen(Filename, "wb"); //saves to file called "Filename"
	long i;

	if (f == NULL)
	{
	return 0;
	}
	
	for (i = 0; i < Size; i++)
	{
		fwrite( &Array[i], sizeof(long), 1, f);
  	}

   	fclose(f);
	
	return (0);

}

long power(long twos, long threes)
{
	int count = 0;
  	long ans = 1;
  	for(count = 0; count < twos; count++)
 	  {
 	    ans = 2 * ans;
 	  }
 	for(count = 0; count < threes; count++)
 	  {
 	    ans = ans * 3;
 	  }
 	  return(ans); //returns an answer that corresponds to different values of sub array lengths - 2^(x)*3^(y)
}

long * subArrayCount(int Size, int * len)
{
	 *len = 0;
 	 int row = 0;
 	 int element = 0;
 	 long value = 0;
 	 long posn = 0;
 	 long * subArraySeq = malloc(sizeof(long) * Size);

	
 	for (row = 0; row < Size;row++)
 	{ 
     		element = 0;
    	 	while(element <= row)
     		{
     		   value = power(row - element,element);
     		   if (value < Size) //adds a new element to the sub array sequence only if its less than the size of the array inputted
     		   {
     	 	     subArraySeq[posn] = value;
     	 	     posn++; //adds the value to a new posn in the array
     	 	     *len = *len + 1;
     	 	   }

     	 	   else
     		   {
     	 	  	 if(power(row + 1, 0) > Size) //returns the array if the first element of the sub array sequence pyramid is greater than size
     		  	    {
        	      	   return subArraySeq;
        	   	    }
        		    element = row + 1;
                   }  
			element++;
    	       }	
	}  	
 	return subArraySeq;
}

void Shell_Insertion_Sort(long *Array, int Size, double *N_Comp, double *N_Move)
{

	int len = 0;
	long * subArrayCnt =  subArrayCount(Size, &len);
	int k = subArrayCnt[len - 1];
	int j;
	int n = Size;
	int temp_r;
	int i;
	double comps = 0;
	double swaps = 0;

	while( len > 0)
	{
	for(j = k; j < n; j++)
	{
		temp_r = Array[j];
		i = j;
		
		while ((i >= k)	&& (Array[i-k] > temp_r))
		{
			
			Array[i] = Array[i-k];
			i = i-k;
			comps++;
			swaps++;
		}
			
		comps++;
		Array[i] = temp_r;
		
	}
		len--;
		k = subArrayCnt[len];
	}
	
	* N_Comp = comps;
	* N_Move = swaps;

	free (subArrayCnt);


}


void Shell_Selection_Sort(long *Array, int Size, double *N_Comp, double *N_Move)
{

	int len = 0;
	long * subArrayCnt =  subArrayCount(Size, &len);
	int k = subArrayCnt[len - 1];
	len = len - 1;

	int j;
	int n = Size;
	long temp_r;
	double comps = 0;
	double swaps = 0;
	int posn;
	int minPosn;
	long min;
	int i;

	while( len >= 0)
	{
	for(j = 0; j < k; j++)
	{

	for(i = j; i < n; i+=k)
	{
		min = Array[i];
		posn = i;
		minPosn = i;
	
		while(posn < n)
		{
			comps++;
			if(Array[posn] < min)
			{
				min = Array[posn];
				minPosn = posn;
			}
			 posn = posn + k;
		}

		comps++;
		if(minPosn != i)
		{
			temp_r = Array[i];
			Array[i] = Array[minPosn];
			Array[minPosn] = temp_r;
			swaps = swaps + 3;
		}
	}
	}
		len--;
		k = subArrayCnt[len];
	}
	
	* N_Comp = comps;
	* N_Move = swaps;

	free (subArrayCnt);

}



int Print_Seq(char * Filename, int Size)
{
	int len = 0;
	long * subArrSeq = subArrayCount(Size, &len);
	FILE * ptr1;
		int i = 0;
	
	ptr1 = fopen(Filename, "w");

	if(ptr1 == NULL)
	{
		return 0;
	}

		for(i = 0; i < len; i++)
	 	{
		fprintf(ptr1, "%lu\n", subArrSeq[i]);	
		}

	free (subArrSeq);

	fclose (ptr1);
	return len;
}


