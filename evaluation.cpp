#include<bits/stdc++.h>

#include "global.h"

using namespace std;

void apply_chosen_heuristic(vector<vector<int>> &yard, vector<int> &stack_position, int origin_stack, int choosed){
    int destiny_stack;

    //Heurística space
    if (choosed == 1){
 //       cout << "my\n";
        destiny_stack = myopic_space(yard, origin_stack);
    }
    //Heurística RI
    else if(choosed == 2){
  //      cout << "ri\n";
        destiny_stack = RI(yard, origin_stack);
    }
    //Heurística RIL
    else if(choosed == 3){
//        cout << "ril\n";
        destiny_stack = RIL(yard, origin_stack);
    }
    //Heurística top_diff
    else if(choosed == 4){
 //       cout << "WTf\n";
        destiny_stack = top_diff(yard, origin_stack);
    }

    else if(choosed == 5){
   //     cout << "WTF\n";
        destiny_stack = myopic_min_space(yard, origin_stack);
    }

    else if(choosed == 6){
   //     cout << "WTF\n";
        destiny_stack = RI_inverse(yard, origin_stack);
    }

    //Realizamos el movimiento
    //cout << "DESTINY: " << destiny_stack << endl;
    int h_origin = yard[origin_stack].size();
    int c2relocate = yard[origin_stack][h_origin-1];
    yard[origin_stack].pop_back();
    yard[destiny_stack].push_back(c2relocate);
    stack_position[c2relocate] = destiny_stack;

}


void evaluateInd(individuo &ind, vector<vector<int>> &initial_yard, vector<int> &stack_position){

    ind.fobj[0] = 0; ind.fobj[1] = 0;

    //Copiamos variables iniciales para trackear los movimientos
    vector<vector<int>> actual_yard = initial_yard;
    vector<int> actual_positions = stack_position;

    //Inicializamos variables
    int id_to_retrieve = 1;
    int n_containers_actual = n_initial_containers;
    int move_actual = 0;
    int n_moves = ind.moves.size();

    //Hasta que no queden containers
    while(n_containers_actual > 0){

        ind.fobj[0]++;
        int origin_stack = actual_positions[id_to_retrieve];
        int h_origin = actual_yard[origin_stack].size();

        //Si está en el tope lo sacamos
        if(id_to_retrieve == actual_yard[origin_stack][h_origin-1]){
            actual_yard[origin_stack].pop_back();
            actual_positions[id_to_retrieve] = -1;
            id_to_retrieve++;
            n_containers_actual--;
        }

        //Si no es así entonces aplicamos heuristica que toca
        else{

            //Si aun quedan movimientos en la lista, aplicarlos
            if(move_actual < n_moves){
                apply_chosen_heuristic(actual_yard, actual_positions, origin_stack, ind.moves[move_actual]);
                move_actual++;
            }
            //Si no quedan, agregar nuevos movimientos de forma aleatoria
            else{
                int coded_heuristic = apply_random_heuristic(actual_yard, actual_positions, origin_stack);
                ind.moves.push_back(coded_heuristic);
            }
            
            //Si se acaban los movimentos de la lista y aun quedan container, repetirlos desde el principio
            //move_actual == n_moves-1? move_actual = 0 : move_actual++;
        }   
    }

    //Si no se utilizaron todos los movimientos, eliminar los sobrantes
    while(move_actual < n_moves){
        ind.moves.pop_back();
        move_actual++;
    }
}

void evaluatePop(vector<individuo> &pop, vector<vector<int>> &initial_yard, vector<int> &stack_position){

    for (int i = 0; i < params.popsize; i++)
    {
        evaluateInd(pop[i], initial_yard, stack_position);
    }
    
}


