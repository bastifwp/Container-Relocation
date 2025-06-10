#include<bits/stdc++.h>

#include "global.h"

using namespace std;

/*
    ---------- Estas funciones consideran aleatoriedad, por eso las comenté ---------------

//Función que retorna una lista con los valores de la función miope
//(valor_funcion, stack)
void myopic_space(vector<vector<int>> &yard, vector<pair<int, int>> &values, int origin_stack){
    //Recorremos todo el yard y vamos calculando
    for(int i = 0; i < n_bays*n_rows; i++){
   
        if(i == origin_stack){
            values.push_back(pair(0, i));
            continue;
            //cout << "Rechazado porque es el mismo origen" << endl;
        }

        int value = max_h - yard[i].size();
        if(value > 0) values.push_back(pair(value, i));
    }

}*/

/*
int count_blocked(vector<int> stack, int c2relocate){

    int blocked_containers = 0;
    for(int i = 0; i < stack.size(); i++){
        if(stack[i]< c2relocate) blocked_containers++;
    }
    return blocked_containers;
}

void myopic_blocked(vector<vector<int>> &yard, vector<pair<int, int>> &values, int num_choices, int origin_stack)
{
    for (int i = 0; i < num_choices; i++)
    {
        int id_selected = getRandomInt(0, n_bays*n_rows-1);
        int feasible = max_h - yard[id_selected].size();

        
        if(id_selected != origin_stack && feasible != 0){

            int blocked_containers = count_blocked(yard[id_selected], yard[origin_stack].size()-1);

            values.push_back(pair(blocked_containers,id_selected));
        }
        else i--;

    }

}
*/



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

    if(debug) printf("%d %d %d (choosed: %d)\n", c2relocate, origin_stack, destiny_stack, choosed);

    return choosed;
}



individuo initialize_ind(vector<vector<int>> &initial_yard, vector<int>& stack_position){


    individuo new_ind;
    new_ind.moves = {};
    new_ind.fobj[0] = 0;
    new_ind.fobj[1] = 0;
        
    //Copiamos variables iniciales para trackear los movimientos
    vector<vector<int>> actual_yard = initial_yard;
    vector<int> actual_positions = stack_position; 

    //Creamos movimientos hasta que ya no queden containers
    int id_to_retrieve = 1;
    int n_containers_actual = n_initial_containers;
    while(n_containers_actual > 0){

        new_ind.fobj[0]++;

        int origin_stack = actual_positions[id_to_retrieve];
        int h_origin = actual_yard[origin_stack].size();

        //Si está en el tope lo sacamos y no guardamos ninguna heurística
        if(id_to_retrieve == actual_yard[origin_stack][h_origin-1]){
            actual_yard[origin_stack].pop_back();
            actual_positions[id_to_retrieve] = -1;

            if(debug) printf("%d %d %d\n", id_to_retrieve, origin_stack, -1);

            id_to_retrieve++;
            n_containers_actual--;
        }

        //Si no es así entonces tenemos que decidir que heurística usar y guardarla en la lista
        else{
            int coded_heuristic = apply_random_heuristic(actual_yard, actual_positions, origin_stack);
            new_ind.moves.push_back(coded_heuristic);
        }

    }
    
    //Retornamos el individuo creado
    return new_ind;

}