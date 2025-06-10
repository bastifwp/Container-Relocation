#include<bits/stdc++.h>

#include "global.h"

using namespace std;

void swap(individuo &ind){// De toda la vida

    int moves_size = ind.moves.size();
    int a = getRandomInt(0,moves_size-1);
    int b = getRandomInt(0,moves_size-1);

    int aux = ind.moves[a];
    ind.moves[a] = ind.moves[b];
    ind.moves[b] = aux;

}
 
void inversion(individuo &ind){// Entre dos puntos random

    int moves_size = ind.moves.size();
    int a = getRandomInt(0,moves_size-1);
    int b = getRandomInt(0,moves_size-1);

    //"a" debe ser menor o igual a b
    if(a>b){int aux = a; a = b; b = aux;}

    //Invertimos sección entre a y b incluidos
    vector<int> section;
    for (int i = a; i < b+1; i++)
    {
        section.push_back(ind.moves[i]);
    }
    for (int i = a; i < b+1; i++)
    {
        ind.moves[i] = section[b-i];
    }
      
}

void intFlip(individuo &ind){// De toda la vida

    int moves_size = ind.moves.size();
    int i = getRandomInt(0,moves_size-1);

    ind.moves[i] = getRandomInt(1,params.n_heu);

}

//Mutar poblacion, con una probabilidad de pmut por individuo
void mutatePop(vector<individuo> &pop){

    for (int i = params.elite; i < params.popsize; i++)
    {
        double p = getRandomProb();
        if(p <= params.pmut){
            int mut = getRandomInt(1,3);
            if(mut == 1){
                swap(pop[i]);
            }
            else if(mut == 2){
                inversion(pop[i]);
            }
            else{
                intFlip(pop[i]);
            }
        }
    }
    
}