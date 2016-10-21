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

using namespace std;

//c++ directives
#include <unordered_map>
#include <vector>
#include <iostream>
#include <algorithm>
#define numThreads 4


#include "type.h"
unordered_map<long long int, vector<BLOCK>> collisionTable;
long long int *keys;
double **mat;


#include "finalNeighbors.cpp"



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
*/
void pushToCollisionTable(vector<vector<int>> c, vector<ELEMENT> vect){
    int numOfElements =4;
    omp_lock_t writelock;
    omp_init_lock(&writelock);

    
// for each combinations generated in c, obtain the combination indices' elements from vect, the neighborhood, and generate blocks from them
// to be inserted to the collision table
#pragma omp parallel for num_threads(numThreads)
    for(int k = 0; k < c.size(); k++) {

        //for each element index in a combo generated, access vect to get the appropriate element in the neighborhood 
        //and put the row in the element list. and to get the keySum from keys array from the row index
        long long int keysSum = 0;
        BLOCK newBlock;

        for (int j = 0; j < numOfElements; j++) {

            ELEMENT el = vect[c[k][j]];

            newBlock.rowIds.push_back(el.row);
            newBlock.col = el.col;
            keysSum += keys[el.row];


        }

        //add to collision table, if it doesn't exist, it makes a new entry

        omp_set_lock(&writelock);//prevents other threads writing to the same location
        collisionTable[keysSum].push_back(newBlock);

        omp_unset_lock(&writelock);
    }   omp_destroy_lock(&writelock);
}



/*
Generate blocks given a vector of ELEMENTS and pivot. v.size() -1 because it also contains the pivot at the end of the vector of ELEMENTS
*/
int genBlocks(vector<ELEMENT> v, int pivot ){

    //2 combos vectors for block generations and to prevent redundant blocks
    vector<vector<int>> combos1;
    vector<vector<int>> combos2;
    int r =4;
    int blocksGen = 0;
    omp_lock_t writelock;
    omp_init_lock(&writelock);

    //if pivot is the same value as the v's size, then go straight ahead and generate the combos for whole ELEMENT vector
    if(pivot==v.size()-1){

        combos1 = genCombos( ((int)v.size())-1, r);

        pushToCollisionTable(combos1, v);

    
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


                            omp_set_lock(&writelock);
                            //add the combined combo into the combinedCombos vector
                            combinedCombos.push_back( aCombinedCombo );
                            omp_unset_lock(&writelock);
                        }   omp_destroy_lock(&writelock);


                    }

                    //After all of the combinedCombos have been generated, push the combinedCombs with the neighborhood v to the 
                    //collision table
                    pushToCollisionTable(combinedCombos, v);


                }
            }


        }


    }
    return blocksGen;
}




int main(int argc, char* argv[]){


    if(argc < 6 || !isdigit(argv[3][0]) || !isdigit(argv[4][0]) ||  !isdigit(argv[5][0]) ){

        printf("Please give the correct arguments: progName datafilename keysfilename rows columns dia\n");

        return -1;
    }

    
    int rows = atoi(argv[3]);
    int cols = atoi(argv[4]);
    double dia = atof(argv[5]);


    //initializing keys and mat
    keys = (long long int*)malloc(rows*sizeof(long long int));
    mat = (double**) malloc( sizeof(double *) * rows );

    for(int x=0; x < rows; x++) {
        mat[x] = (double *)malloc(sizeof(double)*cols);
    }



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
        //always restart j whenever you get a new row
        j =0;
        record = strtok(line,",");
        while(record != NULL)
        {

            //printf("recodrd: %s\n",record) ;
            mat[i][j++] = atof(record) ;
            record = strtok(NULL,",");

        }

        //increasing row number
        ++i ;

    }

    fclose(fstream);

    


    //sorting and generating the column by column
#pragma omp num_threads(numThreads) for schedule(static)
    for(int k = 0; k < cols; k++ ){

    vector<ELEMENT> justAColumn(rows);
    
    for(int x = 0 ; x < rows; x++){

        ELEMENT el;
        el.row = x;
        el.col = 0;
        el.datum =  mat[x][k];


        justAColumn[x] = el;

        

    }



    //call finalneighbors function (getNeighbors) where the column will be sorted in the function. Returns a list of neighborhoods
    vector<vector<ELEMENT>> output = getNeighbours(justAColumn, dia);


    for(int k = 0; k < output.size(); k ++){

        genBlocks(output[k], (output[k][output[k].size()-1]).datum );
    }




}



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
}
