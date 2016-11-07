


 /* struct for each element in the matrix */
typedef struct ELEMENTS
{

  int col;
  int row;

  
  long double datum;

  
}ELEMENT;

/*struct for BLOCKS containing the elements' rowIds and column location*/
typedef struct BLOCKS
{
	
  int rowIds[4];
  int col;
  long long int sum;
	

}BLOCK;

typedef struct PROCESSES
{

  int processId;
  unsigned long long totalBlocks;
	

}PROCESS;















