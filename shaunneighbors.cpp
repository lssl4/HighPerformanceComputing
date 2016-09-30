

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <cmath>
#define dia 0.000001

using namespace std;
#include <unordered_set>
#include <iostream>
#include <vector>
//#include <algorithm>
#include "type.h"

double element[10]={0.0004525,0.000453,0.0004535,0.000454,0.0004545,0.000455,0.0004555,0.000456,0.0004565,0.000457};
int pivot;




vector<vector<double>> getNeighbours(double *s){
    
    vector<vector<double>> listOfNeigh;
    

    //for each element in the array, find its neighborhood, including the last element even though there's no more trailing elements after it. 
    for (int start = 0; start < (sizeof(element)/sizeof(element[0])); start++)

    {
        vector<double> v1;
        v1.push_back(element[start]);
        //element j= the element being checked to see if it is within dia distance.


        //for each trailing element after start, check if it's within neighborhood
        for(int j = 1;j<(sizeof(element)/sizeof(element[0])) -start; j++ ){
            //for(start;start<(sizeof(element)/sizeof(element[0]));start++){
          

            printf("%.12f - %.12f = %.12f | %i\n",(1000000.0*element[j+start]), (1000000.0*element[start]), (1000000.0*element[j+start])-(1000000.0*element[start])  , (1000000.0*element[j+start]) - (1000000.0*element[start]) < (1000000.0*dia) );

            if( ( (1000000.0*element[j+start])-(1000000.0*element[start]) )< (1000000.0*dia) ){

                v1.push_back(element[j+start]);
                //pivot=j;
                
            }

            //if element j is not within the dia distance
            else{
            

                break;
            }
        }

        //after finding the longest neighborhood, push it in the list 
        listOfNeigh.push_back(v1);

     
    }

    

     return listOfNeigh;
 
 }

    




int main(){

    //vector<double> v1;
    vector<vector<double>> output = getNeighbours(element);

        /*for( vector<vector<double>>::iterator it = output.begin();it!=output.end();it++)
                {
                    for(vector<double>::iterator it2 = (*it).begin(); it2 != (*it).end(); it2++)
                            {cout<< *it2 << " ";}
                        cout << endl;
                }*/

    for(int i = 0; i < output.size(); i++){
        vector<double> neigh = output[i];
        for(int j = 0; j < neigh.size(); j ++){

            cout<< neigh[j] << " ";
        }

        cout<< endl;
    }
}

