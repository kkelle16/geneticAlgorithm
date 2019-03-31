//
//  GA.cpp
//  
//
//  Created by Kelsey Kelley on 3/30/19.
//

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <map>

using namespace std;

void createPopulation(map<int, vector<int> > &p, int l){
    
    map<int, vector<int> >::iterator it;
    int random;
    vector<int> v;
    
    v.resize(l);
    
    for(it = p.begin(); it != p.end(); it++){
        srand((unsigned)tim(NULL));
        v = it->second;
        for(int i = 0; i < l; i++){
            random = rand();
            if(random%2 == 0){
                it->second[i] == 0;
            }else{
                it->second[i] == 1;
            }
        }
    }
}

int main(int argc, char *argv[]){
    
    map<int, vector<int> > population;
    
    //number of genes
    int l = 20;
    
    //population size
    int N = 30;
    
    //number of generation
    int G = 10;
    
    //mutation probability
    double pm = 0.033;
    
    //crossover probability
    double pc = 0.6;
    
    //read in the values as input
    //cin >> l >> N >> G >> pm >> pc >> seed;
    
    vector<int> v;
    
    for(int i = 0; i < N, i++){
        v.resize(l);
        population.insert(make_pair(i+1, v));
    }
    createPopulation(population, l);
    
    
    
    return 0;
}
