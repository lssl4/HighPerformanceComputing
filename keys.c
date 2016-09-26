/*
Printing out keys.txt

*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "type.h"

#define ROWS 4400
#define COLS 500




 int lowToHigh(const void *a, const void *b){
  if ( (*((long long*)a)) > (*((long long*)b)))
    return 1;
  else if ((*((long long*)a))  < (*((long long*)b)) )
    return -1;
  else
    return 0;  

}

int main(){

//Reading in the files
FILE *fp = fopen("keys.txt", "r");



static long long keys[ROWS];

if(fp == NULL){
	printf("File opening failed\n");
	return -1;
}

//Getting every lli from the file
for(int j = 0 ; j < sizeof(keys)/sizeof(long long); j ++){

	fscanf(fp, "%lli",&keys[j]);
}


 qsort(keys, ROWS, sizeof(long long), lowToHigh);

for (int i = 0; i < ROWS; ++i)
{
	printf("%lli\n", keys[i]);
	/* code */
}


}

