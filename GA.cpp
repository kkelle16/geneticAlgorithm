//
//  GA.cpp
//  project4
//
//  Created by Kelsey Kelley on 3/31/19.
//  Copyright © 2019 Kelsey Kelley. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <map>
#include <vector>
#include <cmath>
#include <utility>


using namespace std;

void createPopulation(map<int, vector<int> > &p, int l, int seed){
    
    map<int, vector<int> >::iterator it;
    int random;
    vector<int> v;
    
    v.resize(l);
    srand((unsigned)time(NULL));
    for(it = p.begin(); it != p.end(); it++){
        v = it->second;
        for(int i = 0; i < l; i++){
            //srand((unsigned)time(NULL));
            random = rand()%500;
            if(random%2 == 0){
                it->second[i] = 0;
            }else{
                it->second[i] = 1;
            }
        }
    }
}

double calculateFitness(vector<int> v, double &total){
    
    double sum = 0;
    double fitness;
    double exponent = (unsigned)v.size() - 1;
    
    for(int i = 0; i < v.size(); i++){
        if(v[i] == 1){
            sum = sum + pow(2,exponent-i);
        }
    }
    fitness = pow((sum/(pow(2, v.size()))), 10);
    total = total + fitness;
    return fitness;
}

pair<int, int> getParents(vector<double> total, int N, int seed){
    double r1, r2;
    double p1, p2;
    pair<int, int> parents;
    srand((unsigned)time(NULL));
    r1 = (rand()%1000)/1000;
    r2 = (rand()%1000)/1000;
    for(int i = 0; i < N; i++){
        if((total[i] > r1) && (total[i+1] < r1)){
            p1 = i+1;
        }
        if((total[i] > r2) && (total[i+1] < r2)){
            p2 = i+1;
        }
    }
    if(p1 != p2){
        parents = make_pair(p1, p2);
        return parents;
    }else{
        parents = getParents(total, N, seed);
    }
    return parents;
}

void crossover(map<int, vector<int> > p, int m, int d, map<int, vector<int> > &ng, int ind, int N, double mutationProb, int seed, int length){
    map<int, vector<int> >::iterator it;
    map<int, vector<int> >::iterator pit;
    map<int, vector<int> >::iterator nit;
    map<int, vector<int> >::iterator git;
    
    srand((unsigned)time(NULL));
    int random = rand()%length;
    
    it = p.find(m);
    pit = p.find(d);
    nit = ng.find(ind);
    git = ng.find(ind+N/2);
    
    for(int i = 0; i <= random; i++){
        nit->second[i] = it->second[i];
        git->second[i] = pit->second[i];
    }
    for(int j = random+1; j < length; j++){
        nit->second[j] = pit->second[j];
        git->second[j] = it->second[j];
    }
    
    for(int k = 0; k < length; k++){
        srand((unsigned)time(NULL));
        double prob = (rand()%1000)/1000;
        if(prob <= mutationProb){
            if(nit->second[k] == 0){
                nit->second[k] = 1;
            }else{
                nit->second[k] = 0;
            }
        }
    }
    for(int k = 0; k < length; k++){
        srand((unsigned)time(NULL));
        double prob = (rand()%100)/100;
        if(prob <= mutationProb){
            if(git->second[k] == 0){
                git->second[k] = 1;
            }else{
                git->second[k] = 0;
            }
        }
    }
}

void notCrossover(map<int, vector<int> > p, int m, int d, map<int, vector<int> > &ng, int ind, int N){
    map<int, vector<int> >::iterator it;
    map<int, vector<int> >::iterator pit;
    it = p.find(m);
    pit = ng.find(ind);
    pit->second = it->second;
    it = p.find(d);
    pit = ng.find(ind+N/2);
    pit->second = it->second;
}

int main(int argc, char *argv[]){
    
    map<int, vector<int> > population;
    map<int, vector<int> > nextGeneration;
    map<int, vector<int> >::iterator pit;
    map<int, vector<int> >::iterator nit;
    
    //number of genes
    int l = 20;
    
    //population size
    int N = 30;
    
    //number of generations
    int G = 10;
    
    //mutation probability
    double pm = 0.033;
    
    //crossover probability
    double pc = 0.6;
    
    //read in the values as input
    int seed = 300;
    //cin >> l >> N >> G >> pm >> pc >> seed;
    
    vector<int> v;
    vector<double> fitness;
    vector<double> normFitness;
    vector<double> runningTotal;
    
    fitness.resize(N);
    normFitness.resize(N);
    runningTotal.resize(N);
    
    pair<double, double> parents;
    
    double total = 0;
    double normTotal = 0;
    double random;
    
    vector<double> averageFitness;
    vector<double> bestFitness;
    vector<int> correctBits;
    int bestIndex;
    
    averageFitness.resize(G);
    bestFitness.resize(G);
    correctBits.resize(G);
    
    //creating the population
    for(int i = 0; i < N; i++){
        v.resize(l);
        population.insert(make_pair(i, v));
    }
    createPopulation(population, l, seed);
    
    for(int g = 0; g < G; g++){
        
        fitness.resize(N);
        normFitness.resize(N);
        runningTotal.resize(N);
        
        for(int i = 0; i < N; i++){
            v.resize(l);
            nextGeneration.insert(make_pair(i,v));
        }
        
        for(int i = 0; i < N; i++){
            pit = population.find(i);
            fitness[i] = calculateFitness(pit->second, total);
        }
        
        for(int j = 0; j < N; j++){
            normFitness[j] = fitness[j]/total;
            normTotal = normTotal + normFitness[j];
            runningTotal[j] = normTotal;
        }
        
        for(int n = 0; n < N/2; n++){
            
            parents = getParents(runningTotal, N, seed);
            srand((unsigned)time(NULL));
            random = (rand()%100)/100;
            
            if(random <= pc){
                crossover(population, parents.first, parents.second, nextGeneration, n, N, pm, seed, l);
            }else{
                notCrossover(population, parents.first, parents.second, nextGeneration, n, N);
            }
            
            for(int i = 0; i < N; i++){
                pit = population.find(i);
                nit = nextGeneration.find(i);
                pit->second.swap(nit->second);
            }
            
        }
        
        averageFitness[g] = total/(double)N;
        
        bestFitness[g] = fitness[0];
        for(int k = 0; k < N; k++){
            if(fitness[k] >= bestFitness[g]){
                bestFitness[g] = fitness[k];
                bestIndex = k;
            }
        }
        correctBits[g] = 0;
        pit = population.find(bestIndex);
        for(int m = 0; m < l; m++){
            if(pit->second[m] == 1){
                correctBits[g] = correctBits[g] + 1;
            }
        }
        
        nextGeneration.clear();
        fitness.clear();
        normFitness.clear();
        runningTotal.clear();
        total = 0;
        normTotal = 0;
        
    }
    cout << "average fitness   best fitness   correct bits" << endl;
    for(int r = 0; r < G; r++){
        cout << averageFitness[r] << "    " << bestFitness[r] << "    " << correctBits[r] << endl;
    }
    return 0;
}
