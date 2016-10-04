



bool lowHigh (ELEMENT i, ELEMENT j) { 
    return (i.datum<j.datum); 
}

    
vector<vector<ELEMENT>> getNeighbours(vector<ELEMENT> s, double dia){

   


    vector<vector<ELEMENT>> listOfNeigh;

    //index of the last seen element in array s
    int prevLastIndex = 1;

    //sort s
    sort(s.begin(), s.end(), lowHigh);

    

    //for element in s, find its neighborhood. skip finding neigbourhoods when all elements have been seen

    for (int start = 0; start < s.size() && prevLastIndex < s.size(); start++)

    {
        vector<ELEMENT> v1;
       
        int pivot = 1;

        //when start equals to prevLastIndex, move prevlastIndex by one
        if(prevLastIndex == start){
            prevLastIndex++;
        }

    


        //make v1 be consist of the subset of elements that have been seen from the previous neighborhood 
        int k;
        
        #pragma omg parallel for
        for(k = start ; k < prevLastIndex; k++){
       
            v1.push_back(s[k]);

        }
      


        //for each trailing s after start, check if it's within neighborhood. vectorsize -2 
        //because of pivot number at end and shifting everything to the right by previous list size
        //must set to <= because 
        for(int j = prevLastIndex; j <= s.size() ; j++){
          
         


            if( j < s.size() && ( (int)( 1000000*(s[j].datum))- (int)( 1000000*(s[start].datum)) ) < (int)(1000000*dia) ){


                v1.push_back(s[j]);
              

                
            }

            //if j is not within the dia distance, break and add the vector so far to the list
            else{

                //if no new elements are added and j is still at prev index then break 
                if(j == prevLastIndex){
                    break;
                }


                 //if there's no more elements to be added, append pivot to the vector
                if(listOfNeigh.size() >0){

                     vector<ELEMENT> prevVector = listOfNeigh.back();

                     //gets the row value of the last vector in listOfNeigh. -2 because the pivot is at the end of the vector
                    int prevVectRow = prevVector[prevVector.size()-2].row;
                    int currVectRow = v1.front().row;

                    if(prevVectRow - currVectRow >=0 ){
                        pivot = prevVectRow - currVectRow +1;
                    }else{
                        //if rows don't overlap then just put the vector size as the pivot
                         pivot = v1.size();
                    }

                        
                //if no vector in list then just do vector size    
                }else{
                    pivot = v1.size();
                }

                if(v1.size() >=4){
                    //push back the pivot number in the neighborhood vector as an element type. pivot appears at the end of vector
                    ELEMENT pivotEl;
                    pivotEl.datum = pivot;
                    v1.push_back(pivotEl);

                    //after finding the longest neighborhood, push it in the list 
                    listOfNeigh.push_back(v1);

                    
                  }

                       //update prevLastIndex with jth element which indicates which elements have been seen
                prevLastIndex = j;
                
                
                break;
            }


        }
                 
    }

    

     return listOfNeigh;
 
 }

    






