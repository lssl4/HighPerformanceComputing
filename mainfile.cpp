/*
Each row directly correspond with a key in the key array. 
That is row 1 would correspond to key 1 in the key array
*/


//c directives
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "type.h"

//c++ directives
#include <unordered_map>
#include <unordered_set>


#define ROWS 4400
#define COLS 500
#define DIA 0.000001
#define BLOCKLISTSIZE 400000000000




using namespace std;

unordered_map<long long int, BLOCKLIST> collisionTable;


 int lowToHigh(const void *a, const void *b){
  if ( (*((ELEMENT*)a)).datum > (*((ELEMENT*)b)).datum)
    return 1;
  else if ((*((ELEMENT*)a)).datum  < (*((ELEMENT*)b)).datum )
    return -1;
  else
    return 0;  

}

int findCombinations(unordered_set<ELEMENT, ElementKeyHasher> set){


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

   

   //sorting and generating the column by column
   //for(int k = 0; k < COLS; k++ ){
     static ELEMENT justAColumn[ROWS];
     for(int x = 0 ; x < ROWS; x++){

          ELEMENT el;
          el.row = x;
          el.col = 0;
          el.datum =  mat[x][0];


          justAColumn[x] = el;
       
      }


   qsort(justAColumn, ROWS, sizeof(ELEMENT), lowToHigh);
   printf("%s\n", "After sorting");
   for (int x = 0; x < ROWS; ++x)
   {
     printf("%f\n", justAColumn[x].datum);
   }


   //generating blocks using an array of blocks with the hashed signature index



//}
}


