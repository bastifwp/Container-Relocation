#ifndef UTILS_H
#define UTILS_H

#include <bits/stdc++.h>


struct individuo
{
    // Lista de movimientos (heurísticas codificadas)
    std::vector<int> moves;
    
    // Funciones objetivo
    int fobj[2];

};


struct hyperparams{
    float pmyo;
    float pmut;
    float pcross;
    int popsize;
    int max_gen;
    int k; //Cantidad de grupos de la lista de movimientos
    int n_heu;//Cantidad de heurísticas
    int elite;
};


/* Reader functions */
void readInstance(std::ifstream &f, std::vector<std::vector<int>> &yard, std::vector<int> &stack_position);

/* Random functions */
void randomize(int seed);
int getRandomInt(int a, int b);
float getRandomProb();

/* Initialice functions */
individuo initialize_ind(std::vector<std::vector<int>> &initial_yard, std::vector<int> &stack_position);

/*Heuristics*/
int RIL(std::vector<std::vector<int>> &yard, int origin_stack);
int RI(std::vector<std::vector<int>> &yard, int origin_stack);
int myopic_blocked(std::vector<std::vector<int>> &yard,  int origin_stack);
int myopic_space(std::vector<std::vector<int>> &yard, int origin_stack);

/*Evolutive Algorithm functions*/
std::vector<individuo> one_point_crossover(individuo padre1, individuo padre2);
void swap(individuo &ind);
void inversion(individuo &ind);
void intFlip(individuo &ind);
void mutatePop(std::vector<individuo> &pop);
void evaluateInd(individuo &ind, std::vector<std::vector<int>> &yard, std::vector<int> &stack_position);
void evaluatePop(std::vector<individuo> &pop, std::vector<std::vector<int>> &initial_yard, std::vector<int> &stack_position);
void generateNewPop(std::vector<individuo> &old_pop);

/* Extra functions */
void printYard(std::vector<std::vector<int>> &yard);
void printInd(individuo &ind);
std::tuple<int,int,int> search_next_c(std::vector<std::vector<int>> &yard);
bool desc_sort(std::pair<int, int>& a,  std::pair<int, int>& b);
bool compararPorFobjAsc(const individuo &a, individuo &b);


/* ------------- VARIABLES GLOBALES ---------------------*/

// Declaramos variables globales de la instancia
extern std::string instance_name;
extern int n_bays;
extern int n_rows;
extern int max_h;
extern int n_initial_containers;
extern std::vector<std::vector<int>> initial_yard;
extern std::vector<int> stack_position;
extern int debug;

//declaramos los hiperparametros
extern hyperparams params;


// Declaramos el generador aleatoreo
extern std::mt19937 rng;


#endif