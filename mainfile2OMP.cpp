/*
This is the main file of our C++ implemented matrix collision program. This file requires other files such as finalNeighbors.cpp and type.h.
Require argument line arugments: ./(progname) data.txt keys.txt rows columns dia

This program generate blocks from columns of data with the same neighborhood.
Each row in the data text directly correspond with a key in the key array with the same index. 
*/


//c directives
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <mpi.h>

using namespace std;

//c++ directives
#include <unordered_map>
#include <vector>
#include <iostream>
#include <algorithm>
#define numThreads 4


#include "type.h"
unordered_map<long long int, vector<BLOCK>> collisionTable;
vector<PROCESS> allTheProcesses;
long long int *keys;
double **mat;


#include "finalNeighbors.cpp"


double **alloc_2d_double(int rows2d, int cols2d) {
    double *data = (double *)malloc(rows2d*cols2d*sizeof(double));
    double **array= (double **)malloc(cols2d*sizeof(double*));
    for (int i=0; i<cols2d; i++)
        array[i] = &(data[rows2d*i]);

    return array;
}

int **alloc_2d_int(int rows2d, int cols2d){

   

    int *data = (int *)malloc(rows2d*cols2d*sizeof(int));
    int **array= (int **)malloc(rows2d*sizeof(int*));
    for (int i=0; i<rows2d; i++)
        {array[i] = &(data[cols2d*i]);}


    return array;
}

ELEMENT **alloc_2d_element(int rows2d, int cols2d){

   

    ELEMENT *data = (ELEMENT *)malloc(rows2d*cols2d*sizeof(ELEMENT));
    ELEMENT **array= (ELEMENT **)malloc(rows2d*sizeof(ELEMENT*));
    for (int i=0; i<rows2d; i++)
        {array[i] = &(data[cols2d*i]);}


    return array;
}



int** vectorTo2DArray(vector<vector<int>> v){


    int n = v.size();
    int m = v[0].size();

     

    int** contInt2dArray = alloc_2d_int(n,m);

    
    //populate contiguous 2d array
    for(int x = 0 ; x < n; x++){

        for(int y = 0 ; y < m ; y++){

                contInt2dArray[x][y] = v[x][y];

        }

    }

   // cout << "n: " << n << " m: " << m<< "hello"<<endl;
   
    return contInt2dArray;

}




/*
Generate all the combinations of indices given an integer n and choosing r.
*/
vector<vector<int>> genCombos(int n, int r) {
    vector<int> eachCom;
    vector<vector<int>> listOfCombos;
    //generates the eachCom with numbers up to r
    for (int i = 0; i < r; i++){

        eachCom.push_back(i);

    }

    if(r-1 >= 0){
        while (eachCom[r - 1] < n) {

            //put the just generated combo into the listOfCombos
            listOfCombos.push_back(eachCom);


            int t = r - 1;
            while (t != 0 && eachCom[t] == n - r + t) t--;
            eachCom[t]++;
            for (int i = t + 1; i < r; i++) eachCom[i] = eachCom[i - 1] + 1;
        }
    }



    return listOfCombos;
}

/*
After the 4 element combinations called blocks have been generated and modified, 
Assign and declare each combinations to a Block type and push to the global variable hashmap, collisionTable 
c is the list of block combinations. vect is the vector of neighborhood
*/
void pushToCollisionTable(BLOCK *givenBlockList, int blockListSize){
    //int numOfElements =4;


    omp_lock_t writelock;
    omp_init_lock(&writelock);


#pragma omp parallel for num_threads(numThreads)
    for(int k = 0; k < blockListSize; k++) {

       
        BLOCK b = givenBlockList[k];

 

        //add to collision table, if it doesn't exist, it makes a new entry
        omp_set_lock(&writelock);//prevents other threads writing to the same location
        collisionTable[b.sum].push_back(b);

        omp_unset_lock(&writelock);
    
    }   

    omp_destroy_lock(&writelock);
}


/*
Generates a list of blocks from the given combination and neighborhood. Returns the list of BLOCKS to be inserted into the hashmap.
c is the list of block combinations. neigh is the vector of neighborhood
*/
BLOCK* genBlocks(vector<vector<int>> c, vector<ELEMENT> neigh){
    int numOfElements =4;
    int cSize = c.size();
    BLOCK* listOfBlocks = (BLOCK*) malloc(cSize*sizeof(BLOCK));


    //for each block combination
    for(int k = 0; k < cSize; k++) {

        //for each element index in a combo generated, access neigh to get the appropriate element in the neighborhood 
        //and put the row in the block rowIds list. 
        BLOCK newBlock;
        long long int keysSum = 0;

        for (int j = 0; j < numOfElements; j++) {

            ELEMENT el = neigh[c[k][j]];

            newBlock.rowIds[j] = el.row;
            newBlock.col = el.col;
             keysSum += keys[el.row];
            
        }

        newBlock.sum = keysSum;

        //inserting it into an array
        listOfBlocks[k] = newBlock;
    
    } 


    return listOfBlocks;

}





/*
Generate blocks given a vector of ELEMENTS and pivot. v.size() -1 because it also contains the pivot at the end of the vector of ELEMENTS
Returns the list of block combinations index
*/
 vector<vector<int>> genBlockCombinations(vector<ELEMENT> v, int pivot ){

    //2 combos vectors for block generations and to prevent redundant blocks
    vector<vector<int>> combos1;
    vector<vector<int>> combos2;
    int r =4;
   
   /*cout << "new neighborhood" << endl;
   for(int x = 0 ; x < v.size(); x++){
        cout << v[x].datum << endl;
   }*/



    //if pivot is the same value as the v's size, then go straight ahead and generate the combos for whole ELEMENT vector
    if(pivot==v.size()-1){

        combos1 = genCombos( ((int)v.size())-1, r);





        return combos1;

    
    //else if there's a pivot
    }else{


        if(pivot <(v.size() -1)&& pivot >= 0 ){
            for(int k = 0 ; k < r; k++){

                int n1 = pivot;
                int r1 = r-k-1;
                int n2 = (int)((v.size()-1)-pivot);
                int r2 = k+1;

                if( r1<=n1 &&r1 >=0 &&r2<=n2 &&r2 >=0 ){
                    vector<vector<int>> combinedCombos;


                    //iteratively decreasing r for the first combos
                    combos1 = genCombos(pivot, r-k-1);

                    //iteratively increasing r for the second combos
                    combos2 = genCombos((int)((v.size()-1)-pivot), k+1);




                    //adding all of the combos by pivot number in combos2 to match the latter half of array indices
                    #pragma omp parallel for
                    for(int x = 0; x < combos2.size() ; x++){
                        vector<int>eachCom = combos2[x];

                        //adding each element in eachCom by pivot
                        for(int y = 0 ; y < eachCom.size(); y++){

                            eachCom[y] += pivot;

                        }

                        combos2[x] = eachCom;

                    }


                    //after producing 2 sets of combos, combined them in a permutative manner
                   #pragma omp parallel for num_threads(numThreads) schedule(static)
                    for(int l = 0 ; l < combos1.size() ; l++){
                        vector<int> combA = combos1[l];


                        for(int m = 0 ; m  < combos2.size(); m++){
                            vector<int> aCombinedCombo;

                            vector<int> combB = combos2[m];


                            //inserting combos1 first

                            aCombinedCombo.insert(aCombinedCombo.end(),combA.begin(), combA.end());

                            //inserting combos2 second

                            aCombinedCombo.insert(aCombinedCombo.end(),combB.begin(), combB.end());


                           
                            //add the combined combo into the combinedCombos vector
                            combinedCombos.push_back( aCombinedCombo );
                            
                        }   


                    }

                    //After all of the combinedCombos have been generated, push the combinedCombs with the neighborhood v to the 
                    //collision table
                   return combinedCombos;


                }
            }


        }


    }
}


unsigned long long combosCalc(unsigned long long n, unsigned long long k) {
    if (k > n) {
        return 0;
    }
    unsigned long long r = 1;
    for (unsigned long long d = 1; d <= k; ++d) {
        r *= n--;
        r /= d;
    }
    return r;
}

//Comparison function to compare each process's blocksToBeGenerated value
bool lowHighProcesses (PROCESS i, PROCESS j) {
    return (i.totalBlocks<j.totalBlocks);
}


int main(int argc, char* argv[]){

    int numprocs, myid, master = 0, blocksToBeGenerated =0; 

    //more declarations
    //MPI_Status status;
    int rows, cols;
    double dia;
    int sendProcessId;
    int stopComplete =1; // 0 means false, 1 means true
    int rc;
    int chunklength;
    int tag1;
    int tag2;
    int dest;
    int source;
    int offset;


    //Processing work variables
    int neighboursSize;
    int blockCombosSize;
    ELEMENT** listOfNeighborhoods;
    BLOCK* blockList;

   
    MPI_Status status;



     //starting mpi here
     MPI_Init(&argc,&argv);
     MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
     MPI_Comm_rank(MPI_COMM_WORLD,&myid);

     //Defining structs for MPI
    BLOCK blockExample;

    int countBlock = 3;
    //says the type of every block
    MPI_Datatype arrayOfTypes[countBlock];
    arrayOfTypes[0] = MPI_INT;
    arrayOfTypes[1] = MPI_INT;
    arrayOfTypes[2] = MPI_LONG_LONG_INT;

        //how many field variables in that struct
        int arrayOfBlocklengths[countBlock];
        arrayOfBlocklengths[0] ={4};
        arrayOfBlocklengths[1] ={1};
        arrayOfBlocklengths[2] ={1};

            //Says where every block starts in memory, counting from the beginning of the struct.
        MPI_Aint array_of_displacements[countBlock];
    
        MPI_Aint address1, address2, address3, address4;
        MPI_Get_address(&blockExample,&address1);
        MPI_Get_address(&blockExample.rowIds,&address2);
        MPI_Get_address(&blockExample.col,&address3);
        MPI_Get_address(&blockExample.sum,&address4);


        array_of_displacements[0] = address2 - address1;
        array_of_displacements[1] = address3 - address1;
        array_of_displacements[2] = address4 - address1;


        //Create MPI Datatype and commit
    MPI_Datatype block_type;
    MPI_Type_create_struct(countBlock, arrayOfBlocklengths, array_of_displacements, arrayOfTypes, &block_type);
    MPI_Type_commit(&block_type);

/*
    //for element structs setup
      //setup description for row and col

 MPI_Datatype elementtype, oldtypes[2];
    int blockcounts[2];
    MPI_Aint    offsets[2], extent;

    offsets[0] = 0;
   oldtypes[0] = MPI_INT;
   blockcounts[0] = 2;

     // setup description of the one long double
   // need to first figure offset by getting size of MPI_FLOAT
   MPI_Type_get_extent(MPI_INT, &extent);
   offsets[1] = 2 * extent;
   oldtypes[1] = MPI_LONG_DOUBLE;
   blockcounts[1] = 1;

     // define structured type and commit it. 2 because of 2 different types
   MPI_Type_struct(2, blockcounts, offsets, oldtypes, &elementtype);
   MPI_Type_commit(&elementtype);*/

  
if(argc < 6 || !isdigit(argv[3][0]) || !isdigit(argv[4][0]) ||  !isdigit(argv[5][0]) ){

        printf("Please give the correct arguments: progName datafilename keysfilename rows columns dia\n");

        return -1;
    }


    rows = atoi(argv[3]);
    cols = atoi(argv[4]);
    dia = atof(argv[5]);


      //initializing keys and mat
    keys = (long long int*)malloc(rows*sizeof(long long int));
    mat = alloc_2d_double(rows, cols);


    //Reading in the keys.txt files
    FILE *fp = fopen(argv[2], "r");



    if(fp == NULL){
        printf("File opening failed\n");
        return -1;
    }
    

//Getting every lli from the file
    for(int x = 0 ; x < rows; x++){


        fscanf(fp, "%lli", &keys[x]);
        
    }
fclose(fp);

   //error checking
   if(cols%numprocs !=0){
    printf("Quitting. Number of MPI tasks must be divisible by numprocs.\n");
    MPI_Abort(MPI_COMM_WORLD, rc);
    exit(0);
   }

   chunklength = cols/numprocs;

   tag1 = 1;
   tag2 = 2;


    //only master thread processes this code block
     if(myid == master){



//Getting the data.txt
    char buffer[5000] ; //big enough for 500 numbers
    char *record;
    char *line;
    int i=0,j=0;


    FILE *fstream = fopen(argv[1],"r");
    if(fstream == NULL)
    {
        printf("\n file opening failed ");
        return -1 ;
    }



    while((line=fgets(buffer,sizeof(buffer),fstream))!=NULL)
    {


        //always restart i (col) whenever you get a new row
        i =0;
        record = strtok(line,",");

        
        while(record != NULL)
        {

            //printf("recodrd: %s\n",record) ;
            mat[i++][j] = atof(record) ;
            /*i++;
            printf("i: %i j: %i record: %f\n", i , j , atof(record));*/
            record = strtok(NULL,",");

        }

        //increasing row number
        ++j ;

    }

    fclose(fstream);


/*for(int x =0; x < cols; x++){

    cout << x <<"th column" <<endl;
    for(int y = 0 ; y < rows ; y++){

        cout << "value: " << mat[x][y] <<endl;
    }
}*/

   
//distributing work
offset = chunklength;
for(dest= 1 ; dest < numprocs; dest++){

    MPI_Send(&offset, 1, MPI_INT, dest,
                        tag1, MPI_COMM_WORLD);
    MPI_Send(&(mat[offset][0]), chunklength*rows, MPI_DOUBLE,
                    dest, tag2, MPI_COMM_WORLD);

    offset += chunklength;
    
}

//Master process its own work
offset = 0;

for(int k = offset; k < offset + chunklength; k++ ){


    vector<ELEMENT> justAColumn(rows);
    
    for(int x = 0 ; x < rows; x++){

        ELEMENT el;
        el.row = x;
        el.col = 0;
        el.datum =  mat[k][x];


        justAColumn[x] = el;

        

    }


//call finalneighbors function (getNeighbors) for the column. Returns a list of neighborhoods in that column
vector<vector<ELEMENT>> output = getNeighbours(justAColumn, dia);

 for(int l = 0; l < output.size(); l++){

        vector<vector<int>> blockCombos = genBlockCombinations(output[l], (output[l][output[l].size()-1]).datum );

        //once the block combinations have been received, generate the blocks from them
        blockList= genBlocks(blockCombos, output[l]);

         //push the blocks to collision table
         pushToCollisionTable(blockList, sizeof(blockList)/sizeof(blockList[0]) );
        
}


}//end of master processing its own work


//receiving results from other processes
         for(int x=1; x<numprocs;x++) {
                               

             source = x;
             //for each column that a process is responsible for 
             for(int y=0; y<chunklength;y++){

                //gets how many neighborhoods there are for that column
                 MPI_Recv(&neighboursSize,1, MPI_INT,source,tag1,MPI_COMM_WORLD,&status);


                 //for each neighborhood in that column, get the genrated blocks if neighboursSize is 0, it doesn't go into this for loop and gets the next column
                 for(int z=0; z < neighboursSize; z++ ){
                    
                     //obtains the size of the list of Block combinations
                     MPI_Recv(&blockCombosSize, 1, MPI_INT, source, tag1, MPI_COMM_WORLD,
                              &status);
                     
                     //Receiving the list of blocks generated
                     MPI_Recv(&blockList, blockCombosSize, block_type, source, tag2, MPI_COMM_WORLD, &status);

                     //once the list of block combinations are received, push to collision table                     
                     //pushToCollisionTable(blockList, blockCombosSize);

                     



                 }
                 
                 
             }

         }



    //sorting and generating the column by column
//#pragma omp num_threads(numThreads) for schedule(static)

   
  /*  for(int k = 0; k < cols; k++ ){


    vector<ELEMENT> justAColumn(rows);
    
    for(int x = 0 ; x < rows; x++){

        ELEMENT el;
        el.row = x;
        el.col = 0;
        el.datum =  mat[k][x];


        justAColumn[x] = el;

        

    }



    //call finalneighbors function (getNeighbors) where the column will be sorted in the function. Returns a list of neighborhoods
    vector<vector<ELEMENT>> output = getNeighbours(justAColumn, dia);


    //allocate the neighbors to the nodes that have the least amount of work
    for(int k = 0 ; k < output.size(); k++){

        //sort the vector before allocating the neighborhoods to other processses to find the process that has the least amount of blocks
        sort(allTheProcesses.begin(), allTheProcesses.end(), lowHighProcesses);

        //the process that has the least amount of blocks to be processed 
        PROCESS leastWork = allTheProcesses.front();

        sendProcessId = 1;//leastWork.processId;
        

        unsigned long long totalCombinations = combosCalc(output.size(), 4);
    
        leastWork.totalBlocks += totalCombinations;

        //producing an vector of primitive types for it to be sent to through MPI sending

        //sending the neighborhood to the leastWork process id
        int neighSize= static_cast<int>(output[k].size());
        
 cout << "k: " << k<<endl;

       // MPI_Send(&neighSize, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
       
       // MPI_Send(&output[k], output[k].size(), element_type, leastWork.processId, 2, MPI_COMM_WORLD);

        cout << "NeighSize: "<<neighSize << endl;


    }



    for(int k = 0; k < output.size(); k ++){

        genBlocks(output[k], (output[k][output[k].size()-1]).datum );
    }




    }*/

         //do mpi barrier here to make sure all proceses have been finished

        // stopComplete = 0;
        // MPI_Barrier(MPI_COMM_WORLD);
   // MPI_Bcast(&stopComplete, 1, MPI_INT ,   0, MPI_COMM_WORLD);




}//end of master section


//Non master section only
if(myid >master){

    MPI_Recv(&offset, 1, MPI_INT, master, tag1, MPI_COMM_WORLD, &status);
    MPI_Recv(&(mat[offset][0]), chunklength*rows, MPI_DOUBLE, master, tag2, MPI_COMM_WORLD, &status);

    //create neighbourhoods, then send neighbourhoods to generate blocks
    vector <ELEMENT> justAColumn(rows);

    //for each column in that chunk
    for(int k = offset; k < offset+chunklength; k++ ) {
        for (int x = 0; x < rows; x++) {

            ELEMENT el;
            el.row = x;
            el.col = 0;
            el.datum = mat[k][x];


            justAColumn[x] = el;
        }


        /*for(int l = 0 ; l < justAColumn.size() ; l++){
            cout<< "value: "<<justAColumn[l].datum << endl;
        }*/

        vector<vector<ELEMENT>> output = getNeighbours(justAColumn, dia);

        /*for(int l = 0 ; l < output.size() ; l ++){
            cout << "the output[l]. size is: " << output[l].size() << endl;
            for(int m = 0 ; m < output[l].size() ; m ++){
                cout << "value: "<<output[l][m].datum << endl;
            }
        }*/

        neighboursSize = output.size();
        //sends info to master process about the amount of neighbourhoods
        MPI_Send(&neighboursSize, 1,MPI_INT,master,tag1,MPI_COMM_WORLD);

        


        //for each neighborhood in that column
        for(int l = 0; l < neighboursSize; l ++){
            
            
            
            vector<vector<int>> blockCombos = genBlockCombinations(output[l], (output[l][output[l].size()-1]).datum );

            /*for(int m =0 ; m < blockCombo.size(); m++){
                for(int n =0 ; m < blockCombo[m].size(); m++){
                    cout << blockCombo[m][n] << endl;
                }
            }*/

            //the amount of block combinations in that neighborhood
            blockCombosSize = blockCombos.size();


            MPI_Send(&blockCombosSize, 1, MPI_INT, master,tag1, MPI_COMM_WORLD);

            //int **blockCombos2dArray = vectorTo2DArray(blockCombos);
           // MPI_Send(&(blockCombos2dArray[0][0]),blockCombosSize*4, MPI_INT, master, tag2, MPI_COMM_WORLD);

            //Now generate blocks from the block combinations
            blockList = genBlocks(blockCombos, output[l]);

            //Now we can send the list back to the master process
            MPI_Send(&blockList, sizeof(blockList)/sizeof(blockList[0]), block_type, master, tag2, MPI_COMM_WORLD);



        }

        
    }





  //generate the neighbours from the data received from main, then call gen blocks to create blocks
  // and return the blocks to master node


//calling genBlockCombinations to get a list of block combinations
//genBlockCombinations()







}//End of non master processes work






//printing out collision table summary

   int collisionSum = 0;
   int blocksGen = 0;
     for ( auto it = collisionTable.begin(); it != collisionTable.end(); ++it )
      { 

        //for each key add their value size
        blocksGen += (*it).second.size();

        if((*it).second.size() > 1){
            collisionSum++;
        }


    }


    cout<< "collisionSum: "<< collisionSum << " BlocksGen: " << blocksGen<<endl ;
    free(keys);
    free(mat);

    MPI_Finalize();
}
