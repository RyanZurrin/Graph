//
// Created by Ryan.Zurrin001 on 12/13/2021.
//
#include "Graph.h"
//******************************************************************************
//___________________________main function______________________________________
int main(int argc, const char * argv[]) {
    // create a graph from user input
    int nb_nodes, nb_edges, is_directed, source, dest;
    scanf("%d %d %d %d %d", &nb_nodes, &nb_edges, &is_directed, &source, &dest);
    graph *g = create_graph(nb_nodes, is_directed);
    while (nb_edges--) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        connect(g, u, v, w);
    }
    print_graph(g);
    dijkstra(g, 6, 3);
    bellman_ford(g, 0);
    get_shortest_path(g, 4, 6);
    printf("breadth first search\n");
    bfs(g, 0);
    printf("\n");
    printf("depth first search\n");
    dfs(g, 0);
    printf("\n");
    printf("connected components\n");
    printf("%d\n", count_connected_components(g));
    towerOfHanoi(8, 1, 2, 3);

    free_graph(g);
    g = NULL;

    return 0;
} //________________________end of main function________________________________

/* I have an input file with the following values in this format to read in for
 * testing the undirected graph data structure:
12 17 0 1 12
1 2 12
1 3 10
2 4 11
2 5 13
3 5 12
3 7 13
4 6 9
5 6 7
6 7 15
6 10 13
6 11 11
7 8 7
8 9 12
8 10 10
9 10 10
10 11 9
11 12 10

* this is the input for a directed graph with a total of 3 components
9 12 1 0 8
0 1 4
0 2 6
1 2 3
2 1 2
3 6 11
4 5 5
4 3 6
4 4 2
5 3 2
5 4 7
6 4 6
7 8 10
 */

//******************************************************************************