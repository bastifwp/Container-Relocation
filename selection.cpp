#include<bits/stdc++.h>

#include "global.h"

using namespace std;

//Función de comparación para ordenar en orden ascendente por fobj[0]
bool compararPorFobjAsc(const individuo &a, individuo &b) {
    return a.fobj[0] < b.fobj[0];
}

//Pa un objetivo q me da lata
individuo tournament(individuo &ind1, individuo &ind2){

    int fo1; //Ganador para fo1 
    if(ind1.fobj[0] < ind2.fobj[0]) return ind1;
    else if(ind2.fobj[0] < ind1.fobj[0]) return ind2;
    else{
        double p = getRandomProb();
        if(p <= 0.5) return ind1;
        else return ind2;
    }

}

//Funcion para generar nueva poblacion a partir de una poblacion padre
void generateNewPop(vector<individuo> &old_pop){

    vector<int> a1(params.popsize), a2(params.popsize);
    int temp;
    int rand;
    individuo parent1, parent2;
    vector<individuo> new_pop(params.popsize), children;

    double p = getRandomProb();
    sort(old_pop.begin(), old_pop.end(), compararPorFobjAsc);

    if(p<=params.pcross){
    
        //Obtener elite de poblacion padre y pasarla directamente a la nueva poblacion
        for (int i = 0; i < params.elite; i++)
        {
            new_pop[i] = old_pop[i];
        }

        //Preparar torneos
        for (int i=0; i<params.popsize; i++)
        {
            a1[i] = a2[i] = i;
        }
        for (int i=0; i<params.popsize; i++)
        {
            rand = getRandomInt(i, params.popsize-1);
            temp = a1[rand];
            a1[rand] = a1[i];
            a1[i] = temp;
            rand = getRandomInt(i, params.popsize-1);
            temp = a2[rand];
            a2[rand] = a2[i];
            a2[i] = temp;
        }

        //Realizar torneos y generar hijos en base a ganadores
        for (int i=params.elite; i<params.popsize; i+=2)
        {
            parent1 = tournament (old_pop[a1[i]], old_pop[a1[i+1]]);
            parent2 = tournament (old_pop[a2[i]], old_pop[a2[i+1]]);
            //parent2 = tournament (old_pop[a1[i+2]], old_pop[a1[i+3]]);
            children = one_point_crossover(parent1, parent2);
            new_pop[i] = children[0]; new_pop[i+1] = children[1];

            //parent1 = tournament (old_pop[a2[i]], old_pop[a2[i+1]]);
            //parent2 = tournament (old_pop[a2[i+2]], old_pop[a2[i+3]]);
            //children = one_point_crossover(parent1, parent2);
            //new_pop[i+2] = children[0]; new_pop[i+3] = children[1];
        }
        old_pop = new_pop;

    }

}


//Si ninguno domina al otro, se retorna uno al azar,
//pero podriamos implementar el calculo de crowding distance
individuo tournamentMultiFO(individuo &ind1, individuo &ind2){

    int fo1; //Ganador para fo1 
    if(ind1.fobj[0] < ind2.fobj[0]) fo1 = 1;
    else if(ind2.fobj[0] < ind1.fobj[0]) fo1 = 2;
    else fo1 = 0;

    int fo2; //Ganador para fo2
    if(ind1.fobj[1] < ind2.fobj[1]) fo2 = 1;
    else if(ind2.fobj[0] < ind1.fobj[0]) fo2 = 2;
    else fo2 = 0;

    if(fo1 == fo2){// Si el mismo individuo es mejor en ambas fos
        if(fo1 == 1) return ind1;
        else if(fo1 == 2) return ind2;
        else{
            double p = getRandomProb();
            if(p <= 0.5) return ind1;
            else return ind2;
        }
    }
    else if(fo1 == 0 || fo2 == 0){ //Si empatan en una fo y en otra alguno gana
        if(max(fo1,fo2) == 1) return ind1;
        else return ind2;
    }
    else{ //Si ambos ganan en fos distintas
        double p = getRandomProb();
        if(p <= 0.5) return ind1;
        else return ind2;
    }

}




