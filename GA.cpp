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
#include <vector>
#include <cmath>

using namespace std;

void createPopulation(map<int, vector<int> > &p, int l, int seed){
    
    map<int, vector<int> >::iterator it;
    int random;
    vector<int> v;
    
    v.resize(l);
    
    for(it = p.begin(); it != p.end(); it++){
        //srand((unsigned)time(NULL));
        v = it->second;
        for(int i = 0; i < l; i++){
            random = rand()%30;
            if(random%2 == 0){
                it->second[i] = 0;
            }else{
                it->second[i] = 1;
            }
        }
    }
}

double calculateFitness(vector<int> v){
    
    double sum = 0;
    double fitness;
    double exponent = (unsigned)v.size() - 1;
    
    for(int i = 0; i < v.size(); i++){
        if(v[i] == 1){
            sum = sum + pow(2,exponent-i);
        }
    }
    fitness = pow((sum/(pow(2, v.size()))), 10);
    return fitness;
}

int main(int argc, char *argv[]){
    
    map<int, vector<int> > population;
    map<int, vector<int> >::iterator pit;
    
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
    int seed = 5;
    //cin >> l >> N >> G >> pm >> pc >> seed;
    
    vector<int> v;
    double fitness[N];
    double normFitness[N];
    double runningTotal[N];
    double total = 0;
    int f;
    
    //creating the population
    for(int i = 0; i < N; i++){
        v.resize(l);
        population.insert(make_pair(i, v));
    }
    createPopulation(population, l, seed);
    
    
    /*for(pit = population.begin(); pit != population.end(); pit++){
     for(int j = 0; j < l; j++){
     cout << pit->second[j];
     }
     cout << endl;
     }*/
    
    for(int g = 0; g < G; g++){
        
        for(int j = 0; j < N; j++){
            pit = population.find(j);
            fitness[j] = calculateFitness(pit->second);
        }
        
    }
    
    
    
    return 0;
}
