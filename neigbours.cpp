

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

// #include <fopenmp.h>
double element[7]={0.000452,0.000453,0.000454,0.000455,0.000456,0.000458,0.000459};

vector<vector<double>> getNeighbours(double *s){
    
    vector<vector<double>> listOfNeigh;
    vector<double>::iterator it;

    int j=1;
    int pivot=0;

    v1.push_back(element[0]);
    for (int start = 0; start<(sizeof(element)/sizeof(element[0])); start++)
    {
        vector<double> v1;
        v1.push_back(element[start]);
        //element j= the element being checked to see if it is within dia distance.


        while(j<sizeof(element)/sizeof(element[0])&&(1000000.0*element[j])-(1000000.0*element[start]) <= (1000000.0*dia)){


                v1.push_back(element[j]);
                pivot++;//increase the pivot index, note the pivot index starts from 0(same as arrays)
            j++;

            }

        //send the vector and pivot to makeBlocks




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

    getNeighbour(element);
}

