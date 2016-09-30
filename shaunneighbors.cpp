

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cmath>
#define dia 0.000002

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
    vector<double>::iterator it;
<<<<<<< HEAD
    // it = v1.begin();

    //int start = 0;
    
    int pivot=-1;
   
    for (int start = 0; start < (sizeof(element)/sizeof(element[0])); start++)

    {
        vector<double> v1;
        v1.push_back(element[start]);
        //element j= the element being checked to see if it is within dia distance.
<<<<<<< HEAD
        // v1.push_back(element[i]);
        for(int j = 1;j<(sizeof(element)/sizeof(element[0])); j++ ){
            //for(start;start<(sizeof(element)/sizeof(element[0]));start++){
          
            cout<<(1000000.0*element[j])-(1000000.0*element[start])<<endl;
            if( ( (1000000.0*element[j])-(1000000.0*element[start]) )< (1000000.0*dia)){

                v1.push_back(element[j]);
                //pivot=j;
                
            }

            //if element j is not within the dia distance
            else{
                
               listOfNeigh.push_back(v1);

              
                

                break;
            }
        }



        //x++;
        //start=x;
        //j=x;
        //cout<<  <<endl;
    }

    

     return listOfNeigh;


        //for debugging
        for( it = v1.begin();it!=v1.end();it++)
        {
            cout<< *it <<endl;
        }
        cout<< pivot <<endl;


        v1.erase(v1.begin());//remove front element
        pivot = 0;//reset pivot index point
        }

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

