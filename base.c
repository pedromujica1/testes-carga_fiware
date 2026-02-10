//Atividade Avaliativa 02 - Comparação de Dois Algoritmos de Caminho Mínimo
//Alunos: Pedro Miotto Mujica e Ithony Elvis de Lima Avila
//Arquivo: grafo.cpp
//gcc g.c -o tsp -lm; ./tsp 'Entrada 10.txt
//Objetivo: Implementar os algoirtmos Bellman-Ford e Djikistra par comparação de Dois Algoritmos de Caminho Mínimo

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#define INF INT_MAX

typedef struct aresta
{
    int vertice_ini;
    int peso;
    int vertice_fim;
    
} aresta;

typedef struct TSPSoluca {
    int melhor_custo;
    int *melhor_rota;
    int *rota_atual;
    
} TSPSolucao;


void verifica_params(int argc){
    if (argc < 2){
        fprintf(stderr,"Você esqueceu de informar o arquivo de entrada\n");
    }
}

void verifica_arquivo(const char *arquivo, char *argv[]){
    if (arquivo == NULL){
        fprintf(stderr,"ERRO: Não foi possível abrir o arquivo '%s'\n",argv[1]);
        perror("Motivo: ");
    }
}

void leitura_vertices(FILE *arquivo,int *vertices){
    fscanf(arquivo,"%d",vertices);
}

void leitura_adj(FILE *arquivo,int vertices,int **matriz_adj){
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            fscanf(arquivo,"%d", &matriz_adj[i][j]);
        }
    }
}

void imprime_matriz(int vertices,int **matriz_adj){
    
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            printf("%4d ", matriz_adj[i][j]);
        }
        printf("\n");
    }
}

void imprime_adj(int n, int mat[n][n]) {
    for (int i = 0; i < n; i++) {
        printf("Vertice %d:", i);
        for (int j = 0; j < n; j++) {
            printf(" -> (%d, peso=%d)", j, mat[i][j]);
        }
        printf("\n");
    }
}

void imprime_total_arestas(int arestas_nao_direcionadas, aresta totalAresta[]){
    for (int i = 0; i < arestas_nao_direcionadas; i++) {
        printf("Aresta %d: %d -> %d, peso=%d\n",
            i,
            totalAresta[i].vertice_ini,
            totalAresta[i].vertice_fim,
            totalAresta[i].peso);
    }
}

void bellman_ford(int vertices,int no_inicio,int total_arestas,aresta conjuntoArestas[],int distancias_finais[],int predecessores[]){
    
    //inicializa distancias e predecessores
    for (int i = 0; i < vertices; i++) {
        //define com macho INT_MAX
        distancias_finais[i] = INF;
        predecessores[i] = -1;
    }

    distancias_finais[no_inicio] = 0;

    //relaxamento por V-1 iterações
    int iteracoes = vertices -1;
    for (int i = 0; i < iteracoes; i++){
        bool distancia_melhorou = false;
        for (int j = 0; j < total_arestas; j++){
            int vertice_origem = conjuntoArestas[j].vertice_ini;
            int vertice_destino = conjuntoArestas[j].vertice_fim;
            int vertice_peso = conjuntoArestas[j].peso;

            int custo_local = vertice_peso + distancias_finais[vertice_origem];

            if (distancias_finais[vertice_origem] != INF && custo_local < distancias_finais[vertice_destino]) {
                distancias_finais[vertice_destino] = custo_local;
                predecessores[vertice_destino] = vertice_origem;
                distancia_melhorou = true;
            }
        }
        if (!distancia_melhorou)
        {
            break;
        }
    }

}

void calcula_distancias(int vertices,int **matriz_distancias,int **matriz_predecessores,int total_arestas,aresta conjuntoArestas[],int *distancias_finais,int *predecessores) {
    for (int origem = 0; origem < vertices; origem++)
    {
        bellman_ford(vertices,origem,total_arestas,conjuntoArestas,distancias_finais,predecessores);
        for (int destino = 0; destino < vertices; destino++){
            matriz_distancias[origem][destino] = distancias_finais[destino];
            matriz_predecessores[origem][destino] = predecessores[destino];
        }
    }
    //imprime matriz de distancias reais
    //imprime_matriz(vertices,matriz_distancias);
    
    
}

void caminho_minimo(int predecessores[], int inicio, int fim){
    if (predecessores[fim] == -1 && inicio != fim){
        printf("Não há caminho do nó %d para o nó %d\n", inicio, fim);
        return;
    }

    int caminho[100];
    int indice = 0;
    int atual = fim;

    while (atual != -1){
        caminho[indice++] = atual;
        atual = predecessores[atual];
    }

    printf("Caminho mínimo do nó %d para o nó %d: ", inicio, fim);
    for (int i = indice -1; i >= 0; i--){
        printf("%d ", caminho[i]);
        if (i != 0){
            printf("-> ");
        }
    }
    printf("\n");
}

//função para calcular custo baseado na rota
int calcula_custo_rota(int vertices, int **matriz_distancias, int *rota){
    int custo_total = 0;
    for (int i = 0; i < vertices; i++){
        int vertice_atual = rota[i];
        int vertice_proximo = rota[i+1];
        custo_total += matriz_distancias[vertice_atual][vertice_proximo];
    }
    return custo_total;
}

void solucao_inicial(int vertices, int **matriz_distancias, int *rota_inicial){

    int *nao_visitados = malloc(vertices * sizeof(int));
    int *rota_parcial  = malloc((vertices + 1) * sizeof(int));

    

    for (int i = 0; i < vertices; i++){
        nao_visitados[i] = 1;
    }
    //salva na rota parcial o caminho entre 0 e 1
    rota_parcial[0] = 0;
    rota_parcial[1] = 1;
    rota_parcial[2] = 0;

    nao_visitados[1] = 0; //marca como já inserido
    nao_visitados[0] = 0; //marca como já inserido

    int tamanho_rota = 3;
    //int vertices_atual = rand() % vertices;
    

    while (tamanho_rota<vertices+1){
        
        int melhor_candidato = -1;
        int melhor_pos = -1;
        int melhor_delta = INF;

        //logica da INSERÇÂO MAIS BARATA
        //para cada vertices fora darota
        for (int i = 0; i < vertices; i++){
            if (nao_visitados[i] != 0){
                //para cada aresta fora da rota
                for (int j = 0; j < tamanho_rota-1; j++)
                {
                    //vertices que já fazem parte da rota
                    int vertice1 = rota_parcial[j];
                    int vertice2 = rota_parcial[j+1];

                    //calculo do delta
                    int delta = matriz_distancias[vertice1][i] + matriz_distancias[i][vertice2] - matriz_distancias[vertice1][vertice2];

                    if (delta < melhor_delta) { 
                        melhor_delta = delta; 
                        melhor_candidato = i; 
                        melhor_pos = j + 1; 
                    }

                }
            }
        }
        for (int i = tamanho_rota; i > melhor_pos; i--){
            rota_parcial[i] = rota_parcial[i-1];

        }
        rota_parcial[melhor_pos] = melhor_candidato;
        tamanho_rota++;
        nao_visitados[melhor_candidato] = 0;
    }
    // Copia para saída
    for (int i = 0; i < tamanho_rota; i++) {
        rota_inicial[i] = rota_parcial[i];
    }
    
    free(nao_visitados);
    free(rota_parcial);
    
}
void recozimento_simulado(int vertices, int **matriz_distancias, int *rota_inicial,int custo_minimo){

    int custo_ini = calcula_custo_rota(vertices, matriz_distancias, rota_inicial);
    printf("Custo da Rota Inicial: %d\n", custo_ini);
    TSPSolucao resultado;
    resultado.melhor_rota =  malloc((vertices+1) * sizeof(int));
    resultado.rota_atual =  malloc((vertices+1) * sizeof(int));
    resultado.melhor_custo = custo_ini;

    //salva rota inicial no rota_atual
    for (int i = 0; i <= vertices; i++)
    {
        resultado.rota_atual[i] = rota_inicial[i];
    }

    for (int i = 0; i <= vertices; i++)
    {
        resultado.melhor_rota[i] = resultado.rota_atual[i];
    }

    //parametros do SA
    double temp = 2000.0;
    double alpha = 0.995;
    int melhor_custo = custo_ini;

    //criterio de parada
    clock_t tempo_inicio = clock();
    double segundos = 0.0;
    int iteracoes = 0;
    int max_segundos = 30;

    while (1){
        //altera a quantidade de segundos
        segundos = (double)(clock() - tempo_inicio) / CLOCKS_PER_SEC;
     
        if (segundos >= max_segundos) {
            break;
        }

        //pega indices [1, n-2]
        int i = 1 + rand() % (vertices - 2);
        //pega indices [i+1, n-1]     
        int j = i + 1 + rand() % (vertices - i - 1); 

        int a = resultado.rota_atual[i-1]; //vertices antes do corte
        int b = resultado.rota_atual[i];//inicio do segmento invertido
        int c = resultado.rota_atual[j];// fim do segumento invertido
        int d = resultado.rota_atual[j+1]; //cidade dps do corte

        int custo_antigo = matriz_distancias[a][b] + matriz_distancias[c][d];
        int novo_custo = matriz_distancias[a][c] + matriz_distancias[b][d];
        int delta = novo_custo - custo_antigo;

        double num_rand = (double)rand() / (double)RAND_MAX;

        // regra de aceitação
        if (delta < 0 || num_rand < exp(-(double)delta / temp)) {

            //invertendo segumento da rota
            for (int l = 0; l < (j - i + 1)/2; l++) {
                int tmp = resultado.rota_atual[i + l];
                resultado.rota_atual[i + l] = resultado.rota_atual[j - l];
                resultado.rota_atual[j - l] = tmp;
            }

            custo_ini += delta;

            if (custo_ini < resultado.melhor_custo) {
                resultado.melhor_custo = custo_ini;
                for (int k = 0; k <= vertices; k++){
                    resultado.melhor_rota[k] = resultado.rota_atual[k];

                } 
            }
        }

        //resfriamento
        temp *= alpha;
        //para evitar underflow
        if (temp < 1e-9) temp = 1e-9; // evita underflow
        
        
        iteracoes++;
    }
    // devolve melhor rota
    for (int i = 0; i <= vertices; i++) rota_inicial[i] = resultado.melhor_rota[i];

    printf("SA: melhor custo = %d\n", resultado.melhor_custo);
    custo_minimo = resultado.melhor_custo;

    free(resultado.melhor_rota);
    free(resultado.rota_atual);
     

}

void imprime_lista(int vertices, int grau[],aresta lista_adj[vertices][vertices]){
    for (int i = 0; i < vertices; i++) {
        //printf("Vertice %d:", lista_adj[i][]);
    
        for (int k = 0; k < grau[i]; k++) {
            printf("%d -> (%d, peso=%d) ",
                lista_adj[i][k].vertice_ini,
                lista_adj[i][k].vertice_fim,
                lista_adj[i][k].peso);
        }
        printf("\n");    
    }

}

void escreve_arquivo_saida_tsp(const int *rota_final, int vertices, int melhor_custo, int instancia) {

    char nome_arquivo[64];
    sprintf(nome_arquivo, "2_caixeiro%d_saida.txt", instancia);

    FILE *arquivo_saida = fopen(nome_arquivo, "w");
    if (arquivo_saida == NULL) {
        printf("Erro ao abrir arquivo de saída.\n");
        return;
    }

    fprintf(arquivo_saida, "---- Solução Final Após Recozimento Simulado ----\n");
    fprintf(arquivo_saida, "Vertices: %d\n", vertices);
    fprintf(arquivo_saida, "Custo total: %d\n\n", melhor_custo);

    fprintf(arquivo_saida, "Rota: ");
    for (int i = 0; i <= vertices; i++) {
        fprintf(arquivo_saida, "%d", rota_final[i]);
        if (i < vertices) fprintf(arquivo_saida, " -> ");
    }
    fprintf(arquivo_saida, "\n");

    fclose(arquivo_saida);
}


int main(int argc, char *argv[]){
    //parte1: leitura do arquivo e verificação da entrada
    printf("\n---------- HELLO CAIXEIRO VIAJANTE!! ----------\n");
    verifica_params(argc);
    const char *arquivo_entrada = argv[1];
    FILE *arquivo = fopen(arquivo_entrada,"r");
    verifica_arquivo(arquivo_entrada, argv);

    //parte1: leitura do número de vértices
    int vertices;
    leitura_vertices(arquivo,&vertices);

    //parte2: leitura da matriz de adjacência
    int **matriz_adj = malloc(vertices * sizeof(int*));
    for (int i = 0; i < vertices; i++)
        matriz_adj[i] = malloc(vertices * sizeof(int));

    leitura_adj(arquivo,vertices,matriz_adj);
    fclose(arquivo);

    //parte3: impressão da matriz de adjacência
    //imprime_matriz(vertices,matriz_adj);

    
    //malloc de aresta
    aresta **lista_adj = malloc(vertices * sizeof(aresta *));
    for (int i = 0; i < vertices; i++) {
        lista_adj[i] = malloc(vertices * sizeof(aresta));
    }

    int *grau = malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        grau[i] = 0;
    }

    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (matriz_adj[i][j] != 0 && i != j) {
                lista_adj[i][grau[i]].vertice_ini = i;
                lista_adj[i][grau[i]].vertice_fim = j;
                lista_adj[i][grau[i]].peso = matriz_adj[i][j];
                grau[i]++;
            }
        }
    }
    
    
    
    int arestas = 0;
    for (int i = 0; i < vertices; i++) {
        arestas += grau[i];
    }
    
    printf("Total de Arestas: %d\n", arestas);
    int total_arestas = arestas*2;
    aresta *conjuntoArestas = malloc(total_arestas * sizeof(aresta));
    if (!conjuntoArestas) {
        fprintf(stderr, "Erro ao alocar conjuntoArestas\n");
        exit(1);
    }
    

    int indice = 0;

    for (int i = 0; i < vertices; i++) {
        //printf("Vertice %d:", lista_adj[i][]);    
        for (int k = 0; k < grau[i]; k++) {
            
            int j = lista_adj[i][k].vertice_fim;
            int peso = lista_adj[i][k].peso;

            // i -> j
            conjuntoArestas[indice].vertice_ini = i;
            conjuntoArestas[indice].vertice_fim = j;
            conjuntoArestas[indice].peso = peso;
            indice++;

            // j -> i (aresta inversa)
            conjuntoArestas[indice].vertice_ini = j;
            conjuntoArestas[indice].vertice_fim = i;
            conjuntoArestas[indice].peso = peso;
            indice++;
        }   
    }
    
    int *distancias_finais = malloc(vertices * sizeof(int));
    int **matriz_distancias = malloc(vertices * sizeof(int *));
    int **matriz_predecessores = malloc(vertices * sizeof(int *));

    for (int i = 0; i < vertices; i++) {
        matriz_distancias[i] = malloc(vertices * sizeof(int));
        matriz_predecessores[i] = malloc(vertices * sizeof(int));
    }

    int *rota_inicial = malloc((vertices + 1) * sizeof(int));
    int *predecessores = malloc(vertices * sizeof(int));
    int custo_minimo = 0;
    //calcula distancias entre todos os pares de nós
    calcula_distancias(vertices,matriz_distancias,matriz_predecessores,total_arestas,conjuntoArestas,distancias_finais,predecessores);

    solucao_inicial(vertices,matriz_distancias,rota_inicial);

    recozimento_simulado(vertices,matriz_distancias,rota_inicial,custo_minimo);

    escreve_arquivo_saida_tsp(rota_inicial, vertices, custo_minimo, vertices);

  
    for (int i = 0; i < vertices; i++) {
        free(matriz_adj[i]);
    }
    free(matriz_adj);

    for (int i = 0; i < vertices; i++) {
        free(matriz_distancias[i]);
        free(matriz_predecessores[i]);
    }
    free(matriz_distancias);
    free(matriz_predecessores);

    for (int i = 0; i < vertices; i++) {
        free(lista_adj[i]);
    }
    free(lista_adj);
    free(rota_inicial);
    free(distancias_finais);
    free(conjuntoArestas);
    free(grau);
    free(predecessores);
    return 0;
}