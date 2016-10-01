

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <cmath>
#include <algorithm>
#define dia 0.000001

using namespace std;
#include <unordered_set>
#include <iostream>
#include <vector>
//#include <algorithm>
#include "type.h"

vector<double> sample = {0.0004520,0.0004525, 0.0004531, 0.0004532, 0.0004533, 0.0004534, 0.0004535, 0.0004535,0.000454,0.000454,0.000458,0.000459, 0.00046, 0.0004601, 0.0004602, 0.0004603, 0.0004604};




bool lowHigh (ELEMENT i, ELEMENT j) { 
    return (i.datum<j.datum); 
}

    
vector<vector<ELEMENT>> getNeighbours(vector<ELEMENT> s){
    
    vector<vector<ELEMENT>> listOfNeigh;
    int prevLastIndex =-1;

    //sort s
    sort(s.begin(), s.end(), lowHigh);



    for (int i = 0; i < s.size(); ++i)
    {

        /* code */
       printf("%.7f ", s[i]);
    }
    cout<< endl << endl;

    //for each s in the array, find its neighborhood, including the last s even though there's no more trailing elements after it. 
    for (int start = 0; start < s.size(); start++)

    {
        vector<ELEMENT> v1;
        vector<ELEMENT> v2;
        int pivot = 1;

        v1.push_back(s[start]);


        //for each trailing s after start, check if it's within neighborhood. vectorsize -2 
        //because of pivot number at end and shifting everything to the right by previous list size
        for(int j = start +1 ;j < s.size() ; j++){
          
            printf("j: %i start: %i\n", j, start);
            printf("%.12f - %.12f = %.12f | %i\n\n",(1000000.0*s[j].datum), (1000000.0*s[start].datum), (1000000.0*s[j].datum)-(1000000.0*s[start].datum)  , (1000000.0*s[j].datum)  - (1000000.0*s[start].datum) < (1000000.0*dia) );

            if( ( (1000000.0*s[j].datum)-(1000000.0*s[start].datum) )< (1000000.0*dia) ){


                v1.push_back(s[j]);
                //pivot=j;

                cout << "Pushed in v1: " << s[j].datum <<endl;
                
            }

            //if s j is not within the dia distance
            else{

                /*if(v1.size() < 4){
                    break;
                }*/


                
                break;
            }

            



        }

        
                  //if there's no more elements to be added, get pivot if any
                if(listOfNeigh.size() >0){

                    vector<ELEMENT> prevVector = listOfNeigh.back();

                 

                    int prevVectRow = prevVector[prevVector.size()-2].row;
                    int currVectRow = v1.front().row;


                    if(prevVectRow - currVectRow >=0 ){
                        pivot = prevVectRow - currVectRow +1;
                        printf("pivot: %i\n", pivot);
                    }

                        
                    
                }else{
                    pivot = v1.size();
                }




                    //push back the pivot number in the neighborhood vector as an element. pivot appears at the end of vector
                    ELEMENT pivotEl;
                    pivotEl.datum = pivot;

                    v1.push_back(pivotEl);

                    //after finding the longest neighborhood, push it in the list 
                    listOfNeigh.push_back(v1);



        

     
    }

    

     return listOfNeigh;
 
 }

    




int main(){
    
    vector<ELEMENT> element;
    for(int x = 0 ; x < sample.size(); x++){

        ELEMENT el;
        el.row = x;
        el.col = 0;
        el.datum = sample[x];


        element.push_back(el);

    }



    //vector<double> v1;
    vector<vector<ELEMENT>> output = getNeighbours(element);

        /*for( vector<vector<double>>::iterator it = output.begin();it!=output.end();it++)
                {
                    for(vector<double>::iterator it2 = (*it).begin(); it2 != (*it).end(); it2++)
                            {cout<< *it2 << " ";}
                        cout << endl;
                }*/

    for(int i = 0; i < output.size(); i++){
        vector<ELEMENT> neigh = output[i];
        for(int j = 0; j < neigh.size(); j ++){

            cout<< neigh[j].datum << " ";
        }

        cout<< endl;
    }
}

