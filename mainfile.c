#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){

//Reading in the files
FILE *fp = fopen("keys.txt", "r");



long long keys[4400];

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

   static double mat[4400][500];
   FILE *fstream = fopen("data.txt","r");
   if(fstream == NULL)
   {
      printf("\n file opening failed ");
      return -1 ;
   }

   while((line=fgets(buffer,sizeof(buffer),fstream))!=NULL)
   {
    	record = strtok(line,",");
     while(record != NULL)
     {
     
     //printf("recodrd: %s\n",record) ; 
     mat[i][j++] = atof(record) ;
     record = strtok(NULL,",");
     
     }
     ++i ;
     
   }

  /* for(int x = 0 ; i < 100; x++){
   		for(int y = 0 ; j < 100; y++){

   			printf("%f ", mat[x][y]);
   		}
   		printf("\n");
   }*/

}


