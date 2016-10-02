/*
Each row directly correspond with a key in the key array. 
That is row 1 would correspond to key 1 in the key array
*/


//c directives
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>



using namespace std;

//c++ directives
#include <unordered_map>
#include <vector>
#include <iostream>
#include <algorithm>
//#include <unordered_set>



#define ROWS 4400
#define COLS 500
#define DIA 0.000001
//#define BLOCKLISTSIZE 400000000000

#include "type.h"
#include "finalNeighbors.cpp" 


unordered_map<long long int, vector<BLOCK>> collisionTable;
long long keys[ROWS];
static double mat[ROWS][COLS];



/*
Generate combinations of indices.
*/
vector<vector<int>> genCombos(int n, int r) {
    vector<int> eachCom;
    vector<vector<int>> listOfCombos;

   // cout << "n: " << n << " r: " << r << endl;

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
After the 4 element combos have been generated and modified, generate the blocks from the combos and push to collisiontable 
*/
void pushToCollisionTable(vector<vector<int>> c, vector<ELEMENT> vect){
    int numOfElements =4;

   // cout << "\nc size: "<< c.size() << " vect: "<< vect.size() << endl;
     //for each combos generated in combos1, ultimately get the combo elements' block and insert them to the collision table
        for(int k = 0; k < c.size(); k++){
            


            //for each element index in a combo generated, access v to get the appropriate element and put it in element list.
            //and to get the key value from keys array from the row
            long long int keysSum =0;
            BLOCK newBlock;

            for(int j = 0 ;j < numOfElements; j++){
               // cout << "c[k][j]: " << c[k][j]  << endl;

                ELEMENT el = vect[c[k][j]];

                newBlock.rowIds.push_back(el.row);
                newBlock.col = el.col;

               
                // cout << "el.row: "<<el.row << endl;
                keysSum += keys[el.row];

               
                 

            }
           

            //Assign keysSum to signature of block
            newBlock.signature = keysSum;

            //add to collision table, if it doesn't exist, it makes a new entry
            collisionTable[keysSum].push_back(newBlock);

        }
}



/*
Generate blocks given a vector of ELEMENTS and pivot. v.size() -1 because it also contains the pivot at the end
*/
int genBlocks(vector<ELEMENT> v, int pivot){

    //2 combos vectors for block generations and to prevent redundant blocks
    vector<vector<int>> combos1;
    vector<vector<int>> combos2;
    int r =4;
    int blocksGen = 0;


    //if pivot is the same value as the v's size, then go straight ahead and generate the combos for whole ELEMENT vector
    if(pivot==v.size()-1){

        //cout << "n ((int)v.size()-1): " << (int)v.size()-1 << "r: " << r<<endl;
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

         //cout <<"pivot: "<< pivot<<" for combos1: r-k-1: "<< r-k-1 << endl;

        cout<< "n1: "<< n1 << "r1: "<< r1 << endl;

          //iteratively decreasing r for the first combos
         combos1 = genCombos(pivot, r-k-1);


        cout <<"aFter combos1. combos1 size: " << combos1.size()<<endl;

       // cout <<"(v.size()-pivot): "<< (int)(v.size()-pivot) <<" for combos2: k+1: "<< k+1 << endl;


        cout<< "n2: "<< n2 << "r2: "<< r2 << endl;

         //iteratively increasing r for the second combos
         combos2 = genCombos((int)((v.size()-1)-pivot), k+1);

        cout <<"aFter combos2. combos2 size: " << combos2.size()<<endl;


        //adding all of the combos by pivot in combos2 to match the latter half of array indices
         for(int x = 0; x < combos2.size() ; x++){
            vector<int>eachCom = combos2[x];
            
            //adding each element in eachCom by pivot
            for(int y = 0 ; y < eachCom.size(); y++){

                eachCom[y] = eachCom[y] + pivot;
               
            }
            
            combos2[x] = eachCom;

         }


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
        pushToCollisionTable(combinedCombos, v);        

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

int filesInput(){
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


}


int main(){
    //get files inputted into program
    filesInput();

    //sorting and generating the column by column
    //for(int k = 0; k < COLS; k++ ){

    vector<ELEMENT> justAColumn(ROWS);
    for(int x = 0 ; x < ROWS; x++){

        ELEMENT el;
        el.row = x;
        el.col = 0;
        el.datum =  mat[x][0];


        justAColumn[x] = el;



    }





    //call finalneighbors (getNeighbors) where the column will be sorted in the function. Returns a list of neighborhoods
    vector<vector<ELEMENT>> output = getNeighbours(justAColumn);

     cout << "Output size: "<<output.size() << endl;
    /*for (int k = 0; k < output.size(); ++k)
    {   
        vector<ELEMENT> n = output[k];

        for(int l = 0 ; l < n.size(); l++ )
            printf("Size of vector: %i %i %f\n", n.size(),k, n[l].datum );
    }*/
       

   for(int k = 0; k < output.size(); k ++){

    //  cout << "Size of Output: "<< endl << output.size()<<"(output[k][output[k].size()-2]).datum: " << (output[k][output[k].size()-2]).datum << endl;
    genBlocks(output[k], (output[k][output[k].size()-1]).datum );
   }


    //printing out collision table
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
