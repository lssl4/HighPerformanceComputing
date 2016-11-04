


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
	
  vector<int> rowIds;
  int col;
	

}BLOCK;

typedef struct PROCESSES
{

  int processId;
  unsigned long long totalBlocks;
	

}PROCESS;















