


 /* struct for each element in the matrix */
typedef struct ELEMENTS
{

  int row;
  int col;
  
  long double datum;

  
}ELEMENT;

/*struct for BLOCKS containing the elements' rowIds and column location*/
typedef struct BLOCKS
{
	
  vector<int> rowIds;
  int col;
	

}BLOCK;















