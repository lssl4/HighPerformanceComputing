



typedef struct ELEMENTS
{
  /* struct for each element in the matrix */
  int row;
  int col;
  double datum;

  
}ELEMENT;


typedef struct BLOCKS
{
	
	//vector<ELEMENT> elementList;
  vector<int> rowIds;
  int col;
	long long int signature;

}BLOCK;















