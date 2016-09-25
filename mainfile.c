#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ROWS 4400
#define COLS 500

static int lowToHigh(const void *a, const void *b){
  double xx = *(double*)a, yy=*(double*)b;
  if (xx < yy) return -1;
  if (xx > yy) return 1;
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
      j =0;
    	record = strtok(line,",");
     while(record != NULL)
     {
     
     //printf("recodrd: %s\n",record) ; 
     mat[i][j++] = atof(record) ;
     record = strtok(NULL,",");
     
     }
     ++i ;
     
   }

   

   //sorting the column by column
   
   static double justAColumn[ROWS];
   for(int x = 0 ; x < ROWS; x++){

    
        justAColumn[x] = mat[x][0];
     
 }


 qsort(justAColumn, ROWS, sizeof(justAColumn[0]), lowToHigh);

 for (int x = 0; x < ROWS; ++x)
 {
   printf("%f\n", justAColumn[x]);
 }

}


