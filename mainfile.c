#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){

//Reading in the files
FILE *fp = fopen("keys.txt", "r");
 char buffer[1024] ;
 char *record,*line;
 int R=0;
 int mat[100][100];
long keys[4400];

if(fp == NULL){
	printf("\nFile opening failed\n");
	return -1;
}


while((line = fgets(buffer,sizeof(buffer), fp) ) != NULL){

	record = strtok(line, "\n");
	keys[R++] = atol(record);
	


}

for(int j = 0 ; j < R; j ++){

	printf("%lld\n",keys[j]);
}

}


