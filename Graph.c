//
// Created by Ryan.Zurrin001 on 12/6/2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Graph.h"
#define INT_MAX 2147483647
#define NIL (-1)
//_________________________function definitions_________________________________
graph* create_graph(int nb_nodes, bool is_directed) {
    graph * g = (graph*)malloc(sizeof(graph));
    g->edges = (edge_node **)malloc(sizeof(edge_node *) * nb_nodes);
    g->nb_nodes = nb_nodes;
    g->nb_edges = 0;
    g->is_directed = is_directed;
    for (int i = 0; i < nb_nodes; i++) {
        g->edges[i] = NULL;
    }
    return g;
}

void print_graph(graph* g) {
    printf("Graph: \n");
    for (int i = 0; i < g->nb_nodes; i++) {
        edge_node * e = g->edges[i];
        printf("%d: ", i);
        while (e != NULL) {
            printf("%d ", e->vertex);
            e = e->next;
        }
        printf("\n");
    }
}

void connect(graph* g, int u, int v, int weight) {
    edge_node * e = (edge_node *)malloc(sizeof(edge_node));
    e->vertex = v;
    e->weight = weight;
    e->next = g->edges[u];
    g->edges[u] = e;

    if (!g->is_directed) {
        e = (edge_node *)malloc(sizeof(edge_node));
        e->vertex = u;
        e->weight = weight;
        e->next = g->edges[v];
        g->edges[v] = e;
    }
    g->nb_edges++;
}

edge_node* get_neighbors(graph* g, int u) {
    return g->edges[u];
}

edge_node* add_edge(edge_node* e, int u, int v, int weight) {
    edge_node * new_e = (edge_node *)malloc(sizeof(edge_node));
    new_e->vertex = v;
    new_e->weight = weight;
    new_e->next = e;
    return new_e;
}

edge_node* remove_edge(edge_node* e, int u) {
    if (e == NULL) {
        return NULL;
    }
    if (e->vertex == u) {
        edge_node * temp = e->next;
        free(e);
        return temp;
    }
    e->next = remove_edge(e->next, u);
    return e;
}

bool is_connected(graph* g) {
    int * visited = (int *)malloc(sizeof(int) * g->nb_nodes);
    for (int i = 0; i < g->nb_nodes; i++) {
        visited[i] = 0;
    }
    int nb_visited = 0;
    visited[0] = 1;
    nb_visited++;
    edge_node * e = g->edges[0];
    while (e != NULL) {
        if (visited[e->vertex] == 0) {
            visited[e->vertex] = 1;
            nb_visited++;
        }
        e = e->next;
    }
    return nb_visited == g->nb_nodes;
}

bool adjacentTo(graph* g, int u, int v) {
    edge_node * e = g->edges[u];
    while (e != NULL) {
        if (e->vertex == v) {
            return true;
        }
        e = e->next;
    }
    return false;
}

void union_set(graph* g, int * set, int u, int v) {
    if (set[u] != set[v]) {
        for (int i = 0; i < g->nb_nodes; i++) {
            if (set[i] == set[v]) {
                set[i] = set[u];
            }
        }
    }
}

int get_weight(graph* g, int u, int v) {
    edge_node * e = g->edges[u];
    while (e != NULL) {
        if (e->vertex == v) {
            return e->weight;
        }
        e = e->next;
    }
    return NIL;
}

int get_nb_nodes(graph* g) {
    return g->nb_nodes;
}

int get_nb_edges(graph* g) {
    return g->nb_edges;
}

edge_node* get_edges(graph* g, int u) {
    return g->edges[u];
}

void dfs_helper(graph* g, int u, bool* visited) {
    if (visited[u]) {
        return;
    }
    printf("%d ", u);
    visited[u] = true;
    edge_node * e = get_neighbors(g, u);
    while (e != NULL) {
        dfs_helper(g, e->vertex, visited);
        e = e->next;
    }
}

void dfs_helper2(graph* g, int u, int* visited) {
    if (visited[u] == 1) {
        return;
    }
    //printf("%d ", u);
    visited[u] = 1;
    edge_node * e = get_neighbors(g, u);
    while (e != NULL) {
        dfs_helper2(g, e->vertex, visited);
        e = e->next;
    }
}

void dfs(graph* g, int u) {
    int i;
    bool visited[g->nb_nodes];
    for (i = 0; i < g->nb_nodes; i++) {
        visited[i] = false;
    }
    for (i = u; i < g->nb_nodes; i++) {
        dfs_helper(g, i, visited);
    }
}

void bfs(graph* g, int u) {
    bool visited[g->nb_nodes];
    for (int i = 0; i < g->nb_nodes; i++) {
        visited[i] = false;
    }
    visited[u] = true;
    queue * q = create_queue();
    enqueue(q, u);
    for (int i = u; i < g->nb_nodes; i++) {
        if (visited[i] == false) {
            visited[i] = true;
            enqueue(q, i);
        }
        while (!empty_queue(q)) {
            int v = dequeue(q);
            visited[v] = true;
            printf("%d ", v);
            edge_node * e = get_neighbors(g, v);

            while (e != NULL) {
                if (!visited[e->vertex]) {
                    visited[e->vertex] = true;
                    enqueue(q, e->vertex);
                }
                e = e->next;
            }
        }
    }
    free_queue(q);
}

void dijkstra(graph* g, int source, int destination) {
    heap * h = create_heap(g->nb_edges);
    int parents[g->nb_nodes];
    int distances[g->nb_nodes];
    int node;
    for (node = 0; node < g->nb_nodes; node++) {
        parents[node] = NIL;
        distances[node] = INT_MAX;
    }
    edge u = create_edge(source, 0);
    insert_min_heap(h, &u);
    distances[source] = 0;
    parents[source] = NIL;
    while (!empty_heap(h)) {
        u = remove_min_heap(h);
        edge_node * e = g->edges[u.vertex];
        while (e != NULL) {
            if (distances[u.vertex] + e->weight < distances[e->vertex]) {
                distances[e->vertex] = distances[u.vertex] + e->weight;
                parents[e->vertex] = u.vertex;
                edge v = create_edge(e->vertex, distances[e->vertex]);
                insert_min_heap(h, &v);
            }
            e = e->next;
        }
    }
    int path[g->nb_nodes];
    int path_length = 0;
    int dest = destination;
    do {
        path[path_length++] = dest;
        dest = parents[dest];
    } while (dest != NIL);
    printf("the distance from %d to %d is %d\n", source, destination, distances[destination]);
    for (int i = path_length - 1; i >= 0; i--) {
        printf("%d ", path[i]);
    }
    printf("\n");
    free_heap(h);
    h = NULL;
}

void get_shortest_path(graph* g, int u, int v) {
    dijkstra(g, u, v);
}

int count_connected_components(graph* g) {
    int i;
    int * visited = (int*) malloc(sizeof(int) * g->nb_nodes);
    for (i = 0; i < g->nb_nodes; i++) {
        visited[i] = 0;
    }
    int count = 0;
    for (i = 0; i < g->nb_nodes; i++) {
        if (visited[i] == 0) {
            count++;
            dfs_helper2(g, i, visited);
        }
    }
    free(visited);
    return count;

}

int count_paths(graph* g, int u, int v, bool* visited) {
    if (u == v) {
        return 1;
    }
    visited[u] = true;
    int nb_paths = 0;
    edge_node * e = get_neighbors(g, u);
    while (e != NULL) {
        if (!visited[e->vertex]) {
            nb_paths += count_paths(g, e->vertex, v, visited);
        }
        e = e->next;
    }
    visited[u] = false;
    free(e);
    return nb_paths;
}


// uses a heap to find the shortest path from any source to all others nodes using heap
void bellman_ford(graph* g, int source) {
    heap * h = create_heap(g->nb_nodes);
    int parents[g->nb_nodes];
    int distances[g->nb_nodes];
    int node;
    for (node = 0; node < g->nb_nodes; node++) {
        parents[node] = NIL;
        distances[node] = INT_MAX;
    }
    edge u = create_edge(source, 0);
    insert_min_heap(h, &u);
    distances[source] = 0;
    parents[source] = NIL;
    for (int i = 0; i < g->nb_nodes - 1; i++) {
        u = remove_min_heap(h);
        edge_node * e = g->edges[u.vertex];
        while (e != NULL) {
            if (distances[u.vertex] + e->weight < distances[e->vertex]) {
                distances[e->vertex] = distances[u.vertex] + e->weight;
                parents[e->vertex] = u.vertex;
                edge v = create_edge(e->vertex, distances[e->vertex]);
                insert_min_heap(h, &v);
            }
            e = e->next;
        }
        free(e);
        e = NULL;
    }
    for (int i = 0; i < g->nb_nodes; i++) {
        if (distances[i] == INT_MAX) {
            printf("there is no path from %d to %d\n", source, i);
        }
        else {
            printf("the distance from %d to %d is %d\n", source, i, distances[i]);
        }
    }
    free_heap(h);
}

bool find(const int *pInt, int u) {
    return pInt[u] == u;
}
void display(int arr[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void towerOfHanoi(int n, int source, int destination, int aux) {
    if (n == 1) {
        printf("move disk 1 from peg %d to peg %d\n", source, destination);
        return;
    }
    towerOfHanoi(n - 1, source, aux, destination);
    printf("move disk %d from peg %d to peg %d\n", n, source, destination);
    towerOfHanoi(n - 1, aux, destination, source);
}

void free_graph(graph* g) {
    for (int i = 0; i < g->nb_nodes; i++) {
        edge_node * e = g->edges[i];
        while (e != NULL) {
            edge_node * tmp = e;
            e = e->next;
            free(tmp);
        }
    }
    free(g->edges);
    free(g);
}