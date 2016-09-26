/*
Each row directly correspond with a key in the key array. 
That is row 1 would correspond to key 1 in the key array
*/



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "type.h"

#define ROWS 4400
#define COLS 500
#define DIA 0.000001




 int lowToHigh(const void *a, const void *b){
  if ( (*((Element*)a)).datum > (*((Element*)b)).datum)
    return 1;
  else if ((*((Element*)a)).datum  < (*((Element*)b)).datum )
    return -1;
  else
    return 0;  

}

int main(){

//Reading in the files
FILE *fp = fopen("keys.txt", "r");



long long keys[ROWS];

if(fp == NULL){
	printf("File opening failed\n");
	return -1;
}

//Getting every lli from the file
for(int j = 0 ; j < sizeof(keys)/sizeof(long long); j ++){

	fscanf(fp, "%lli",&keys[j]);
}

//print out the keys
/*for(int j = 0 ; j < sizeof(keys)/sizeof(long long); j ++){

	printf("%lli\n",keys[j]);
}*/


//Getting the data.txt
char buffer[5000] ; //big enough for 500 numbers
   char *record;
   char *line;
   int i=0,j=0;

   static double mat[ROWS][COLS];
   FILE *fstream = fopen("data.txt","r");
   if(fstream == NULL)
   {
      printf("\n file opening failed ");
      return -1 ;
   }

   while((line=fgets(buffer,sizeof(buffer),fstream))!=NULL)
   {
      //always restart j whenever you get a new row
      j =0;
    	record = strtok(line,",");
     while(record != NULL)
     {
     
     //printf("recodrd: %s\n",record) ; 
     mat[i][j++] = atof(record) ;
     record = strtok(NULL,",");
     
     }

     //increasing row number
     ++i ;
     
   }

   

   //sorting the column by column
   static Element justAColumn[ROWS];
   for(int x = 0 ; x < ROWS; x++){

        Element el;
        el.row = x;
        el.col = 0;
        el.datum =  mat[x][0];


        justAColumn[x] = el;
     
    }


 qsort(justAColumn, ROWS, sizeof(Element), lowToHigh);
 printf("%s\n", "After sorting");
 for (int x = 0; x < ROWS; ++x)
 {
   printf("%f\n", justAColumn[x].datum);
 }


 //generating blocks
static Element justAColumn[] 






}


