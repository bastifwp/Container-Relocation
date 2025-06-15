#include<bits/stdc++.h>

#include "global.h"

using namespace std;

/* -------------- Estas funciones retornan directamente el mejor valor ----------------*/

//Función miope de espacio que cambia al stack con más espacio
int myopic_space(vector<vector<int>> &yard, int origin_stack){
    //Recorremos todo el yard y vamos calculando
    int max_space = 0;
    int choosed_stack = 0;

    for(int i = 0; i < n_bays*n_rows; i++){

        if(i == origin_stack){
            continue;
        }

        //Verificamos si es mejor que lo que ya hemos encontrado
        int value = max_h - yard[i].size();
        if(value > max_space){
            max_space = value;
            choosed_stack = i;
        }
    }

    //Retornamos el mejor stack para moverse
    return choosed_stack;
}


int count_blocked(vector<int> stack, int c2relocate){

    int blocked_containers = 0;
    for(int i = 0; i < stack.size(); i++){
        if(stack[i]< c2relocate) blocked_containers++;
    }
    return blocked_containers;
}

int myopic_blocked(vector<vector<int>> &yard,  int origin_stack)
{   
    //Recorremos la bahía y retornamos el con menor bloqueos
    int min_blocks = n_initial_containers;
    int choosed_stack = 0;

    for (int i = 0; i < n_bays*n_rows; i++)
    {
    
        int feasible = max_h - yard[i].size();
    
        if(i != origin_stack && feasible != 0){

            int c2relocate = yard[origin_stack][yard[origin_stack].size()-1];
            int blocked_containers = count_blocked(yard[i], c2relocate);

            if(blocked_containers < min_blocks){
                min_blocks = blocked_containers;
                choosed_stack = i; 
            }

        }
    }

    return choosed_stack;
}


int RI(vector<vector<int>> &yard, int origin_stack){

    //Recorremos todo el yard y vamos calculando
    int h_origin = yard[origin_stack].size();
    int c2relocate = yard[origin_stack][h_origin-1];
    int choosed_stack = 0;
    int min_ri = yard[0].size();

    for(int i = 0; i < n_bays*n_rows; i++){
        int ri_stack = 0;

        if(i == origin_stack){
            continue;
        }

        if(max_h == yard[i].size()) //Stack lleno
            continue;

        int size = yard[i].size();
        for(int j = 0; j < size; j++){
            if(yard[i][j] < c2relocate)
                ri_stack++;
        }

        //Verificamos si es mejor que lo que ya hemos encontrado
        if(min_ri > ri_stack){
            min_ri = ri_stack;
            choosed_stack = i;
        }
    }

    //Retornamos el mejor stack para moverse
    return choosed_stack;
}

int RIL(vector<vector<int>> &yard, int origin_stack){

    //Recorremos todo el yard y vamos calculando
    int h_origin = yard[origin_stack].size();
    int c2relocate = yard[origin_stack][h_origin-1];
    int choosed_stack = 0;
    int choosed_container = 0;
    int min_ri = yard[0].size();

    for(int i = 0; i < n_bays*n_rows; i++){
        int ri_stack = 0;
        int highest_c = 0;


        if(i == origin_stack){
            continue;
        }

        if(max_h == yard[i].size()) //Stack lleno
            continue;

        if(yard[i].size() == 0) //Forzar elegir stack vacio
            return i;

        int size = yard[i].size();
        for(int j = 0; j < size; j++){
            if(yard[i][j] < c2relocate){
                ri_stack++;
                if(yard[i][j] > highest_c)
                    highest_c = yard[i][j];
            }
        }

        //Verificamos si es mejor que lo que ya hemos encontrado
        if(min_ri > ri_stack){
            min_ri = ri_stack;
            choosed_stack = i;
            choosed_container = highest_c;
        }

        else if(min_ri == ri_stack){
            if(highest_c > choosed_container){
                choosed_stack = i;
                choosed_container = highest_c;
            }
        }
    }

    //Retornamos el mejor stack para moverse
    return choosed_stack;
}


//Función para elegir una de las funciones miopes disponibles de forma random
//La idea es que le aplique una heurística al yard y retorne la heurística que utilizó
int apply_random_heuristic(vector<vector<int>> &yard, vector<int> &stack_position, int origin_stack){

    //Obtenemos un número aleatorio para elegir la heurística
    int n_heuristic = 4;
    int choosed = getRandomInt(1, n_heuristic);
    int destiny_stack;


    //Heurística space
    if (choosed ==  1){
        destiny_stack = myopic_space(yard, origin_stack);
    }
    //Heurística block
    else if (choosed == 2){
        destiny_stack = myopic_blocked(yard, origin_stack);
    }
    //Heurística RI
    else if(choosed == 3){
        destiny_stack = RI(yard, origin_stack);
    }
    //Heurística RIL
    else if(choosed == 4){
        destiny_stack = RIL(yard, origin_stack);
    }


    //Realizamos el movimiento
    int h_origin = yard[origin_stack].size();
    int c2relocate = yard[origin_stack][h_origin-1];
    yard[origin_stack].pop_back();
    yard[destiny_stack].push_back(c2relocate);
    stack_position[c2relocate] = destiny_stack;


    return choosed;
}