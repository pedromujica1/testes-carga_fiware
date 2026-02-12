//Atividade Avaliativa 02 - Comparação de Dois Algoritmos de Caminho Mínimo
//Alunos: Pedro Miotto Mujica e Ithony Elvis de Lima Avila
//Arquivo: grafo.cpp
//g++ 
//Objetivo: Implementar os algoirtmos Bellman-Ford e Djikistra par comparação de Dois Algoritmos de Caminho Mínimo

#include<iostream>
#include<stdlib.h>
#include <iostream>
#include <vector>
#include <climits>

#define INF INT_MAX
using namespace std;

struct no{
    int vertices;
    no* vizinhos[7];
};


typedef struct aresta {
    int vertice_ini;
    int peso;
    int vertice_fim;
} aresta;

// ======= (SEUS MÉTODOS) adaptados =======

void bellman_ford(int vertices,int no_inicio,int total_arestas,const vector<aresta>& conjuntoArestas,vector<int>& distancias_finais,vector<int>& predecessores) {
    
    //inicializa distancias e predecessores
    distancias_finais.assign(vertices, INF);
    predecessores.assign(vertices, -1);

    distancias_finais[no_inicio] = 0;

    //relaxamento por V-1 iterações
    int relaxamentos = 0;
    int iteracoes = vertices - 1;
    for (int i = 0; i < iteracoes; i++) {
        bool distancia_melhorou = false;

        for (int j = 0; j < total_arestas; j++) {
            int vertice_origem  = conjuntoArestas[j].vertice_ini;
            int vertice_destino = conjuntoArestas[j].vertice_fim;
            int vertice_peso    = conjuntoArestas[j].peso;

            if (distancias_finais[vertice_origem] != INF) {
                int custo_local = vertice_peso + distancias_finais[vertice_origem];

                if (custo_local < distancias_finais[vertice_destino]) {
                    distancias_finais[vertice_destino] = custo_local;
                    predecessores[vertice_destino] = vertice_origem;
                    distancia_melhorou = true;
                    relaxamentos++;
                }
            }
        }

        if (!distancia_melhorou) break;
    }

    //falta implementar verficação de ciclo negativo

}

void caminho_minimo(const vector<int>& predecessores, int inicio, int fim) {
    if (predecessores[fim] == -1 && inicio != fim) {
        cout << "Não há caminho do nó " << inicio << " para o nó " << fim << "\n";
        return;
    }

    vector<int> caminho;
    int atual = fim;

    while (atual != -1) {
        caminho.push_back(atual);
        atual = predecessores[atual];
    }

    cout << "Caminho mínimo do nó " << inicio << " para o nó " << fim << ": ";
    for (int i = (int)caminho.size() - 1; i >= 0; i--) {
        cout << caminho[i];
        if (i != 0) cout << " -> ";
    }
    cout << "\n";
}


vector<aresta> matriz_para_arestas(const vector<vector<int>>& grafo) {
    int n = (int)grafo.size();
    vector<aresta> edges;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // Regra: 0 = sem aresta; (se quiser permitir peso 0, precisa mudar isso)
            if (grafo[i][j] != 0) {
                edges.push_back({i, grafo[i][j], j});
            }
        }
    }
    return edges;
}

void imprime_matriz(const vector<vector<int>>& g) {
    int n = (int)g.size();
    for (int i = 0; i < n; i++) {
        cout << "vértice " << i << ": ";
        for (int j = 0; j < n; j++) {
            cout << g[i][j] << " ";
        }
        cout << "\n";
    }
}

int main() {
    const int N = 7;

    // Matriz de adjacência (como você já tinha)
    vector<vector<int>> grafo(N, vector<int>(N, 0));

    // Seu grafo (aqui está como peso 1 nas conexões)
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

    cout << "Matriz de adjacência:\n";
    imprime_matriz(grafo);

    // Converte matriz em lista de arestas (para Bellman-Ford)
    vector<aresta> edges = matriz_para_arestas(grafo);
    int total_arestas = (int)edges.size();

    // Executa Bellman-Ford
    int inicio = 0; // nó inicial (0-based)
    vector<int> dist, pred;
    bellman_ford(N, inicio, total_arestas, edges, dist, pred);

    // Mostra distâncias
    cout << "\nDistâncias a partir do nó " << inicio << ":\n";
    for (int i = 0; i < N; i++) {
        cout << "  " << inicio << " -> " << i << " = ";
        if (dist[i] == INF) cout << "INF\n";
        else cout << dist[i] << "\n";
    }

    // Mostra caminho mínimo até um destino (exemplo)
    int destino = 5;
    cout << "\n";
    caminho_minimo(pred, inicio, destino);

    return 0;
}

