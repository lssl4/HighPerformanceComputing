

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cmath>
#define dia 0.000001

using namespace std;
#include <unordered_set>
#include <iostream>
#include <vector>
#include <algorithm>
#include "type.h"

double element[7]={0.000452,0.000453,0.000454,0.000455,0.000456,0.000458,0.000459};
int pivot;



void getNeighbour(double *s){
    vector<double> v1;
    vector<double> v2;
    vector<double>::iterator it;
    // it = v1.begin();

    //int start = 0;
    int j=1;
    int pivot=-1;
    //int x = 0;
    //while(x<(sizeof(element)/sizeof(element[0]))-1)// this while loop controls the location of x(ie the start values)
    //j=x;
    for (int start = 0; start < (sizeof(element)/sizeof(element[0]))-1; start++)
    {
        //element j= the element being checked to see if it is within dia distance.
        // v1.push_back(element[i]);
        while(j<(sizeof(element)/sizeof(element[0]))){
            //for(start;start<(sizeof(element)/sizeof(element[0]));start++){
            if((1000000.0*element[j])-(1000000.0*element[start]) <= (1000000.0*dia)){

                v1.push_back(element[j]);
                pivot=j;
                j++;
            }
            else{
                j=start;

                for( it = v1.begin();it!=v1.end();it++)
                {
                    cout<< *it <<endl;
                }
                //v1.erase(v1.begin());
                //cout<< pivot <<endl;
                //send vector out, 
                //cout<< j <<endl;

                break;
            };
        }

        //x++;
        //start=x;
        //j=x;
        //cout<<  <<endl;
    }
    //for(int j=start;j<sizeof(element)/sizeof(element[0]);j++){
    /*if( (1000000.0*element[j])-(1000000.0*element[start]) <= (1000000.0*dia)){
        v1.push_back(element[j]);//add element end of vector, that is within dia distance
        pivot=j;//the last element of the vector
    }
    //genBlocks(vector<ELEMENT> v1, int pivot)
    //find pivot. pivot of first neighbourhood will be last element of first neighbour
    //
    //

}

}}
//}

cout<<"Stored values are:"<<endl;
for(iterator = set.begin();iterator!=set.end();iterator++)sd
{
cout<< *iterator <<endl;
}*/
    // cout<< pivot <<endl;/*
    /*for(it = v1.begin();it!=v1.end();it++)
   {
     cout<< *it <<endl;
   }*/

}



int main(){
    //vector<double> v1;
    getNeighbour(element);
}

/*
#include <iostream>
#include <unordered_set>
 
using namespace std; 
int main()
{
    unordered_set<int> set;
        
    set.insert(5);    
    //Insert same items here to see if more than one of them
    //have been inserted
    set.insert(8);
    set.insert(8);    
    set.insert(45);
    set.insert(50);    
    
    //iterate the set here
    unordered_set<int>::iterator iterator;    
    cout<<"Stored values are:"<<endl;
    for(iterator = set.begin();iterator!=set.end();iterator++)
    {
      cout<< *iterator <<endl;
    }
}*/