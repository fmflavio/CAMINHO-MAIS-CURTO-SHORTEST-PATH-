#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>
using namespace std;

typedef struct { //DIJKSTRA
    unsigned int first;
    unsigned int second;
    unsigned int weight;
} weighted_edge;

typedef struct { //BELLMAN-FORD e FLOYD-WARSHALL
    unsigned int first;
    unsigned int second;
    int weight;
} weighted_arc;


unsigned int *dijkstra(const weighted_edge *edges, unsigned int size, unsigned int order, unsigned int vertex){
    unsigned int i;
    unsigned int *distances = (unsigned int*) malloc(order * sizeof(unsigned int));
    unsigned int *unvisited = (unsigned int*) malloc(order * sizeof(unsigned int));
    unsigned int unvisited_count = order;
    unsigned int current = vertex;
    if (distances == NULL || unvisited == NULL) {
        free(distances);
        free(unvisited);
        return NULL;
    }
    /* All distances start infinite and all vertices start unvisited */
    for (i = 0; i < order; i++) {
        distances[i] = UINT_MAX;
        unvisited[i] = 1;
    }
    /* Distance to starting vertex is 0 */
    distances[vertex] = 0;
    while (unvisited_count > 0) {
        /* Update the distances to all neighbours */
        unsigned int e, v;
        unsigned int min_distance;
        for (e = 0; e < size; e++) {
            if (edges[e].first == current || edges[e].second == current) {
                const unsigned int neighbour = edges[e].first == current ?
                    edges[e].second : edges[e].first;
                const unsigned int distance = distances[current] + edges[e].weight;
                if (distance < distances[neighbour]) {
                    distances[neighbour] = distance;
                }
            }
        }
        /* Finished with this vertex */
        unvisited[current] = 0;
        unvisited_count--;
        /* Find the nearest unvisited vertex */
        min_distance = 0;
        for (v = 0; v < order; v++) {
            if (unvisited[v] == 1 && (min_distance == 0 || distances[v] < min_distance)) {
                min_distance = distances[v];
                current = v;
            }
        }
    }
    free(unvisited);
    return distances;
}

int *bellman_ford(const weighted_arc *arcs, unsigned int size, unsigned int order, unsigned int vertex) {
    unsigned int i;
    int *distances = (int*) malloc(order * sizeof(unsigned int));
    unsigned int a, v, negative_cycle = 0;
    if (distances == NULL) {
        return NULL;
    }
    /* All distances start infinite */
    for (i = 0; i < order; i++) {
        distances[i] = INT_MAX;
    }
    /* Distance to starting vertex is 0 */
    distances[vertex] = 0;
    /* Relax edges repeatedly */
    for (v = 0; v < order; v++) {
        for (a = 0; a < size; a++) {
            const unsigned int first = arcs[a].first;
            const unsigned int second = arcs[a].second;
            const int weight = arcs[a].weight;
            if (distances[first] != INT_MAX
                && distances[first] + weight < distances[second])
            {
                distances[second] = distances[first] + weight;
            }
        }
    }
    /* Check for negative weight cycle */
    for (a = 0; a < size && !negative_cycle; a++) {
        const unsigned int first = arcs[a].first;
        const unsigned int second = arcs[a].second;
        const int weight = arcs[a].weight;
        negative_cycle = distances[first] + weight < distances[second];
    }
    if (negative_cycle) {
        free(distances);
        distances = NULL;
    }

    return distances;
}

int **floyd_warshall(const weighted_arc *arcs, unsigned int size, unsigned int order){
    unsigned int i, j, k;
    int **distances = (int**) malloc(order * sizeof(int *));
    /* Initialise the distance table */
    for (i = 0; i < order; i++) {
        distances[i] = (int*) malloc(order * sizeof(int));
        for (j = 0; j < order; j++) {
            if (i == j) {
                distances[i][j] = 0;
            }
            else {
                distances[i][j] = INT_MAX;
            }
        }
    }
    /* Add the distance for each arc */
    for (i = 0; i < size; i++) {
        distances[arcs[i].first][arcs[i].second] = arcs[i].weight;
    }
    /* Calculate the rest of the distances */
    for (i = 0; i < order; i++) {
        for (j = 0; j < order; j++) {
            for (k = 0; k < order; k++) {
                const int djk = distances[j][k];
                const int dji = distances[j][i];
                const int dik = distances[i][k];
                if (dji != INT_MAX && dik != INT_MAX
                        && djk > dji + dik)
                {
                    distances[j][k] = dji + dik;
                }
            }
        }
    }
    return distances;
}

/* Connect two edges */
void weighted_edge_connect(weighted_edge *edges, unsigned int first, unsigned int second, unsigned int weight, unsigned int *pos){
    edges[*pos].first = first;
    edges[*pos].second = second;
    edges[*pos].weight = weight;
    (*pos)++;
}

/* Connect two arcs */
void weighted_arc_connect(weighted_arc *arcs, unsigned int first, unsigned int second, int weight, unsigned int *pos) {
    arcs[*pos].first = first;
    arcs[*pos].second = second;
    arcs[*pos].weight = weight;
    (*pos)++;
}

/* Connect two arcs */
void weighted_arc_connect_floyd(weighted_arc *arcs, unsigned int first, unsigned int second, int weight, unsigned int *pos){
    arcs[*pos].first = first;
    arcs[*pos].second = second;
    arcs[*pos].weight = weight;
    (*pos)++;
}

/* Print a distance table */
void print_distances(int **distances, unsigned int order){
    unsigned int i, j;
    for (i = 0; i < order; i++) {
        for (j = 0; j < order; j++) {
            printf("%u: %d\n", j, distances[i][j]);
        }
        //putchar('\n');
        break;
    }
}

int main(void){
    printf("UFF - Pos-graduacao em Computacao\nAnalise e Sintese de Algoritmos - 2019-2.\n");
    printf("Professor Luis Antonio Brasil Kowada\nAluno Flavio Miranda de Farias\n");
    printf("Analise de metodos de algotritmos de maximinizacao e minimizacao custo.\n");

    const unsigned int size = 9; /* Edges */
    const unsigned int order = 6; /* Vertices */
    weighted_edge *edges = (weighted_edge*) malloc(size * sizeof(weighted_edge));
    weighted_arc *arcs = (weighted_arc*) malloc(size * sizeof(weighted_arc));
    weighted_arc *arcs_floyd = (weighted_arc*) malloc(size * sizeof(weighted_arc));
    unsigned int *distances;
    int *distances_bellman, **distances_floyd;
    unsigned int i,j=0,a=0,b=0,c=0;
    //dados do grafo
    int vet[3*size] = {0, 1, 2,
                       0, 2, 4,
                       1, 2, 1,
                       1, 3, 4,
                       1, 4, 2,
                       2, 4, 3,
                       3, 4, 3,
                       3, 5, 2,
                       4, 5, 2,};
    while(j<3*size){ //preenchendo os grafos
        weighted_edge_connect(edges, vet[j], vet[j+1], vet[j+2], &a);
        weighted_arc_connect(arcs, vet[j], vet[j+1], vet[j+2], &b);
        weighted_arc_connect_floyd(arcs_floyd, vet[j], vet[j+1], vet[j+2], &c);
        j=j+3;
    }
    //DIJKSTRA
    clock_t start = clock();
    distances = dijkstra(edges, size, order, 0);
    clock_t time = clock() - start;

    printf("\nDistancias DIJKSTRA:\n");
    for (i = 0; i < order; i++)
        printf("%u: %u\n", i, distances[i]);
    printf("Tempo gasto pelo DIJKSTRA = %f segundos.\n",static_cast<float>(time) / CLOCKS_PER_SEC);

    //BELLMAN-FORD
    start = clock();
    distances_bellman = bellman_ford(arcs, size, order, 0);
    time = clock() - start;

    printf("\nDistancias BELLMAN-FORD:\n");
    for (i = 0; i < order; i++)
        printf("%u: %d\n", i, distances_bellman[i]);
    printf("Tempo gasto pelo BELLMAN-FORD = %f segundos.\n",static_cast<float>(time) / CLOCKS_PER_SEC);

    //FLOYD-WARSHALL
    start = clock();
    distances_floyd = floyd_warshall(arcs_floyd, size, order);
    time = clock() - start;

    printf("\nDistancias FLOYD-WARSHALL:\n");
    print_distances(distances_floyd, order);
    printf("Tempo gasto pelo FLOYD-WARSHALL = %f segundos.\n",static_cast<float>(time) / CLOCKS_PER_SEC);

    free(distances);
    free(edges);
    free(arcs);
    free(distances_bellman);
    free(arcs_floyd);
    for (i = 0; i < order; i++)
        free(distances_floyd[i]);
    free(distances_floyd);

    return 0;
}
/*
digraph g{
  rankdir=LR;
  "0" -> "1" [dir=none color="black" label="2"]
  "0" -> "2" [dir=none color="black" label="4"]
  "1" -> "2" [dir=none color="black" label="1"]
  "1" -> "3" [dir=none color="black" label="4"]
  "1" -> "4" [dir=none color="black" label="2"]
  "2" -> "4" [dir=none color="black" label="3"]
  "3" -> "4" [dir=none color="black" label="3"]
  "3" -> "5" [dir=none color="black" label="2"]
  "4" -> "5" [dir=none color="black" label="2"]
}
*/
