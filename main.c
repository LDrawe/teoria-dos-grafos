#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int main() {
    FILE* arquivo = fopen("./dados.txt", "r");

    if (arquivo == NULL) {
        perror("Erro: Não foi possível abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    fscanf(arquivo, "%d\n %d", &numOfVertices, &numOfEstradas);
    
    if (numOfEstradas == 0){
        printf("Necessário construir %d estrada(s)", numOfVertices - 1);
        return 0;
    }
    
    int** grafo = criaMatrizAdjacencia();
    preencheGrafo(grafo, arquivo);
    fclose(arquivo);
    
    int* visited = (int*) calloc(numOfVertices, sizeof(int)); // Calloc vai inicializar os elementos em 0
    
    int islands = 1;
    int unvisitedVertice = firstUnvisitedVertice(visited);

    while (unvisitedVertice) {
        dfs(unvisitedVertice, grafo, visited, islands);
        islands++;
        unvisitedVertice = firstUnvisitedVertice(visited);
    }
    
    const int ilhas = getNumberOfDesconexos(visited);

    if (ilhas == 0) {
        printf("Promessa cumprida!\n");
        return 0;
    }
    
    printf("Necessario construir %d estrada(s)\n", ilhas);
    
    free(grafo);
    free(visited);
    return 0;
}