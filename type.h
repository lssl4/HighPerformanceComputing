

typedef struct ELEMENTS
{
  /* struct for each element in the matrix */
  int row;
  int col;
  double datum;

  bool operator==(const ELEMENTS &other) const
  { return (row == other.row
            && col == other.col
            && datum == other.datum);
  }

}ELEMENT;


typedef struct BLOCKS
{
	
	int rowIds[4];
	int col;
	long long int signature;

}BLOCK;


typedef struct BLOCKLISTS
{
	/* data */
	BLOCK block;
	struct Lists *next;
}BLOCKLIST;




struct ElementKeyHasher
{
  std::size_t operator()(const ELEMENTS& k) const
  {
    using std::size_t;
    using std::hash;
    using std::string;

    return ((hash<int>()(k.row)^(hash<int>()(k.col) << 1)) >> 1)^(hash<double>()(k.datum) << 1);
  }
};












