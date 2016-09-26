


typedef struct ELEMENTS
{
  /* struct for each element in the matrix */
  int row;
  int col;
  double datum;

}ELEMENT;


typedef struct BLOCKS
{
	
	int rowIds[4];
	int col;
	long long signature;

}BLOCK;


typedef struct BLOCKLISTS
{
	/* data */
	BLOCK block;
	struct Lists *next;
}BLOCKLIST;




