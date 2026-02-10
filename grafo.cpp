//Atividade Avaliativa 02 - Comparação de Dois Algoritmos de Caminho Mínimo
//Alunos: Pedro Miotto Mujica e Ithony Elvis de Lima Avila
//Arquivo: grafo.cpp
//gcc g.c -o tsp -lm; ./tsp 'Entrada 10.txt
//Objetivo: Implementar os algoirtmos Bellman-Ford e Djikistra par comparação de Dois Algoritmos de Caminho Mínimo

#include<iostream>
#include<stdlib.h>
using namespace std;

struct no{
    int vertices;
    no* vizinhos[7];
};

int main (int argc,char const *argv []){
    int grafo[7][7];

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            grafo[i][j] = 0;
            /* code */
        }
        
        /* code */
    }
    grafo[0][1] = 1;
    grafo[0][3] = 1;
    grafo[1][0] = 1;
    grafo[1][2] = 1;
    grafo[1][4] = 1;
    grafo[2][1] = 1;
    grafo[2][3] = 1;
    grafo[3][0] = 1;
    grafo[3][2] = 1;
    grafo[3][4] = 1;
    grafo[4][1] = 1;
    grafo[4][2] = 1;
    grafo[4][3] = 1;
    grafo[4][5] = 1;
    grafo[5][4] = 1;

    for (int i = 0; i < 6; i++)
    {
        cout << "\n"<< "vértice " << i+1 << ":";
       
        for (int j = 0; j < 6; j++)
        {
            cout << " " << grafo[i][j];
        }
        cout << endl;
    }
    return 0;
}