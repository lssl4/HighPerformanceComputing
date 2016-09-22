#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){

//Reading in the files
FILE *fp = fopen("keys.txt", "r");
 //char buffer[1024] ;
 //char *record;
 //char *line;
 int R=0;
 //int mat[100][100];
long long keys[4400];

if(fp == NULL){
	printf("File opening failed\n");
	return -1;
}

while(fscanf(fp, "%lli",&keys[R++])>0);

	 
	
	 
	




for(int j = 0 ; j < sizeof(keys)/sizeof(long long); j ++){

	printf("%lli\n",keys[j]);
}

}


