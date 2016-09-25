#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ROWS 4400
#define COLS 500

typedef struct Element
{
  /* struct for each element in the matrix */
  int row;
  int col;
  double datum;

} element;

 int lowToHigh(const void *a, const void *b){
  if (*(double*)a > *(double*)b)
    return 1;
  else if (*(double*)a < *(double*)b)
    return -1;
  else
    return 0;  
}

int main(void){

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
   
   static double justAColumn[ROWS];
   for(int x = 0 ; x < ROWS; x++){

    
        justAColumn[x] = mat[x][0];
     
    }


 qsort(justAColumn, ROWS, sizeof(double), lowToHigh);
 printf("%s\n", "After sorting");
 for (int x = 0; x < ROWS; ++x)
 {
   printf("%f\n", justAColumn[x]);
 }

}


