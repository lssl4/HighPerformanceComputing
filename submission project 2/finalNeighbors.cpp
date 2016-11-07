
/*
 * Comparison function for sorting to compare the ELEMENT's values
 * @param i 1st ELEMENT object to compare its value
 * @param j 2nd ELEMENT object to compare its value
 * @returns true if j is greater than i resulting in an ascending order
*/
bool lowHigh (ELEMENT i, ELEMENT j) {
    return (i.datum<j.datum);
}


/*
 * Generates all the neighborhoods of a column. 
 * @param s the vector which consist of a column
 * @param dia the distance to create a neighborhood with 
 * @return the list of neighborhoods from the provided column vector s and dia distance 
*/
vector<vector<ELEMENT>> getNeighbours(vector<ELEMENT> s, double dia){

    vector<vector<ELEMENT>> listOfNeigh;

    //index of the last seen element in array s
    int prevLastIndex = 1;

    //last element index in s
    int lastIndex = 0;

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
        for(int k = start ; k < prevLastIndex; k++){

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


                //if the neighborhood is greater than 4, vind the pivot
                if(v1.size() >=4){

                    //append pivot from last list information
                    if(listOfNeigh.size() >0){

                        vector<ELEMENT> prevVector = listOfNeigh.back();

                        //gets the row value of the last vector in listOfNeigh. -2 because the pivot is at the end of the vector but i want the last element


                        if(lastIndex - start >=0 ){
                            pivot = lastIndex - start +1;
                        }else{
                            //if rows don't overlap then just put the vector size as the pivot
                            pivot = v1.size();
                        }

                        //if no vector in list then just do vector size
                    }else{

                        pivot = v1.size();
                    }

                    //since the list is successful, update the lastindex
                    lastIndex = j-1;

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




