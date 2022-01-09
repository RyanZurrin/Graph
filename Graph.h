//
// Created by Ryan.Zurrin001 on 12/13/2021.
//

#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Queue.h"
#include "Heap.h"
//__________________________graph data structure________________________________
typedef struct edge_node {
    int vertex;
    int weight;
    struct edge_node *next;
} edge_node;
typedef struct graph {
    edge_node * * edges;
    int nb_nodes;
    int nb_edges;
    bool is_directed;
} graph;

// create a new graph
graph* create_graph(int, bool);
// print the graph
void print_graph(graph*);
// connect u to v with the weight w
void connect(graph*, int, int, int);
//get the neighbors of a node
edge_node* get_neighbors(graph*, int);
//add edge to the graph
edge_node* add_edge(edge_node*, int, int, int);
// remove edge from the graph
edge_node* remove_edge(edge_node*, int);
// boolean to check if the graph is connected
bool is_connected(graph*);
// determine if two nodes are adjacent
bool adjacentTo(graph*, int, int);
// union of two sets
void union_set(graph*, int*, int, int);
// find if a value is in a set
bool find(const int*, int);
// get the weight of the edge u to v
int get_weight(graph*, int, int);
// get the number of nodes in the graph
int get_nb_nodes(graph*);
// get the number of edges in the graph
int get_nb_edges(graph*);
// get the list of edges for a given node
edge_node* get_edges(graph*, int);
// dfs helper for traversal of the graph
void dfs_helper(graph*, int, bool*);
void dfs_helper2(graph*, int, int*);
// dfs traversal of the graph
void dfs(graph*, int);
// bfs traversal of the graph
void bfs(graph*, int);
// find if u is the set of pInt
// count the number of connected components in the graph
int count_connected_components(graph*);
// count number of paths between u and v
int count_paths(graph*, int, int, bool *);
// Dijkstra's algorithm
void dijkstra(graph*, int, int);
// Bellman-Ford algorithm
void bellman_ford(graph*, int);
// get the shortest path between u and v
void get_shortest_path(graph*, int, int);
// Kruskal's algorithm
//void kruskal(graph*);
// Prim's algorithm
//void prim(graph*, int);
// DFS for finding articulation points
//void dfs_articulation_points(graph*, int, int*, int*);
// DFS for finding bridges
//void dfs_bridges(graph*, int, int*, int*);
void display(int arr[], int size);
// function to solve the tower of hanoi
void towerOfHanoi(int, int, int, int);
// free the memory allocated for the graph
void free_graph(graph*);

#endif //GRAPH_GRAPH_H
