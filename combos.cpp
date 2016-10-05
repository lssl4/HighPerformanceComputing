#include <iostream>
#include <vector>

using namespace std;
#include "type.h"




void generate_combos(int n, int r) {
    vector<int> eachCom;
    vector<vector<int>> listOfCombos;

    //generates the eachCom with numbers up to r
    for (int i = 0; i < r; i++){

        eachCom.push_back(i);
       
        //eachCom[i] = i;
    }

    if(r-1>=0){
    while( eachCom[r - 1] < n) {

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
}

int main(){

    generate_combos(56,4);

    return 0;

}