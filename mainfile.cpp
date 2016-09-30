/*
Each row directly correspond with a key in the key array. 
That is row 1 would correspond to key 1 in the key array
*/


//c directives
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

using namespace std;

//c++ directives
#include <unordered_map>
#include <vector>
//#include <unordered_set>
#include "type.h"


#define ROWS 4400
#define COLS 500
#define DIA 0.000001
//#define BLOCKLISTSIZE 400000000000




unordered_map<long long int, vector<BLOCK>> collisionTable;
long long keys[ROWS];


int lowToHigh(const void *a, const void *b){
    if ( (*((ELEMENT*)a)).datum > (*((ELEMENT*)b)).datum)
        return 1;
    else if ((*((ELEMENT*)a)).datum  < (*((ELEMENT*)b)).datum )
        return -1;
    else
        return 0;

}



/*
Generate combinations of indices.
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

    //printing out
  
    for (int i = 0; i < listOfCombos.size(); ++i)
    {   
        vector<int> comb = listOfCombos[i];
        for(int j = 0 ; j < comb.size(); j ++){
            cout << comb[j]<< " ";

        }
        cout<< "\n";
    }

    return listOfCombos;
}


/*
Generate blocks given a vector of ELEMENTS and pivot
*/
int genBlocks(vector<ELEMENT> v, int pivot){

    //2 combos vectors for block generations and to prevent redundant blocks
    vector<vector<int>> combos1;
    vector<vector<int>> combos2;
    int r =4;
    int blocksGen = 0;


    //if pivot is the same value as the v's size, then go straight ahead and generate the combos for whole ELEMENT vector
    if(pivot==v.size()){

        combos1 = genCombos((int)v.size(), r);

        //for each combos generated in combos1, ultimately get the combo elements' block and insert them to the collision table
        for(int k = 0; k < combos1.size(); k++){



            //for each element index in a combo generated, access v to get the appropriate element and put it in element list.
            //and to get the key value from keys array from the row
            long long int keysSum =0;
            BLOCK newBlock;

            for(int j = 0 ;j < r; j++){
                ELEMENT el = v[combos1[k][j]];
                newBlock.rowIds.push_back(el.row);
                newBlock.col = el.col;
                keysSum += keys[el.row];

            }

            //Assign keysSum to signature of block
            newBlock.signature = keysSum;

            //add to collision table, if it doesn't exist, it makes a new entry
            collisionTable[keysSum].push_back(newBlock);
        }

        //else if there's a pivot
    }else{

     
      if(pivot <v.size()&& pivot >= 0 ){
        for(int k = 0 ; k < r; k++){

            int n1 = pivot; 
            int r1 = r-k-1;
            int n2 = (int)(v.size()-pivot);
            int r2 = k+1;

            if( r1<=n1 &&r1 >=0 &&r2<=n2 &&r2 >=0 ){
         vector<vector<int>> combinedCombos;

         //cout <<"pivot: "<< pivot<<" for combos1: r-k-1: "<< r-k-1 << endl;

          //iteratively decreasing r for the first combos
         combos1 = genCombos(pivot, r-k-1);
        cout <<"aFter combos1"<<endl;

       // cout <<"(v.size()-pivot): "<< (int)(v.size()-pivot) <<" for combos2: k+1: "<< k+1 << endl;

         //iteratively increasing r for the second combos
         combos2 = genCombos((int)(v.size()-pivot), k+1);

         //after producing 2 sets of combos, combined them in a permutative manner 
         for(int l = 0 ; l < combos1.size() ; l++){
            vector<int> combA = combos1[l];


            for(int m = 0 ; m  < combos2.size(); m++){
                vector<int> aCombinedCombo;//(combos1[l]);
                
                vector<int> combB = combos2[m];


                //inserting combos1 first
                aCombinedCombo.insert(aCombinedCombo.end(),combA.begin(), combA.end());
                
                //inserting combos2 second
                aCombinedCombo.insert(aCombinedCombo.end(),combB.begin(), combB.end());

                //add the combined combo into combinedCombos
               combinedCombos.push_back( aCombinedCombo );

                

            }

         }

         //AFter all of the combinedCombos have been generated. get their elements and put them in hashmap
          //for each combos generated in combos1, ultimately get the combo elements' block and insert them to the collision table
        /*for(int k = 0; k < combinedCombos.size(); k++){



            //for each element index in a combo generated, access v to get the appropriate element and put it in element list.
            //and to get the key value from keys array from the row
            long long int keysSum =0;
            BLOCK newBlock;

            for(int j = 0 ;j < r; j++){
                ELEMENT el = v[combos1[i][j]];
                newBlock.rowIds.push_back(el.row);
                newBlock.col = el.col;
                keysSum += keys[el.row];

            }

            //Assign keysSum to signature of block
            newBlock.signature = keysSum;

            //add to collision table, if it doesn't exist, it makes a new entry
            collisionTable[keysSum].push_back(newBlock);
        }*/

        //printing out combinedCombos
         /*for(int n = 0 ; n < combinedCombos.size(); n ++){
                    vector<int> ve = combinedCombos[n];
                    for(int o = 0 ; o < ve.size(); o++){
                      cout << ve[o] << " " ;
                  }
                  cout << "End Line"<< endl;
                }*/

         
         } 
     }

      
    }


    }
    return blocksGen;
}




int main(){

//Reading in the files
    FILE *fp = fopen("keys.txt", "r");




    if(fp == NULL){
        printf("File opening failed\n");
        return -1;
    }

//Getting every lli from the file
    for(int j = 0 ; j < sizeof(keys)/sizeof(long long); j ++){

        fscanf(fp, "%lli",&keys[j]);
    }

//print out the keys
/*for(int j = 0 ; j < sizeof(keys)/sizeof(long long); j ++){

  printf("%lli\n",keys[j]);
}*/


//Getting the data.txt
    char buffer[5000] ; //big enough for 500 numbers
    char *record;
    char *line;
    int i=0,j=0;

    static double mat[ROWS][COLS];
    FILE *fstream = fopen("data.txt","r");
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



    //sorting and generating the column by column
    //for(int k = 0; k < COLS; k++ ){
    static ELEMENT justAColumn[ROWS];
    for(int x = 0 ; x < ROWS; x++){

        ELEMENT el;
        el.row = x;
        el.col = 0;
        el.datum =  mat[x][0];


        justAColumn[x] = el;

    }


    qsort(justAColumn, ROWS, sizeof(ELEMENT), lowToHigh);
    



    //generating blocks using an array of blocks with the hashed signature index
    int n = 6;
    ELEMENT elarray[n];
    for(int k = 0; k < n; k++){
        elarray[k].row = k;
        elarray[k].col = 1;
        elarray[k].datum = 1;
    }


    vector<ELEMENT> v;
    for(int k = 0; k < n; k++){
        v.push_back(elarray[k]);
    }



    genBlocks(v,v.size());

     for ( auto it = collisionTable.begin(); it != collisionTable.end(); ++it )
      { 
        cout  <<"Key: "<< (*it).first ;


        for(int k =0; k < (*it).second.size(); k++){

          for(int l = 0 ; l < 4 ; l ++)
            cout<< " Value (row): "<< (*it).second[k].rowIds[l] << " ";

        }

        cout << endl;

      }

     
  

     


//}
}


