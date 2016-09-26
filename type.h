


typedef struct Elements
{
  /* struct for each element in the matrix */
  int row;
  int col;
  double datum;

}Element;

typedef struct LinkedList
{
	/* data */
	Element el;
	struct LinkedList *next;
}List;


/*typedef struct Blocks
{
	
	int rowIds[4];
	long long
}Block;
*/
